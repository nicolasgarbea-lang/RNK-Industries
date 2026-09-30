#pragma once
#include <string.h>
struct EEPROMMock { uint8_t mem[1024]; EEPROMMock(){memset(mem,0xFF,sizeof mem);}
 template<class T> void put(int a,const T&v){memcpy(mem+a,&v,sizeof(T));}
 template<class T> void get(int a,T&v){memcpy(&v,mem+a,sizeof(T));} };
extern EEPROMMock EEPROM;
