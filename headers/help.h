#ifndef HELPBANNER_H
#define HELPBANNER_H

#include <iostream>
#include <string>

using namespace std;

// ==========================================================
// ABSTRACT BASE CLASS
// ==========================================================

class Help {

    public:

        virtual void ApplicationHelp() = 0;

        virtual void DevelopmentTeam() = 0;

        virtual ~Help() {}
};

// ==========================================================
// DERIVED CLASS
// ==========================================================

class HelpBanner : public Help {

    private:

        const string CYAN    = "\033[36m";
        const string GREEN   = "\033[32m";
        const string YELLOW  = "\033[33m";
        const string RED     = "\033[31m";
        const string MAGENTA = "\033[35m";
        const string BOLD    = "\033[1m";
        const string RESET   = "\033[0m";

        void displayBanner(){

            cout << RESET;

            cout << MAGENTA
                 << "========================================================\n"
                 << "          NETPROBE HELP & DOCUMENTATION PANEL\n"
                 << "========================================================\n"
                 << RESET << endl;
        }

    public:

        // ==========================================================
        // POLYMORPHIC FUNCTION #1
        // ==========================================================

        void ApplicationHelp() override {

            system("clear");

            displayBanner();

            cout << BOLD << GREEN
                 << "[+] APPLICATION FEATURES"
                 << RESET << "\n\n";

            cout << YELLOW
                 << "[1] TARGET PORT SCANNING"
                 << RESET << endl;

            cout << "    -> Detects open TCP ports on target systems.\n";
            cout << "    -> Helps identify exposed services.\n\n";

            cout << YELLOW
                 << "[2] TARGET SERVICE DETECTION"
                 << RESET << endl;

            cout << "    -> Detects running services on common ports.\n";
            cout << "    -> Displays protocol and version information.\n\n";

            cout << YELLOW
                 << "[3] BANNER GRABBING & OS DETECTION"
                 << RESET << endl;

            cout << "    -> Captures service banners.\n";
            cout << "    -> Attempts operating system fingerprinting.\n\n";

            cout << YELLOW
                 << "[4] REPORTS & LOG ANALYTICS"
                 << RESET << endl;

            cout << "    -> Stores scan results in JSON logs.\n";
            cout << "    -> Provides filtering and analytics dashboard.\n\n";

            cout << BOLD << CYAN
                 << "[+] SUPPORTED TARGET INPUTS"
                 << RESET << "\n\n";

            cout << "    • Domain Names\n";
            cout << "    • URLs\n";
            cout << "    • IPv4 Addresses\n\n";

            cout << BOLD << RED
                 << "[!] ETHICAL WARNING"
                 << RESET << "\n\n";

            cout << "Use NetProbe only on authorized systems.\n";
            cout << "Unauthorized scanning may violate laws.\n\n";

            cout << MAGENTA
                 << "========================================================\n"
                 << RESET;

            cout << "\nPress ENTER to continue...";

            cin.ignore(1000, '\n');
            cin.get();
        }

        // ==========================================================
        // POLYMORPHIC FUNCTION #2
        // ==========================================================

        void DevelopmentTeam() override {

            system("clear");

            displayBanner();

            cout << BOLD << GREEN
                 << "[+] DEVELOPMENT TEAM"
                 << RESET << "\n\n";

                        cout << "Project Name : NetProbe\n";
            cout << "Language     : C++\n";
            cout << "Architecture : Modular Object Oriented Security Framework\n";
            cout << "Networking   : POSIX Socket Programming\n";
            cout << "Github Repo  :" << BOLD << CYAN << " https://github.com/MuhammadTalha15/NetProbe.git\n\n" << RESET;
            cout<<endl;

            cout<<"[+] Muhammad Talha (Port Scanning Engine, Host Resolving and Interface Designing)"<<endl;
            cout<<"[+] Muhammad Awais Habib (Traget Service Detection)"<<endl;
            cout<<"[+] Muhammad Saif Ali (Banner Grabbing and OS Detection)"<<endl;
            cout<<"[+] Hassan Murtaza (Report Generation and Log Generation)"<<endl;
            cout<<endl;

            cout << BOLD << CYAN
                 << "[+] CORE MODULES"
                 << RESET << "\n\n";

            cout << "    • Port Scanner Engine\n";
            cout << "    • Service Detection System\n";
            cout << "    • Banner Grabbing Module\n";
            cout << "    • Host Resolver\n";
            cout << "    • JSON Logging Manager\n";
            cout << "    • Analytics Dashboard\n\n";

            cout << BOLD << MAGENTA
                 << "\"Reconnaissance Begins With Visibility\""
                 << RESET << "\n\n";

            cout << MAGENTA
                 << "========================================================\n"
                 << RESET;

            cout << "\nPress ENTER to continue...";

            cin.ignore(1000, '\n');
            cin.get();
        }
};

#endif