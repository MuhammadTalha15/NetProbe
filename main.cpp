#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

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
#include "./headers/hostresolver.h"

using namespace std;

const string YELLOW = "\033[33m";
const string GREEN = "\033[32m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";
const string BOLD = "\033[1m";
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
    cout << "[3] Host Discovery" << endl;
    cout << "[4] Banner Grabbing and Operating System Detection" << endl;
    cout << "[5] Vulnerability Analysis" << endl;
    cout << "[6] Scan Report and Logs" << endl;
    cout << "[7] Help, Credits and About" << endl;
    cout << endl;
    cout << "[99] Exit the Application" << endl;
    cout << endl;
}

int main(){

    int choice;
    string targetIP;

    while (true){

        system("clear");
        displayLogo();

        cout << CYAN << "probe" << RESET << ">";
        cin >> choice;

        if (choice == 1){

            cout << "Enter Target IP / Domain: ";
            cin >> targetIP;

            HostResolver resolver;

            string host = resolver.extractHostname(targetIP);

            bool isDomain = false;
            for (char c : host){
                if (isalpha(c)){
                    isDomain = true;
                    break;
                }
            }

            string finalTarget = host;

            if (isDomain){
                string ipAddress = resolver.resolveToIP(host);

                if (ipAddress.empty()){
                    cout << "Could not resolve host\n";
                    continue; // go back to menu
                }

                cout << "Resolved: " << host << " -> " << ipAddress << endl;
                finalTarget = ipAddress;
            }

            cout << YELLOW << "Starting NetProbe Scanning ..." << RESET << endl;

            PortScanner scanner(finalTarget, 20, 500, 250);
            vector<PortResult> results = scanner.scanAllPorts();

            cout << "\nNetProbe Scan Results for (" << targetIP
                 << ") Resolved to -> " << finalTarget << "\n\n";

            bool found = false;
            for (const auto &r : results){
                if (r.open){
                    cout << "Port " << r.port << " is OPEN ["
                         << GREEN << "OK" << RESET << "]\n";
                    found = true;
                }
            }

            if (!found)
                cout << "No open ports found.\n";

            // ⏸ Pause before returning to menu
            cout << "\nPress Enter to return to menu...";
            cin.ignore();
            cin.get();
        }

        else if (choice == 3){
            // Service Detection

            // string ip;

            // cout<<"Enter Target IP: ";
            // cin>>ip;

            // OSDetector osd;

            // string os = osd.detectOS(ip);
            // cout << "\nDetected OS: " << os << std::endl;



        }

        else if (choice == 99){

            cout << "\nThanks for Using Netprobe as your Network Agent\n";
            cout << "Happy Hacking...and remember...hugs are more worth than handshakes\n";
            break; // exit loop
        }

        else {
            cout << "Invalid option!\n";
        }
    }

    return 0;
}
