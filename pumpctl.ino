 /*
  * Simple Pump control and water level Management using ATtiny 85
  * Author:Aaryadev
  * PIN 0,1,2 (PB0,PB1,PB2) will be connected Sensors
  * PIN  Sump Level sensor, PIN 1 Waterlevel Low Sensor,  PIN 2 Waterlevel High Sensor
  * PIN 3,4 Will be output
  */
  

void setup(){
  //Sensor INPUT
  pinMode(0,INPUT); //sump
  pinMode(1,INPUT);//Water Low
  pinMode(2,INPUT);//water High
  //OUTPUT
  pinMode(3,OUTPUT); // Status LED (amber)
  pinMode(4,OUTPUT); // Pump RELAY or SSR
  
}

void loop() {

   
   
}
