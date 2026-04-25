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

    system("clear");

    int choice;
    string targetIP;

    displayLogo();

    cout << CYAN << "probe" << RESET << ">";
    cin >> choice;

    if (choice == 1){

        cout << "Enter Target IP / Domain: ";
        cin >> targetIP;

        HostResolver resolver;

        // Step 1: Extract clean hostname (works for URL/domain/IP)

        string host = resolver.extractHostname(targetIP);

        // Step 2: Detect if it's a domain (contains letters)

        bool isDomain = false;
        for (char c : host){

            if (isalpha(c)){

                isDomain = true;
                break;
            }
        }

        string finalTarget = host;

        // Step 3: Resolve if domain

        if (isDomain){

            string ipAddress = resolver.resolveToIP(host);

            if (ipAddress.empty()){

                cout << "Could not resolve host\n";
                return 0;
            }

            cout << "Resolved: " << host << " -> " << ipAddress << endl;
            finalTarget = ipAddress;
        }

        // Step 4: Scan
        cout<< YELLOW << "Starting NetProbe Scanning ..." << RESET << endl;
        PortScanner scanner(finalTarget, 20, 500, 230);
        vector<PortResult> results = scanner.scanAllPorts();

        
        // Step 5: Output
        cout << "\nNetProbe Scan Results for ("<< targetIP << ") Resolved to -> " << finalTarget << "\n\n";

        bool found = false;
        for (const auto &r : results){

            if (r.open){
                
                cout << "Port " << r.port << " is OPEN ["<< GREEN << "OK" << RESET <<"]\n";
                found = true;
            }
        }

        if (!found)
            cout << "No open ports found.\n";
    }


    if ( choice == 2){
        // Service Detection Code Goes Here 

    }

    else if (choice == 99){

        cout << endl;
        cout << "Thanks for Using Netprobe as your Network Agent";
        cout << endl;
        cout << "Happy Hacking...and remember...hugs are more worht than handshakes";
        cout << endl;
    }

    return 0;
}
