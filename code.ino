#include "LedControl.h"
LedControl lc = LedControl(11,13,10,4); // DIN,CLK,CS 
int button[] = {2,3};
int carrow= 0;

int LastButtonState;
unsigned long timer;
int ButtonState=0;

void setup() {
  pinMode(button[0], INPUT);
  pinMode(button[1], INPUT);
  Serial.begin(9600);

  for(int address=0; address<4; address++){
    lc.shutdown(address, false);
    lc.setIntensity(address, 8);
    lc.clearDisplay(address);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Debounce
  int reading = digitalRead(button[1]) ;
  if(reading != LastButtonState){
    timer = millis();
  }
  if((millis() - timer)> 50){
    if(reading != ButtonState){
      ButtonState=reading;
      if(reading == HIGH && (digitalRead(button[0]) == HIGH)){
        carrow++;
      }
    }
  }
  LastButtonState =reading;
  
  
  
  
  
  Serial.println(digitalRead(button[1]));

  for(int row=0; row<carrow; row++){
    for(int col= 0; col<8; col++){
      lc.setLed(0,row,col,true);
    }
  }

  // Blink

  if(carrow > 8){
    for(int row=0; row<carrow; row++){
      for(int col= 0; col<8; col++){
        lc.setLed(0,row,col,true);
      }
    }
    delay(1000);
    for(int row=0; row<carrow; row++){
      for(int col= 0; col<8; col++){
        lc.setLed(0,row,col,false);
      }
    }
    delay(1000);


  }

  


  

}
