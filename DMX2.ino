//rock me amadeus - falco
//177 bpm, 4/4 takt

//adresse 9 und 23 moving heads
//adresse 1 und 37 scheinwerfer

#include "DmxSimple.h"

#define MOV1 9
#define MOV2 23
#define LIGHT1 1
#define LIGHT2 37

int beatdauer = round(60000 / 177); // ms pro Beat

int repeat = 2;

void light(int channel, int value) {
  DmxSimple.write(LIGHT1+channel-1, value);
  DmxSimple.write(LIGHT2+channel-1, value);
}

void mov(int channel, int value) {
  DmxSimple.write(MOV1+channel-1, value);
  DmxSimple.write(MOV2+channel-1, value);
}

void setup() {
  DmxSimple.usePin(3);
  light(1, 255);
  mov(6, 255);
  mov(3, 100);
}

void loop() {
if (millis() < 30000) {
  if(millis() < 15500 || millis() > 24000) {
  //aufblinken scheinwerfer 1 rot       (auf die 1)
    DmxSimple.write(LIGHT1+1, 200);
    if (millis() > 24000) {
      mov(9, 0);
      light(4, 200)
    } 
    delay(beatdauer);
    DmxSimple.write(LIGHT1+1, 0);
    
    //aufblinken scheinwerfer 2 rot     (auf die 2)
    DmxSimple.write(LIGHT2+1, 200);
    delay(beatdauer);
    DmxSimple.write(LIGHT2+1, 0);

    //aufblinken moving                 (auf die 3)
    if (millis() > 24000) {
      light(4, 0);

      // Aufblinken moving
      mov(9, 255);
    }
    mov(7, 255);
    delay(beatdauer);
    mov(7, 0)
    delay(beatdauer);
  }
  
  // von ca 00:05 bis 00:16 - moving heads sollen sich ein bisschen im Kreis drehen
  
  if (millis() >= 5000 && millis() < 15500) {
    mov(3, 40);
    mov(1, 250)
    mov(9, 250)
  }
  // ca 00:15 EH EH (blau)
  if (millis() >= 15500) {
    while (repeat > 0) {
      mov(1, 0)
      light(4, 250);
      mov(9, 250);
      delay(beatdauer);
      light(4, 0);
      mov(9, 0)
      delay(100); //muss wahrscheinlich angepasst werden
      repeat--;
    }
  }
  
}
}
