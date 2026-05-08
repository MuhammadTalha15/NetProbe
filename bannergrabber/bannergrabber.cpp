
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <cstring>

#include "../headers/banner.h"

bool BannerGrabber::isPortOpen(string ip, int port){

    int sock;

    struct sockaddr_in target;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
        return false;

    target.sin_family = AF_INET;
    target.sin_port = htons(port);

    inet_pton(AF_INET,
              ip.c_str(),
              &target.sin_addr);

    bool connected =
        connect(sock,
                (struct sockaddr*)&target,
                sizeof(target)) >= 0;

    close(sock);

    return connected;
}

string BannerGrabber::grabBanner(string ip, int port){

    int sock;

    struct sockaddr_in target;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
        return "Socket Error";

    target.sin_family = AF_INET;
    target.sin_port = htons(port);

    inet_pton(AF_INET,
              ip.c_str(),
              &target.sin_addr);

    if (connect(sock,
                (struct sockaddr*)&target,
                sizeof(target)) < 0){

        close(sock);

        return "Connection Failed";
    }

    struct timeval tv;

    tv.tv_sec = 2;
    tv.tv_usec = 0;

    setsockopt(sock,
               SOL_SOCKET,
               SO_RCVTIMEO,
               (const char*)&tv,
               sizeof tv);

    // HTTP request
    if (port == 80 || port == 8080){

        string request =
            "GET / HTTP/1.1\r\nHost: test\r\n\r\n";

        send(sock,
             request.c_str(),
             request.size(),
             0);
    }

    char buffer[255];

    int bytes =
        recv(sock,
             buffer,
             sizeof(buffer)-1,
             0);

    if (bytes > 0){

        buffer[bytes] = '\0';

        close(sock);

        return string(buffer);
    }

    close(sock);

    return "No Banner";
}

string BannerGrabber::detectOS(string banner){

    if (banner.find("Ubuntu") != string::npos)
        return "Linux Ubuntu";

    if (banner.find("Debian") != string::npos)
        return "Linux Debian";

    if (banner.find("Apache") != string::npos)
        return "Likely Linux";

    if (banner.find("nginx") != string::npos)
        return "Likely Linux";

    if (banner.find("Microsoft") != string::npos)
        return "Windows";

    if (banner.find("IIS") != string::npos)
        return "Windows Server";

    return "Unknown OS";
}
