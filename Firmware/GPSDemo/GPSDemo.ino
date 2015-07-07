#include "SevSeg.h"
#include <stdlib.h>
#include <TinyGPS.h>

/* 
 */

#define SETTINGSBUTTON 10
#define DOWNBUTTON 11
#define UPBUTTON 12
#define BUZZER 13

SevSeg myDisplay;
TinyGPS gps;

void display_begin(void);
static void smartdelay(unsigned long ms);

char charVal[5]; //temporarily holds data from vals 

int variance = 2;
float SetSpeed = 55;


void setup()
{
  display_begin();
  Serial.begin(9600);
  pinMode(SETTINGSBUTTON, INPUT_PULLUP);
  pinMode(UPBUTTON, INPUT_PULLUP);
  pinMode(DOWNBUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

}

void loop()
{
  
    smartdelay(1000); 
    
float flat, flon;
unsigned long fix_age; // returns +- latitude/longitude in degrees
gps.f_get_position(&flat, &flon, &fix_age);
if (fix_age == TinyGPS::GPS_INVALID_AGE){
  Serial.println("No fix detected");
   charVal[0] = '-'; 
   charVal[1] = '-';
   charVal[2] = '-';
   charVal[3] = '-';
}
  else if (fix_age > 1000){
    Serial.println("Warning: possible stale data!");
   charVal[0] = '_'; 
   charVal[1] = '_';
   charVal[2] = '_';
   charVal[3] = '_';
}
  else{
    float rate = gps.f_speed_kmph();
    if(rate < 2) rate = 0;
    Serial.print(rate);
    dtostrf((rate*10), 4, 0, charVal);
    delay(10);
    
    if(SetSpeed > 0){
      if(rate + variance <= SetSpeed)
        {
          //too slow
          tone(BUZZER, 110, 100);
        }
    
        if(rate - variance >= SetSpeed)
        {
          tone(BUZZER, 440, 100);
         //TOO FAST 
        }
    }
    
    Serial.println("Data is current.");
  }  
}


  

