#ifndef HOSTRESOLVER_H
#define HOSTRESOLVER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class HostResolver{
    public:

        string resolveToIP(const string& targetURL);
        string extractHostname(const string& input);
};

#endif