#include <iostream>
#include <vector>
#include <string>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>

#include "../headers/hostresolver.h"

using namespace std;

        string HostResolver::extractHostname(const string& input) {
            string targetURL = input;

            if (targetURL.find("http:/") == 0){
                targetURL = targetURL.substr(7);
            }
            else if (targetURL.find("https://") == 0){
                targetURL = targetURL.substr(8);
            }

            size_t slash = targetURL.find("/");

            if (slash != string::npos){
                targetURL = targetURL.substr(0, slash);
            }
            
            return targetURL;
        }

        string HostResolver::resolveToIP(const string& targetURL) {
            addrinfo hints{}, *res;

            hints.ai_family = AF_INET;

            int status = getaddrinfo(targetURL.c_str(), nullptr, &hints, &res);

            if (status != 0) {
                cout << "DNS Error: " << gai_strerror(status) << endl;
                return "";
            }

            char ip[INET_ADDRSTRLEN];
            sockaddr_in* addr = (sockaddr_in*)res->ai_addr;

            inet_ntop(AF_INET, &(addr->sin_addr), ip, sizeof(ip));

            freeaddrinfo(res);
            return string(ip);
        }
