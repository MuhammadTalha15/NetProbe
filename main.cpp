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

using namespace std;

// Function to display the futuristic splash screen
void displayLogo() {
    
    // ANSI Escape Codes for Colors
    const string CYAN = "\033[33m";
    const string MAGENTA = "\033[35m";
    const string BOLD = "\033[1m";
    const string RESET = "\033[0m";

    // The Logo (Using C++ Raw String Literal)

        cout << CYAN << R"(
              #                 #                                  
             ###               ###                                 
            ####               ####                                
           ######             ######                               
          ########           ########                              
         ##########         +#########                             
       .###############################.                           
      .#################################.                          
     #####################################                         
    #######################################                        
   ###########+ .#############. -###########                       
  ############+   +#########+   -############                      
    ##########+     #######     -##########                        
       -###############################-                           
           #########################.                              
              ###################                                  
                ###############                                    
                 #############                                     
                  ###########                                      
                   #########.                                      
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
}

void displayHelp(){
    
    cout<<"\nSCAN TECHNIQUES: " <<endl;
    cout<<" -p ( Simple Port Scan )" <<endl;
    cout<<" -sV ( Target Service Version Detection )" <<endl;
    cout<<" -O ( Operating System Detection )" <<endl;
    cout<<" -p ( Simple Port Scan )" <<endl;
    cout<<" -pS ( IP Protocol Scan )" <<endl;

    cout<<"\nHOST DISCOVERY: " <<endl;
    cout<<" -sn ( Simple Ping Scan )" <<endl;
    cout<<" -sL ( Scanning from Given Lists )" <<endl;
    cout<<" -O ( Operating System Detection )" <<endl;
    cout<<" -p ( Simple Port Scan )" <<endl;

    cout<<"\nEXAMPLES: " <<endl;
    cout<<" netp <target ip address>" <<endl;
    cout<<" netp -flag <target ip address>" <<endl;
    cout<<" Type [ -h or --help ] anytime for Help" <<endl;

}

void displayBanner(){
    cout << "================================================" <<endl;
    cout << "           SCANING TECHNIQUES AND ORDER         " <<endl;
    cout << "================================================" <<endl;

    displayHelp();

}

int main() {
    system("clear");

    string choice;

    displayLogo();
    displayBanner();

    cout<<">";
    cin>>choice;

    if (choice == "-h" || choice == "--help"){
        displayHelp();
    }
    
    
    return 0;
}
