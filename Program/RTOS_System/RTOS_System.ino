#include <NilRTOS.h>
#include <NilSerial.h>

#define Serial NilSerial

//A semaphore with just one slot to be accessed.
SEMAPHORE_DECL(sem, 1);

void CRITICAL_REGION(int led, int computingTime){

}

NIL_WORKING_AREA(waRMachine1, 128);

NIL_THREAD(RMachine1, arg){
  
}

NIL_WORKING_AREA(waRMachine2, 128);

NIL_THREAD(RMachine2, arg){

}

NIL_THREADS_TABLE_BEGIN()
NIL_THREADS_TABLE_ENTRY("RMachine1",RMachine1,NULL,waRMachine1,sizeof(waRMachine1))
NIL_THREADS_TABLE_ENTRY("RMachine2",RMachine2,NULL,waRMachine2,sizeof(waRMachine2))
NIL_THREADS_TABLE_END()

void setup(){
  
  //Remember, never use as outputs doors 0 and 1
  Serial.begin(9600);
  
  nilSysBegin();
  
}

void loop(){
  //There won't have anything in here!
}
