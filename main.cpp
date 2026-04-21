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

#include "./utilities/help.cpp"

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

int main() {
    system("clear");

    string choice;

    displayLogo();

    cout<<">";
    cin>>choice;

    if (choice == "-h" || choice == "--help"){
        displayBanner();
        // displayHelp();
    }
    
    
    return 0;
}
