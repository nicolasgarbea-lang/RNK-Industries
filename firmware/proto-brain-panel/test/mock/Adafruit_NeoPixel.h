#pragma once
#include "Arduino.h"
#define NEO_GRB 0
#define NEO_KHZ800 0
extern int g_showCount[20]; extern int g_pinMode[20]; extern int g_pinLevel[20]; extern int g_showUnpowered;
bool slotPowered(uint8_t dataPin);
class Adafruit_NeoPixel { uint8_t pin; public:
 Adafruit_NeoPixel(uint16_t,uint8_t p,int):pin(p){}
 void begin(){ pinMode(pin,OUTPUT); digitalWrite(pin,LOW);}
 void setBrightness(uint8_t){} void setPixelColor(uint16_t,uint32_t){}
 uint32_t Color(uint8_t,uint8_t,uint8_t){return 0;}
 void clear(){}
 void show(){ if(g_pinMode[pin]!=OUTPUT) {printf("FAIL show() with pin %d not OUTPUT\n",pin);} g_showCount[pin]++; if(!slotPowered(pin)) g_showUnpowered++; }
};
