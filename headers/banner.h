#ifndef BANNERGRABBER_H
#define BANNERGRABBER_H

#include <iostream>
#include <string>

using namespace std;

class BannerGrabber {

public:

    bool isPortOpen(string ip, int port);

    string grabBanner(string ip, int port);

    string detectOS(string banner);
};

#endif