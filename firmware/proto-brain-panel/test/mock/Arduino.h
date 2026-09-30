#pragma once
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#define INPUT 0
#define OUTPUT 1
#define LOW 0
#define HIGH 1
#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define F(x) x
void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int analogRead(uint8_t);
unsigned long millis();
void delay(unsigned long);
struct SerialMock { void begin(long){} int available(); int read(); void print(const char*){} void println(const char*){} void println(int){} void print(int){} };
extern SerialMock Serial;
