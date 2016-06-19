#include <NilRTOS.h>
#include <NilSerial.h>
#include <NilTimer1.h>

#define Serial NilSerial

const uint8_t yellowLed = 8;
const uint8_t greenLed = 10;
const uint8_t redLed = 12;

const uint8_t semRedLed = 7;
const uint8_t semGreenLed = 5; 

//A semaphore with just one slot to be accessed.
SEMAPHORE_DECL(sem, 1);

void CONTROL_SEM_LEDS(int signal){
  if(signal == 1){
    digitalWrite(semRedLed,LOW);
    digitalWrite(semGreenLed,HIGH);
  }else if(signal == 0){
    digitalWrite(semRedLed,HIGH);
    digitalWrite(semGreenLed,LOW);
  }
}

int CRITICAL_REGION(int led, int computingTime){
  //This is the place where the thrid running machine and fullfil the bottle
  
  //This is an aperiodic activity and has 10 seconds for computing time
  int CT = 10000;
  
  CONTROL_SEM_LEDS(0);
  
  digitalWrite(led,HIGH);
  Serial.println("Moving running machine");
  nilThdSleepMilliseconds(computingTime);
  digitalWrite(led,LOW);
  Serial.println("Stoped running machine");
  digitalWrite(redLed,HIGH);
  Serial.println("Started fufilling the bottle");
  nilThdSleepMilliseconds(10000);
  digitalWrite(redLed,LOW);
  Serial.println("Finished fulfilling the bottle\nMoved the third running machine");
  
  nilSemSignal(&sem);
  CONTROL_SEM_LEDS(1);
  return CT;
}

NIL_WORKING_AREA(waRMachine1, 128);

NIL_THREAD(RMachine1, arg){
  
  uint32_t P = 30000,D = P, CT = 5000;
  
  while(true){
  
    msg_t test = nilSemWaitTimeout(&sem,P);
    
    if(test == NIL_MSG_OK){
      int waitCR = CRITICAL_REGION(yellowLed,CT);
      nilThdSleepMilliseconds(P - CT - waitCR);
    }
  
  }
  
}

NIL_WORKING_AREA(waRMachine2, 128);

NIL_THREAD(RMachine2, arg){
  uint32_t P = 30000,D = P, CT = 5000;
  
  while(true){
  
    msg_t test = nilSemWaitTimeout(&sem,P);
    
    if(test == NIL_MSG_OK){
      CRITICAL_REGION(greenLed,CT);
      nilThdSleepMilliseconds(P-CT);
    }
  
  }
}

NIL_THREADS_TABLE_BEGIN()
NIL_THREADS_TABLE_ENTRY("RMachine1",RMachine1,NULL,waRMachine1,sizeof(waRMachine1))
NIL_THREADS_TABLE_ENTRY("RMachine2",RMachine2,NULL,waRMachine2,sizeof(waRMachine2))
NIL_THREADS_TABLE_END()

void setup(){
  
  pinMode(yellowLed,OUTPUT);
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(semRedLed,OUTPUT);
  pinMode(semGreenLed,OUTPUT);
  
  //Remember, never use as outputs doors 0 and 1
  Serial.begin(9600);
  
  nilSysBegin();
  
}

void loop(){
  //There won't have anything in here!
}
