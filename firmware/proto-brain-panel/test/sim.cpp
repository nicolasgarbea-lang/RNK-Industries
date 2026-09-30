#include <stdlib.h>
#include "Arduino.h"
#include "EEPROM.h"
#include "../src/config.h"
SerialMock Serial; EEPROMMock EEPROM;
int g_showCount[20], g_pinMode[20], g_pinLevel[20], g_showUnpowered;
unsigned long g_ms; int g_serialChar=-1;
int SerialMock::available(){return g_serialChar>=0;} int SerialMock::read(){int c=g_serialChar; g_serialChar=-1; return c;}
unsigned long millis(){return g_ms;} void delay(unsigned long d){g_ms+=d;}
void pinMode(uint8_t p,uint8_t m){g_pinMode[p]=m;}
void digitalWrite(uint8_t p,uint8_t v){g_pinLevel[p]=v;}
// ---- hardware model
enum SlotHw {EMPTY, MODULE, SHORT_}; SlotHw hwA=EMPTY, hwB=EMPTY;
enum EdgeHw {E_NONE, E_NEIGH, E_SHORT, E_TOOL_NOSHORT}; EdgeHw edgeHw=E_NONE;
double g_neighC=220e-6; unsigned long preStart=0; bool prevPre=false;
bool slotPowered(uint8_t dp){ return (dp==PIN_SLOT_A_DATA_DRV)? g_pinLevel[PIN_SLOT_A_EN_DRV] : g_pinLevel[PIN_SLOT_B_EN_DRV]; }
static int idCounts(SlotHw s, uint8_t dataPin){
  if (g_pinMode[dataPin]==OUTPUT && g_pinLevel[dataPin]==LOW) return 0; // driver pulls node low through 390 ohm
  double v = s==EMPTY?5.0 : s==SHORT_?0.0 : 5.0*10.0/(10.0+100.0);
  return (int)(v/5.0*1023+0.5);
}
double edgeV(){
  if (g_pinLevel[PIN_EDGE_EN_DRV]) return edgeHw==E_SHORT?0:20;
  if (!g_pinLevel[PIN_EDGE_PRE_EN_DRV]) return edgeHw==E_NEIGH? 0 : 0;
  double t=(g_ms-preStart)/1000.0;
  switch(edgeHw){ case E_NONE: case E_TOOL_NOSHORT: return 20; case E_SHORT: return 0.0;
    case E_NEIGH: return 20*(1-exp(-t/(470*g_neighC))); }
  return 0;
}
int analogRead(uint8_t p){
  if (p==PIN_SLOT_A_ID) return idCounts(hwA,PIN_SLOT_A_DATA_DRV);
  if (p==PIN_SLOT_B_ID) return idCounts(hwB,PIN_SLOT_B_DATA_DRV);
  if (p==PIN_EDGE_R_HALL) return 512 + ((edgeHw!=E_NONE)?80:0);
  if (p==PIN_EDGE_R_SENSE){ double v=edgeV()*22.0/122.0; return (int)(v/5.0*1023); }
  return 0;
}
void setup(); void loop();
int fails=0;
#define CHECK(c,msg) do{ if(!(c)){printf("  FAIL: %s (t=%lu)\n",msg,g_ms); fails++;} else printf("  ok: %s\n",msg);}while(0)
// run for ms, return time EN first went high (relative) or -1; also track max time slot powered while hw unsafe
long runUntil(unsigned long dur, uint8_t enPin, int want, unsigned long step=1){
  unsigned long start=g_ms;
  while(g_ms-start<dur){ bool pre=g_pinLevel[PIN_EDGE_PRE_EN_DRV]; if(pre&&!prevPre) preStart=g_ms; prevPre=pre;
    loop(); if(g_pinLevel[enPin]==want) return (long)(g_ms-start); g_ms+=step; }
  return -1;
}
void run(unsigned long dur){ runUntil(dur,0,99); }
int main(int argc,char**){
  bool calibrated = argc>1 && !getenv("NOCAL");
  unsigned long t0 = argc>2 ? 0xFFFFF000UL : 1000; g_ms=t0;
  printf("== boot (calibrated=%d, t0=%lu)\n",calibrated,t0);
  if(argc>3){ edgeHw=E_NEIGH; g_neighC=atof(getenv("NC")?getenv("NC"):"220e-6"); }
  if(calibrated){ struct {uint16_t m; int16_t v;} c{CAL_MAGIC,512}; EEPROM.put(0,c);}  
  setup();
  if(argc>3){ long tt=runUntil(3000,PIN_EDGE_EN_DRV,HIGH); printf("  neighbour at boot: edge ON after %ld ms\n",tt); CHECK(tt>=0,"neighbour attached at boot gets powered"); return fails; }
  CHECK(!g_pinLevel[PIN_SLOT_A_EN_DRV]&&!g_pinLevel[PIN_SLOT_B_EN_DRV]&&!g_pinLevel[PIN_EDGE_EN_DRV]&&!g_pinLevel[PIN_EDGE_PRE_EN_DRV],"all outputs off after setup");
  CHECK(g_showUnpowered==0,"no LED data sent to unpowered strips at boot");
  run(1000); CHECK(!g_pinLevel[PIN_SLOT_A_EN_DRV],"empty slot A stays off");
  printf("== slot A: insert LED module\n"); hwA=MODULE;
  long t=runUntil(1000,PIN_SLOT_A_EN_DRV,HIGH); printf("  ON after %ld ms\n",t); CHECK(t>=200 && t<=300,"slot A turns on after 200-300 ms");
  run(500); CHECK(g_showCount[PIN_SLOT_A_DATA_DRV]>5,"LED animation running");
  CHECK(g_pinLevel[PIN_SLOT_A_EN_DRV],"slot stays on while module present (ID re-read between frames)");
  printf("== slot A: remove module\n"); hwA=EMPTY;
  t=runUntil(1000,PIN_SLOT_A_EN_DRV,LOW); printf("  OFF after %ld ms\n",t); CHECK(t>=0 && t<=ANIM_INTERVAL_MS+1,"slot A off within one frame");
  printf("== slot A: screwdriver short DATA-GND\n"); hwA=SHORT_;
  t=runUntil(3000,PIN_SLOT_A_EN_DRV,HIGH); CHECK(t<0,"slot never turns on with a short");
  printf("== slot A: short removed, module placed\n"); hwA=MODULE;
  t=runUntil(3000,PIN_SLOT_A_EN_DRV,HIGH); printf("  ON after %ld ms\n",t); CHECK(t>=200 && t<=2300,"slot turns on after lockout expires");
  printf("== slot A: short while ON\n"); hwA=SHORT_;
  t=runUntil(200,PIN_SLOT_A_EN_DRV,LOW); CHECK(t>=0&&t<=ANIM_INTERVAL_MS+1,"slot cut within one frame on short");
  hwA=EMPTY; run(2500);
  CHECK(g_showUnpowered==0,"never sent LED data to an unpowered strip");
  CHECK(!g_pinLevel[PIN_SLOT_B_EN_DRV],"slot B untouched (empty)");
  printf("== edge: tool on magnet, touching nothing (Hall over, open)\n"); edgeHw=E_TOOL_NOSHORT;
  t=runUntil(3000,PIN_EDGE_EN_DRV,HIGH); CHECK(t<0,"edge stays OFF when nothing is connected");
  printf("== edge: tool shorting the pins\n"); edgeHw=E_SHORT;
  t=runUntil(3000,PIN_EDGE_EN_DRV,HIGH); CHECK(t<0,"edge stays OFF on short");
  printf("== edge: real neighbour panel\n"); edgeHw=E_NEIGH;
  t=runUntil(4000,PIN_EDGE_EN_DRV,HIGH); printf("  ON after %ld ms\n",t); CHECK(t>=0,"edge turns on for a real neighbour");
  CHECK(!g_pinLevel[PIN_EDGE_PRE_EN_DRV],"pre-test switch opened after main switch closed");
  printf("== edge: neighbour removed\n"); edgeHw=E_NONE;
  t=runUntil(500,PIN_EDGE_EN_DRV,LOW); CHECK(t>=0,"edge turns off when neighbour removed");
  printf("RESULT: %s (%d failures)\n", fails?"FAILED":"PASSED", fails);
  return fails?1:0;
}
