#ifndef TOUCHDRV_H
#define TOUCHDRV_H

#include <XPT2046_Touchscreen.h>
#include <SPI.h>

// PINES DE LA PLACA CYD
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

class TouchDriver {
public:
    void init();
    bool getTouch(uint16_t *x, uint16_t *y);
};

extern SPIClass mySpi;
extern XPT2046_Touchscreen ts;
extern TouchDriver touch;

#endif