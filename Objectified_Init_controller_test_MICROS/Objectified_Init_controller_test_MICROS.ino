//Global Variables
//LED and Button Pins
const int numberOfPlayers = 6;     
int button[numberOfPlayers];       
int buttonState[numberOfPlayers];
int lastReading[numberOfPlayers]; 
int led[numberOfPlayers];     

int onTime = 0;
int blinkRate = 5;
boolean programmed = false;
boolean running = false;
//Track Turn order and create array to hold turns
int Turn = 0;
int turnOrder[15];
int curTurn=0;
int totalTurns=0;
int waitButton = 0;
unsigned long ledStart = 0;

/*modes:
0 = idle
1 = blink
2 = program
3= run
*/

int mode = 0;

void setup(){ 
  //loop to assign button and leds to pins
  for(int i = 0; i < numberOfPlayers; i++){
    button[i] = i*2;
	  pinmode(button[i], INPUT);
    led[i] = i*2+1;
    pinmode(led[i], OUTPUT);
  }
}

void loop(){
  readButtons();
  if(buttonState[0] == HIGH && lastReading[0] == LOW){
    onTime = micros();
  }
  if(buttonState[0] == HIGH && lastReading[0] == HIGH)
  {
    if((micros() - onTime) > 50){
      switch(mode){
        case 0:
          walk();
          mode = 1;
          break;        
        case 1:
          blinkLED();
          break;
        case 2:
          run();
          Turn = 0;
          
          break;
        case 3:
          walk();
          break;
        else:
          walk();
          break;
      }
    }
  }
  lastReading[0] = buttonState[0];
}

void walk(){
  for(int i = 0; i < numberOfPlayers; i++){
    digitalWrite(led[i], HIGH);
    delay(blinkRate);
    digitalWrite(led[i], LOW);
  }
}

void blinkLED(){
  int maxBlinks = 6;
  for(int i=0; i<maxBlinks; i++){
    for(int i=0; i < numberOfPlayers; i++){
      digitalWrite(led[i], HIGH);
    }
    delay(blinkRate);
    for(int i=0; i < numberOfPlayers; i++){
      digitalWrite(led[i], LOW);
    }
    delay(blinkRate);
  }
}

void program(){
   digitalWrite(led1, state1);
   digitalWrite(led2, state2);
   digitalWrite(led3, state3);
    if(buttonState1 == HIGH && lastReading1 == HIGH)
    {
      if((micros() - onTime) > 50 && programmed == true){
      running = true;
      totalTurns= Turn;
       mode = 3;
      
      }
    }
   if(buttonState1 == HIGH  && lastReading1 == LOW)
   {
     turnOrder[Turn] = 1;
     digitalWrite(led1, HIGH);
     digitalWrite(led2, LOW);
     digitalWrite(led3, LOW);
     Turn++;
   }
  else if(buttonState2 == HIGH)
   {
     turnOrder[Turn] = 2;
     digitalWrite(led1, LOW);
     digitalWrite(led2, HIGH);
     digitalWrite(led3, LOW);
     Turn++;
   }
   else if(buttonState3 == HIGH)
   {
    turnOrder[Turn] = 3;
     digitalWrite(led1, LOW);
     digitalWrite(led2, LOW);
     digitalWrite(led3, HIGH);
    Turn++;
   }
   
   lastReading1 = buttonState1;
   }

void run(){
    switch(turnOrder[curTurn]){
         case 1: 
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        waitButton = button1;
                break;
    case 2: 
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, LOW);
                waitButton = button2;
                break;
        case 3: 
                digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, HIGH);
                waitButton = button3;
                break;

   }
   if(digitalRead(waitButton) == HIGH)
     {
     curTurn++;
     }  
     lastReading1 = buttonState1;
    
} 

void readButtons(){
  for(int i = 0; i < numberOfPlayers; i++){
    lastReading[i] = buttonstate[i]);
  }  
  for(int i = 0; i < numberOfPlayers; i++){
    buttonstate[i] = digitalRead(button[i]));
  }
}
