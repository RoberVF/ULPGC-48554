#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <ESPAsyncWebServer.h>

class WebController {
public:
    void init();
};

extern WebController controller;

#endif