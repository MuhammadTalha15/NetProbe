#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include "portScanner.h"

using namespace std;

class LogManager {
private:
    string logFilePath;
    string csvFilePath;
    string version;

    string getCurrentTimestamp(); 
    void writeToJSON(string jsonEntry); 
    void writeToCSV(string timestamp, string target, string type, string duration, string result); 
    string formatTarget(const string& original, const string& resolved);

public:
    LogManager(string path = "log/logs.json", string csvPath = "log/report.csv");

    void logPortScan(const string& original, const string& resolved, const vector<PortResult>& results, double duration);
    void logGeneralScan(const string& type, const string& original, const string& resolved, const string& resultData, double duration);
    
    void displayPrettyLogs(string filter = "", string filterType = ""); 
    void displayDashboard(); 
};

#endif
