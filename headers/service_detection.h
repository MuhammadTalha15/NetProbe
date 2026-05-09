#ifndef SERVICE_DETECTION_H
#define SERVICE_DETECTION_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct ServiceInfo {

    int port;

    string serviceName;

    string protocol;

    string version;

    map<string, string> metadata;
};

class ServiceDetection {

private:

    string targetIP;

public:

    ServiceDetection(const string& ip);

    ServiceInfo detectService(int port);

    vector<ServiceInfo> detectMultipleServices(
        const vector<int>& ports
    );

private:

    bool connectToPort(
        int& sock,
        int port
    );

    string identifyService(
        int port
    );

    string detectProtocol(
        int port
    );

    string extractVersion(
        int port
    );
};

#endif
