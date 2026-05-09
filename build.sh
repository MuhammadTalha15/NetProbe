#!/bin/bash

# g++ main.cpp portscanner/*.cpp utilities/*.cpp -o netprobe
g++ main.cpp ./portscanner/portScanner.cpp ./portscanner/hostresolver.cpp ./bannergrabber/bannergrabber.cpp ./logManager/logManager.cpp ./serviceDetection/serviceDetection.cpp -o Netprobe

echo "Build Successful! Program Compiled Successfully"
echo "Run ./Netprobe"

