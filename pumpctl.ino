 /*
  * Simple Pump control and water level Management using ATtiny 85
  * Author:Aaryadev
  * PIN 0,1,2 (PB0,PB1,PB2) will be connected Sensors
  * PIN  Sump Level sensor, PIN 1 Waterlevel Low Sensor,  PIN 2 Waterlevel High Sensor
  * PIN 3,4 Will be output
  */

#define SUMP 0 // sump
#define WLL  1//Water level LOW
#define WLH 2 // Water level HIGH
#define LED 3 // LED
#define PUMPSW 4// PUMP Switch
//config
int maxruntime = 40000;//8 min
int resettime = 14500000;// 4H
bool pump_status = false;
int  runtime =0;
  

//restart the MC
void(* resetFunc) (void) = 0;

//make led blink fast 
void ledblink(){
  for(int i = 1;i<50;i++){
    if ( (i % 2) == 0){
      digitalWrite(LED, LOW);
    }else{
      digitalWrite(LED, HIGH);
    }
    delay(50);
  }
  runtime = runtime +125;
}

void pumpoff(){
  pump_status = false;
  digitalWrite(PUMPSW, LOW);
}
void pumpon(){
  pump_status = true;
  digitalWrite(PUMPSW, HIGH);
}

//if some error stop pump and Fast blink
void errorhault(){
  //kill pump
  pumpoff();
  while(1){
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(150);
  }

}



void setup(){
  //Sensor INPUT
  pinMode(SUMP,INPUT);
  pinMode(WLL,INPUT);//Water Low
  pinMode(WLH,INPUT);//water High
  //OUTPUT
  pinMode(LED,OUTPUT); // Status LED (amber)
  pinMode(PUMPSW,OUTPUT); // Pump RELAY or SSR
  digitalWrite(PUMPSW, LOW); // write low
  
  digitalWrite(LED, HIGH);
  delay(2000);
  digitalWrite(LED, LOW);
}

void loop() {
// if off for long time restart it
if(!pump_status){
  if(resettime < millis()){
    resetFunc();
  }
}
  //read sensor
  int sump =  digitalRead(SUMP);
  int wl = digitalRead(WLL);
  int wh = digitalRead(WLH);
  
  //LOGIC 
  // low sump water level
  if(pump_status){ //pump is on
    if(sump == 0){
      pumpoff();
    }  
    //if Tank is full turn off pump
    if(wl == 1 && wh == 1){
      pumpoff();
    }

    if(wl == 0 && wh == 1){
      errorhault();   // sensor issue
    }


    
  }else{ // PUMP IS OFF

    if(wl == 0 && wh == 0){ //both are low
      pumpon();
    }
  }

  if(pump_status){
    ledblink();
    if(maxruntime > runtime){
      errorhault();   // Long run issue
    }
    
  }else{
    delay(2000);
  }


  
  
}
