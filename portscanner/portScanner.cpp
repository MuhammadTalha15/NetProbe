#include "../headers/portScanner.h"

// LIBRAIRES AND HEADER FILES FOR PROJECT

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>

PortScanner::PortScanner(const string& ip, int start, int end, int time):targetIP(ip),startPort(start),endPort(end),timout_in_milliseconds(time) {}

void PortScanner::setTarget(const string& ip){
    targetIP = ip;
}

void PortScanner::setRange(int start, int end){
    startPort = start;
    endPort = end;
}

bool PortScanner::startSinglePortScan(int sPort){
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) return false;

    // Non Blocking Socket
    fcntl(sock, F_SETFL, O_NONBLOCK);

    sockaddr_in target{};
    target.sin_family = AF_INET;
    target.sin_port = htons(sPort);
    inet_pton(AF_INET, targetIP.c_str(), &target.sin_addr);

    connect(sock, (sockaddr*)&target, sizeof(target));

    fd_set fdset;
    FD_ZERO(&fdset);
    FD_SET(sock, &fdset);

    timeval tv{};
    tv.tv_sec = timout_in_milliseconds / 1000;
    tv.tv_usec = (timout_in_milliseconds % 1000) * 1000;

    int result = select(sock + 1, nullptr, &fdset, nullptr, &tv);

    if (result > 0) {
        int so_error;
        socklen_t len = sizeof so_error;
        getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);
        close(sock);
        return so_error == 0;
    }

    close(sock);
    return false;
    
}

vector<PortResult> PortScanner::scanAllPorts() {
    vector<PortResult> results;

    for (int port = startPort; port <= endPort; port++) {
        bool status = startSinglePortScan(port);
        results.push_back({port, status});
    }

    return results;
}