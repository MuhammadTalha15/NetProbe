#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <csignal> // FOR CTRL+C INTERRUPT PERSISTENCE // <- HASSAN INCLUDED THIS

// THREADNG LIBRARIES

#include <thread>
#include <mutex>

// POSIX SOCKET LIBRARIES

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

// SOURCE FILES

#include "./headers/portScanner.h"
#include "./headers/service_detection.h"
#include "./headers/hostresolver.h"
#include "./headers/banner.h"
#include "./headers/log_manager.h"

#include "./headers/help.h"

using namespace std;

// GLOBAL SIGNAL FLAG FOR CTRL+C PERSISTENCE // <- INCLUDED BY HASSAN
volatile sig_atomic_t stopFlag = 0;

void handleInterrupt(int sig) { 

    stopFlag = 1; 

    // Notifying the user immediately
    write(STDOUT_FILENO, "\n[!] Interrupt Received! Finalizing log storage...\n", 51);

}

const string YELLOW = "\033[33m";
const string GREEN = "\033[32m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";
const string BOLD = "\033[1m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

// Function to display the futuristic splash screen
void displayLogo(){

    // ANSI Escape Codes for Colors

    // The Logo (Using C++ Raw String Literal)

    cout << CYAN << R"(
              #                 #                                  
             ###               ###                                 
            ####               ####                                
           ######             ######                               
          ########           ########                              
         ##########         ##########                             
       .###############################.                           
      .#################################.                          
     #####################################                         
    #######################################                        
   ###########+ .#############. +###########                       
  ############+   +#########+   +############                      
    ##########+     #######     +##########                        
       -###############################-                           
           #########################                              
              ###################                                  
                ###############                                    
                 #############                                     
                  ###########                                      
                   #########                                      
                    #######                    
    )" << RESET;

    cout << BOLD << CYAN << R"(
    _   __     __  ____             __       
   / | / /__  / /_/ __ \_________  / /__ ___
  /  |/ / _ \/ __/ /_/ / ___/ __ \/ __  / _ \
 / /|  /  __/ /_/ ____/ /  / /_/ / /_/ /  __/
/_/ |_/\___/\__/_/   /_/   \____/\__,_/\___/

    )" << endl
         << RESET;

    // Subtitle / Tagline
    cout << "================================================" << endl;
    cout << MAGENTA << ">> [ SYSTEM NETWORK PROBE INITIATED ]" << RESET << "\n";
    cout << "    --------------------------------------------\n";
    cout << "    Status:  " << CYAN << "ONLINE" << RESET << "          Version: 1.0.4\n\n";
    cout << endl;
    cout << "Usage: Select Options from Below" << endl;
    cout << endl;
    cout << "[1] Target Port Scanning" << endl;
    cout << "[2] Target Service Scanning" << endl;
    cout << "[3] Banner Grabbing and Operating System Detection" << endl;
    cout << "[4] Scan Report and Logs" << endl;
    cout << "[6] Help, Credits and About" << endl;
    cout << endl;
    cout << "[99] Exit the Application" << endl;
    cout << endl;
}

int main(){
    
    // Register the Ctrl+C signal handler
    signal(SIGINT, handleInterrupt);

    int choice;
    string targetIP;

    // ======================================================
    // LOG GENERATION: Initialize LogManager Object
    // ======================================================
    LogManager logger;

    while (true){
        
        stopFlag = 0; // Reset signal flag for new operation

        system("clear");
        displayLogo();

        cout << CYAN << "probe" << RESET << ">";

        cin >> choice;

        // if (!(cin >> choice)) {
        //     if (cin.eof()) break;
        //     cin.clear();
        //     cin.ignore(1000, '\n');
        //     continue;
        // }

        if (choice == 1){
            cout << "Enter Target IP / Domain: ";
            cin >> targetIP;

            HostResolver resolver;

            string hostInput = resolver.extractHostname(targetIP);

            string finalTarget = resolver.resolveToIP(hostInput);

            if (finalTarget.empty()) {
            
                cout << RED << "Could not resolve host" << RESET << endl;
            
                sleep(1);
            
                continue;
            }

            // Show resolved result only if domain was entered
            if(hostInput != finalTarget) {
            
                cout << "Resolved: "
                     << hostInput
                     << " -> "
                     << finalTarget
                     << endl;
            }

            cout << YELLOW
                 << "Starting NetProbe Scanning ..."
                 << RESET << endl;

            // ======================================================
            // Timing Start
            // ======================================================

            auto start = chrono::high_resolution_clock::now();

            PortScanner scanner(finalTarget, 20, 500, 250);

            vector<PortResult> results;

            bool found = false;

            // ======================================================
            // Manual Scan Loop (Old Style Preserved)
            // ======================================================

            for(int p = 20; p <= 500; p++) {
            
                if(stopFlag) {
                    break;
                }
            
                bool isOpen = scanner.startSinglePortScan(p);
            
                if(isOpen) {
                
                    cout << "Port "
                         << p
                         << " is OPEN ["
                         << GREEN
                         << "OK"
                         << RESET
                         << "]\n";
                
                    results.push_back({p, true});
                
                    found = true;
                }
            }

            // ======================================================
            // Timing End
            // ======================================================

            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double> duration = end - start;

            // ======================================================
            // Final Result Header
            // ======================================================

            cout << "\nNetProbe Scan Results for ("
                 << targetIP
                 << ") Resolved to -> "
                 << finalTarget
                 << "\n\n";

            if(!found) {
            
                cout << "No open ports found.\n";
            }

            // ======================================================
            // Interrupted Scan Message
            // ======================================================

            if(stopFlag) {
            
                cout << RED
                     << "\n[!] User Interrupted. Partial data saved."
                     << RESET
                     << endl;
            }

            // ======================================================
            // Save Logs
            // ======================================================

            logger.logPortScan(
                hostInput,
                finalTarget,
                results,
                duration.count()
            );

            cout << CYAN
                 << "\n[!] Results exported to log/logs.json"
                 << RESET
                 << endl;

            // ======================================================
            // Pause
            // ======================================================

            cout << "\nPress Enter to return to menu...";

            cin.ignore(1000, '\n');
            cin.get();        
        }

        else if (choice == 2) {

            cout << "Enter Target IP / Domain: ";

            cin >> targetIP;

            HostResolver resolver;

            string hostInput =
                resolver.extractHostname(targetIP);

            string finalTarget =
                resolver.resolveToIP(hostInput);

            if(finalTarget.empty()) {
            
                cout << RED
                     << "Could not resolve host"
                     << RESET
                     << endl;
            
                sleep(1);
            
                continue;
            }
        
            if(hostInput != finalTarget) {
            
                cout << "Resolved: "
                     << hostInput
                     << " -> "
                     << finalTarget
                     << endl;
            }
        
            cout << YELLOW
                 << "Starting Service Detection..."
                 << RESET
                 << endl;
        
            auto start =
                chrono::high_resolution_clock::now();
        
            ServiceDetection detector(finalTarget);
        
            vector<int> commonPorts = {
            
                21,
                22,
                25,
                53,
                80,
                110,
                143,
                443,
                445,
                3306,
                5432,
                6379,
                8080
            };
        
            vector<ServiceInfo> results =
                detector.detectMultipleServices(
                    commonPorts
                );
            
            stringstream logData;
            
            bool found = false;
            
            for(const auto& result : results){
            
                found = true;
            
                cout << "\n========================\n";
            
                cout << GREEN
                     << "[+] PORT "
                     << result.port
                     << RESET
                     << endl;
            
                cout << "Service : "
                     << result.serviceName
                     << endl;
            
                cout << "Protocol: "
                     << result.protocol
                     << endl;
            
                cout << "Version : "
                     << result.version
                     << endl;
            
                if(!result.metadata.empty()){
                
                    cout << "\nMetadata:\n";
                
                    for(
                        const auto& item
                        : result.metadata
                    ){
                    
                        cout << item.first
                             << " : "
                             << item.second
                             << endl;
                    }
                }
            
                logData
                    << "--- Port "
                    << result.port
                    << " ---\n";
            
                logData
                    << "Service: "
                    << result.serviceName
                    << "\n";
            
                logData
                    << "Protocol: "
                    << result.protocol
                    << "\n";
            
                logData
                    << "Version: "
                    << result.version
                    << "\n\n";
            }
        
            if(!found){
            
                cout << RED
                     << "\nNo detectable services found\n"
                     << RESET
                     << endl;
            }
        
            auto end =
                chrono::high_resolution_clock::now();
        
            chrono::duration<double>
                duration = end - start;
        
            logger.logGeneralScan(
            
                "Service Detection",
            
                hostInput,
            
                finalTarget,
            
                logData.str(),
            
                duration.count()
            );
        
            cout << CYAN
                 << "\n[!] Service detection results logged"
                 << RESET
                 << endl;
        
            cout << "\nPress Enter to continue...";
        
            cin.ignore(1000, '\n');
        
            cin.get();
        
        }

        else if (choice == 3){
            cout << "Enter Target IP / Domain: ";

            cin >> targetIP;

            HostResolver resolver;

            string hostInput = resolver.extractHostname(targetIP);

            string finalTarget = resolver.resolveToIP(hostInput);

            if(finalTarget.empty()) {
            
                cout << RED
                     << "Could not resolve host"
                     << RESET
                     << endl;
            
                sleep(1);
            
                continue;
            }

            // Show resolution only if domain was entered
            if(hostInput != finalTarget) {
            
                cout << "Resolved: "
                     << hostInput
                     << " -> "
                     << finalTarget
                     << endl;
            }

            // ======================================================
            // Timing Start
            // ======================================================

            auto start = chrono::high_resolution_clock::now();

            // ======================================================
            // Log Data Collector
            // ======================================================

            stringstream realLogData;

            BannerGrabber bg;

            vector<int> commonPorts = {
                21,22,25,80,110,143,443,8080
            };

            bool found = false;

            cout << YELLOW
                 << "Initiating Banner/OS Detection..."
                 << RESET
                 << endl;

            for(int port : commonPorts) {
            
                if(stopFlag) {
                    break;
                }
            
                if(bg.isPortOpen(finalTarget, port)) {
                
                    found = true;
                
                    cout << "\n[+] Port "
                         << port
                         << " OPEN\n";
                
                    string banner =
                        bg.grabBanner(finalTarget, port);
                
                    cout << "\nBanner:\n";
                
                    cout << banner << endl;
                
                    string os =
                        bg.detectOS(banner);
                
                    cout << "\nDetected OS: ";
                
                    cout << os << endl;
                
                    // ======================================================
                    // Capture Data For Logs
                    // ======================================================
                
                    realLogData
                        << "--- Port "
                        << port
                        << " ---\n";
                
                    realLogData
                        << "Banner: "
                        << (banner.empty() ? "None" : banner)
                        << "\n";
                
                    realLogData
                        << "OS: "
                        << os
                        << "\n\n";
                }
            }

            // ======================================================
            // Timing End
            // ======================================================

            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double> duration =
                end - start;

            // ======================================================
            // Interrupted Scan
            // ======================================================

            if(stopFlag) {
            
                cout << RED
                     << "\n[!] Interrupted. Saving banners collected so far..."
                     << RESET
                     << endl;
            
                realLogData << "[SCAN INTERRUPTED]";
            }

            // ======================================================
            // Final Output
            // ======================================================

            if(!found && !stopFlag) {
            
                cout << "\nNo responsive services found\n";
            }

            // ======================================================
            // Save Logs
            // ======================================================

            if(found || stopFlag) {
            
                logger.logGeneralScan(
                    "Banner/OS Scan",
                    hostInput,
                    finalTarget,
                    realLogData.str(),
                    duration.count()
                );
            
                cout << CYAN
                     << "\n[!] Full banner data logged to log/logs.json"
                     << RESET
                     << endl;
            }

            // ======================================================
            // Pause
            // ======================================================

            cout << "\nPress Enter to continue...";

            cin.ignore(1000, '\n');
            cin.get();
        }

        else if (choice == 4) {
            
            system("clear");

            int logChoice;

            cout << MAGENTA << BOLD << "--- NETPROBE REPORT & ANALYTICS ---" << RESET << "\n\n";

            cout << "[1] View All Logs (Pretty Table View)\n";

            cout << "[2] Search Logs by Target Name/IP\n";

            cout << "[3] Filter Logs by Scan Type\n";

            cout << "[4] View Analytics Dashboard\n";

            cout << "[0] Back to Main Menu\n\n";

            cout << CYAN << "log-manager" << RESET << ">";

            cin >> logChoice;

            if (logChoice == 1) {

                logger.displayPrettyLogs();

            } else if (logChoice == 2) {

                string searchKey; 

                cout << "Enter Target Name or IP to Search: "; 

                cin >> searchKey;

                logger.displayPrettyLogs(searchKey); 

            } else if (logChoice == 3) {

                string sType; 

                // UPDATED: CLEARER INPUT OPTIONS
                cout << "Enter Scan Type (Port Scan / Banner/OS Scan): "; 

                cin.ignore(1000, '\n'); 
                
                getline(cin, sType);

                logger.displayPrettyLogs("", sType);

            } else if (logChoice == 4) {

                logger.displayDashboard();

            }
            
            if (logChoice != 0) { 

                cout << "\nPress Enter to continue..."; 

                cin.ignore(1000, '\n'); cin.get(); 

            }
        }

        else if (choice == 6) {
            Help *help = new HelpBanner();

            help->ApplicationHelp();

            help->DevelopmentTeam();

            delete help;
        }

        else if (choice == 99){

            cout << "\nThanks for Using Netprobe as your Network Agent\n";
            cout << "Happy Hacking...and remember...hugs are more worth than handshakes\n";
            break; // exit loop
        }

        else {
            cout << BOLD << RED << "Invalid option!\n" << RESET;
            break;
        }
    }

    return 0;
}
