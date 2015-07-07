void display_begin(){
  
  int displayType = COMMON_ANODE; //Your display is either common cathode or common anode
  
  int digit1 = 16; // DIG1 = A2/16 (PC2)
  int digit2 = 17; // DIG2 = A3/17 (PC3)
  int digit3 = 3;  // DIG3 = D3 (PD3)
  int digit4 = 4;  // DIG4 = D4 (PD4)

  //Declare what pins are connected to the segments
  int segA = 8;  // A = D8 (PB0)
  int segB = 14; // B = A0 (PC0)
  int segC = 6;  // C = D6 (PD6), shares a pin with colon cathode
  int segD = A1; // D = A1 (PC1)
  int segE = 23; // E = PB7 (not a standard Arduino pin: Must add PB7 as digital pin 23 to pins_arduino.h)
  int segF = 7;  // F = D7 (PD6), shares a pin with apostrophe cathode
  int segG = 5;  // G = D5 (PD5)
  int segDP= 22; //DP = PB6 (not a standard Arduino pin: Must add PB6 as digital pin 22 to pins_arduino.h)

/*  int digitColon = 2; // COL-A = D2 (PD2) (anode of colon)
  int segmentColon = 6; // COL-C = D6 (PD6) (cathode of colon), shares a pin with C
  int digitApostrophe = 9; // APOS-A = D9 (PB1) (anode of apostrophe)
  int segmentApostrophe = 7; // APOS-C = D7 (PD7) (cathode of apostrophe), shares a pin with F
*/

  int numberOfDigits = 4; //Do you have a 1, 2 or 4 digit display?

  myDisplay.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  
  myDisplay.SetBrightness(100); //Set the display to 100% brightness level
  
}

void checkSpeedSettings(){
 while(!digitalRead(SETTINGSBUTTON)){
   charVal[0] = '!';
   charVal[1] = '!';
   charVal[2] = '!';
   charVal[3] = '!';

    dtostrf((SetSpeed*10), 4, 0, charVal);
   myDisplay.DisplayString(charVal, 4); //(numberToDisplay, decimal point location)
   if(!digitalRead(UPBUTTON)){
      SetSpeed = SetSpeed + 0.1; 
      tone(BUZZER, 600, 5);

   };
   if(!digitalRead(DOWNBUTTON)){
      SetSpeed = SetSpeed - 0.1; 
      if(SetSpeed <= 0)SetSpeed = 0;
      tone(BUZZER, 500, 5);
   }
   delay(10);
 }
}


static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial.available())
      gps.encode(Serial.read());
      myDisplay.DisplayString(charVal, 4); //(numberToDisplay, decimal point location)   
      checkSpeedSettings();
  } while (millis() - start < ms);
}
