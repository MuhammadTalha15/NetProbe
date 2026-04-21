#ifndef PORTSCANNER_H
#define PORTSCANNER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// STRUCTURE FOR PORT Results

struct PortResult{
    int port;
    bool open;
};

class PortScanner {
    private:
        string targetIP;
        int startPort;
        int endPort;
        int timout_in_milliseconds;

    public:

        PortScanner(const string & ip, int start, int end, int time = 500);

        void setTarget(const string& ip);
        void setRange(int start, int end);

        bool startSignlePortScan(int sPort);

        vector <PortResult> scanAllPorts();
};

#endif