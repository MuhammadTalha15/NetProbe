#include <iostream>
#include <string>

using namespace std;

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