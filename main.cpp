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

using namespace std;

const string CYAN = "\033[33m";
const string MAGENTA = "\033[35m";
const string BOLD = "\033[1m";
const string RESET = "\033[0m";

// Function to display the futuristic splash screen
void displayLogo() {
    
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

    )" << endl << RESET;

    // Subtitle / Tagline
    cout << "================================================" <<endl;
    cout << MAGENTA << ">> [ SYSTEM NETWORK PROBE INITIATED ]" << RESET << "\n";
    cout << "    --------------------------------------------\n";
    cout << "    Status:  " << CYAN << "ONLINE" << RESET << "          Version: 1.0.4\n\n";
    cout<<endl;
    cout<<"Usage: Select Options from Below"<<endl;
    cout<<endl;
    cout<<"[1] Target Port Scanning"<<endl;
    cout<<"[2] Target Service Scanning"<<endl;
    cout<<"[3] Host Discovery"<<endl;
    cout<<"[4] Banner Grabbing and Operating System Detection"<<endl;
    cout<<"[5] Vulnerability Analysis"<<endl;
    cout<<"[6] Scan Report and Logs"<<endl;
    cout<<"[7] Help, Credits and About"<<endl;
    cout<<endl;
    cout<<"[99] Exit the Application"<<endl;
    cout<<endl;
}

int main() {

    system("clear");

    PortScanner scanner("127.0.0.1", 20, 500, 10);
    int choice;

    displayLogo();

    cout<< CYAN << "probe" << RESET <<">";
    cin>>choice;

    if (choice == 1){

        vector<PortResult> results = scanner.scanAllPorts();
    
        cout << "Scan Results:\n";
        for (const auto& r : results) {
            if (r.open)
                cout << "Port " << r.port << " is OPEN\n";
        }
    }

    else if (choice == 99){
        
        cout<<endl;
        cout<<"Thanks for Using Netprobe as your Network Agent";
        cout<<endl;
        cout<<"Happy Hacking...and remember...hugs are more worht than handshakes";
        cout<<endl;
    }
    
    
    return 0;
}
