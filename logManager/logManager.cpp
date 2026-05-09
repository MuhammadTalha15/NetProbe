
#include "../headers/log_manager.h"
#include <ctime>
#include <sstream>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

LogManager::LogManager(string path, string csvPath) : logFilePath(path), csvFilePath(csvPath) {
    version = "1.0.4";
    fs::path p(logFilePath);
    if (!fs::exists(p.parent_path())) {
        fs::create_directory(p.parent_path());
    }
}

string LogManager::getCurrentTimestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", ltm);
    return string(buffer);
}

string LogManager::formatTarget(const string& original, const string& resolved) {
    if (original == resolved || original.empty()) return resolved;
    return original + " [" + resolved + "]";
}

void LogManager::writeToCSV(string timestamp, string target, string type, string duration, string result) {
    bool fileExists = fs::exists(csvFilePath);
    ofstream csvFile(csvFilePath, ios::app);
    if (!fileExists) {
        csvFile << "Timestamp,Target,ScanType,Duration(sec),Result\n";
    }
    string sanitizedResult = result;
    // Replace problematic characters for CSV compatibility
    replace(sanitizedResult.begin(), sanitizedResult.end(), ',', ';');
    replace(sanitizedResult.begin(), sanitizedResult.end(), '\n', ' ');
    replace(sanitizedResult.begin(), sanitizedResult.end(), '\r', ' ');
    csvFile << timestamp << "," << target << "," << type << "," << duration << "," << sanitizedResult << "\n";
    csvFile.close();
}

void LogManager::writeToJSON(string jsonEntry) {
    ifstream inFile(logFilePath);
    string content;
    if (inFile) {
        stringstream buffer;
        buffer << inFile.rdbuf();
        content = buffer.str();
        inFile.close();
    }
    ofstream outFile(logFilePath);
    if (content.empty() || content == "[]") {
        outFile << "[\n" << jsonEntry << "\n]";
    } else {
        size_t lastBracket = content.find_last_of(']');
        if (lastBracket != string::npos) {
            string existing = content.substr(0, lastBracket);
            if (existing.find('{') != string::npos) outFile << existing << ",\n" << jsonEntry << "\n]";
            else outFile << "[\n" << jsonEntry << "\n]";
        }
    }
    outFile.close();
}

void LogManager::logPortScan(const string& original, const string& resolved, const vector<PortResult>& results, double duration) {
    string timestamp = getCurrentTimestamp();
    string targetDisplay = formatTarget(original, resolved);
    stringstream res;
    bool foundOpen = false;
    res << "Open: ";
    for (const auto& r : results) {
        if (r.open) { res << r.port << " "; foundOpen = true; }
    }
    string finalRes = foundOpen ? res.str() : "None/Interrupted";

    stringstream ss;
    ss << "  {\n    \"timestamp\": \"" << timestamp << "\",\n    \"type\": \"Port Scan\",\n    \"target\": \"" << targetDisplay << "\",\n    \"duration_sec\": \"" << fixed << setprecision(2) << duration << "\",\n    \"result\": \"" << finalRes << "\"\n  }";
    writeToJSON(ss.str());
    writeToCSV(timestamp, targetDisplay, "Port Scan", to_string(duration), finalRes);
}

void LogManager::logGeneralScan(const string& scanType, const string& original, const string& resolved, const string& resultData, double duration) {
    string timestamp = getCurrentTimestamp();
    string targetDisplay = formatTarget(original, resolved);
    
    // Sanitize JSON input: escape quotes to avoid breaking JSON structure
    string cleanData = resultData;
    size_t pos = 0;
    while ((pos = cleanData.find("\"", pos)) != string::npos) {
        cleanData.replace(pos, 1, "\\\"");
        pos += 2;
    }

    stringstream ss;
    ss << "  {\n    \"timestamp\": \"" << timestamp << "\",\n    \"type\": \"" << scanType << "\",\n    \"target\": \"" << targetDisplay << "\",\n    \"duration_sec\": \"" << fixed << setprecision(2) << duration << "\",\n    \"result\": \"" << cleanData << "\"\n  }";
    writeToJSON(ss.str());
    writeToCSV(timestamp, targetDisplay, scanType, to_string(duration), cleanData);
}

void LogManager::displayPrettyLogs(string filter, string filterType) {
    ifstream inFile(logFilePath);
    if (!inFile) { cout << "\n[!] No logs found.\n"; return; }
    cout << "\n" << "\033[1;36m" << left << setw(28) << "TARGET" << setw(18) << "TIMESTAMP" << setw(15) << "TYPE" << setw(10) << "DUR(s)" << "RESULT" << "\033[0m" << endl;
    cout << string(100, '-') << endl;
    string line, target, time, type, dur, result;
    while (getline(inFile, line)) {
        if (line.find("\"target\":") != string::npos) target = line.substr(line.find(": \"") + 3, line.find_last_of("\"") - (line.find(": \"") + 3));
        if (line.find("\"timestamp\":") != string::npos) time = line.substr(line.find(": \"") + 3, line.find_last_of("\"") - (line.find(": \"") + 3));
        if (line.find("\"type\":") != string::npos) type = line.substr(line.find(": \"") + 3, line.find_last_of("\"") - (line.find(": \"") + 3));
        if (line.find("\"duration_sec\":") != string::npos) dur = line.substr(line.find(": \"") + 3, line.find_last_of("\"") - (line.find(": \"") + 3));
        if (line.find("\"result\":") != string::npos) {
            result = line.substr(line.find(": \"") + 3, line.find_last_of("\"") - (line.find(": \"") + 3));
            if ((filter == "" || target.find(filter) != string::npos) && (filterType == "" || type.find(filterType) != string::npos)) {
                // To keep table clean, only show start of result if it's a huge banner
                string shortRes = (result.length() > 40) ? result.substr(0, 37) + "..." : result;
                cout << left << setw(28) << target << setw(18) << time << setw(15) << type << setw(10) << dur << shortRes << endl;
            }
        }
    }
}

void LogManager::displayDashboard() {
    ifstream inFile(logFilePath);
    if (!inFile) return;
    int totalScans = 0; double totalDuration = 0; map<string, int> targetFreq; string line;
    while (getline(inFile, line)) {
        if (line.find("\"target\":") != string::npos) {
            string t = line.substr(line.find(": \"") + 3, line.find_last_of("\"") - (line.find(": \"") + 3));
            targetFreq[t]++; totalScans++;
        }
        if (line.find("\"duration_sec\":") != string::npos) {
            string d = line.substr(line.find(": \"") + 3, line.find_last_of("\"") - (line.find(": \"") + 3));
            totalDuration += stod(d);
        }
    }
    string mostScanned = "N/A"; int maxCount = 0;
    for (auto const& [target, count] : targetFreq) { if (count > maxCount) { maxCount = count; mostScanned = target; } }
    cout << "\n\033[1;35m" << "========== NETPROBE ANALYTICS DASHBOARD ==========" << "\033[0m\n";
    cout << "  [+] Total Scans Conducted : " << totalScans << "\n";
    cout << "  [+] Most Scanned Target   : " << mostScanned << " (" << maxCount << " times)\n";
    cout << "  [+] Total Execution Time  : " << fixed << setprecision(2) << totalDuration << " seconds\n";
    cout << "  [+] Avg Scan Duration     : " << (totalScans ? totalDuration/totalScans : 0) << " seconds\n";
    cout << "\033[1;35m" << string(50, '=') << "\033[0m\n";
}
