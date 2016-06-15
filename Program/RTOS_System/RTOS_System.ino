#include <NilRTOS.h>
#include <NilSerial.h>

#define Serial NilSerial

void setup(){
  
  //Remember, never use as outputs doors 0 and 1
  Serial.begin(9600);
  
}

void loop(){
  //There won't have anything in here!
}
