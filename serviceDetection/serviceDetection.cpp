#include "../headers/service_detection.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <regex>
#include <cstring>

ServiceDetection::ServiceDetection(
    const string& ip
) {
    targetIP = ip;
}

bool ServiceDetection::connectToPort(
    int& sock,
    int port
) {

    sock = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if(sock < 0)
        return false;

    sockaddr_in target{};

    target.sin_family = AF_INET;

    target.sin_port = htons(port);

    inet_pton(
        AF_INET,
        targetIP.c_str(),
        &target.sin_addr
    );

    struct timeval timeout;

    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    setsockopt(
        sock,
        SOL_SOCKET,
        SO_RCVTIMEO,
        &timeout,
        sizeof(timeout)
    );

    int status =
        connect(
            sock,
            (sockaddr*)&target,
            sizeof(target)
        );

    return status >= 0;
}

string ServiceDetection::identifyService(
    int port
) {

    map<int, string> commonPorts = {

        {21, "FTP"},
        {22, "SSH"},
        {25, "SMTP"},
        {53, "DNS"},
        {80, "HTTP"},
        {110, "POP3"},
        {143, "IMAP"},
        {443, "HTTPS"},
        {445, "SMB"},
        {3306, "MySQL"},
        {5432, "PostgreSQL"},
        {6379, "Redis"},
        {8080, "HTTP-Proxy"}
    };

    if(commonPorts.count(port))
        return commonPorts[port];

    return "Unknown";
}

string ServiceDetection::detectProtocol(
    int port
) {

    map<int, string> protocols = {

        {21, "FTP"},
        {22, "SSH"},
        {25, "SMTP"},
        {53, "DNS"},
        {80, "HTTP"},
        {110, "POP3"},
        {143, "IMAP"},
        {443, "HTTPS"},
        {445, "SMB"},
        {3306, "MYSQL"},
        {5432, "POSTGRESQL"},
        {6379, "REDIS"},
        {8080, "HTTP"}
    };

    if(protocols.count(port))
        return protocols[port];

    return "UNKNOWN";
}

string ServiceDetection::extractVersion(
    int port
) {

    map<int, string> versions = {

        {21, "FTP Service"},
        {22, "OpenSSH"},
        {25, "SMTP Service"},
        {53, "DNS Resolver"},
        {80, "HTTP Service"},
        {110, "POP3 Service"},
        {143, "IMAP Service"},
        {443, "HTTPS Service"},
        {445, "SMB Service"},
        {3306, "MySQL Service"},
        {5432, "PostgreSQL Service"},
        {6379, "Redis Service"},
        {8080, "HTTP Proxy"}
    };

    if(versions.count(port))
        return versions[port];

    return "Unknown";
}

ServiceInfo ServiceDetection::detectService(
    int port
) {

    ServiceInfo info;

    info.port = port;

    int sock;

    bool connected =
        connectToPort(
            sock,
            port
        );

    if(!connected) {

        info.serviceName =
            "Closed";

        return info;
    }

    info.serviceName =
        identifyService(port);

    info.protocol =
        detectProtocol(port);

    info.version =
        extractVersion(port);

    close(sock);

    return info;
}

vector<ServiceInfo>
ServiceDetection::detectMultipleServices(
    const vector<int>& ports
) {

    vector<ServiceInfo> results;

    for(int port : ports) {

        ServiceInfo result =
            detectService(port);

        if(
            result.serviceName
            != "Closed"
        ) {

            results.push_back(result);
        }
    }

    return results;
}
