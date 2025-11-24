#ifndef APPNETWORK_H
#define APPNETWORK_H

#include <WiFi.h>

class AppWiFi {
public:
    void init();
    void update();
};

extern AppWiFi network;

#endif