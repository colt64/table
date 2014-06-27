//Global Variables
//LED and Button Pins
const int numberOfPlayers = 3;     
int button[numberOfPlayers];       
int buttonState[numberOfPlayers];
int lastReading[numberOfPlayers]; 
int led[numberOfPlayers];     

int blinkRate = 5;
boolean programmed = false;
boolean running = false;
//Track Turn order and create array to hold turns
int Turn = 0;
int turnOrder[15];
int curTurn=0;
int totalTurns=0;
int waitButton = 0;



int mode = 0;

void setup(){ 
  //loop to assign button and leds to pins
  for(int i = 0; i < numberOfPlayers; i++){
    button[i] = i*2;
    pinMode(button[i], INPUT);
    led[i] = i*2+1;
    pinMode(led[i], OUTPUT);
  }
}

void loop(){
  readButtons();
  switch(mode){
    case 0:
    walk();
    if(buttonState[0] == HIGH){
      mode = 1;
    }
    break;        
    case 1:
    blinkLED();
    mode = 2;
    break;
    case 2:
    program();
    Turn = 0;
    break;
    case 3:
    run();
    break;
  }
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
    for(int j=0; i < numberOfPlayers; i++){
      digitalWrite(led[i], HIGH);
    }
    delay(blinkRate);
    for(int j=0; i < numberOfPlayers; i++){
      digitalWrite(led[i], LOW);
    }
    delay(blinkRate);
  }
}

void program(){
  readButtons();
  if(buttonState[0] == HIGH && lastReading[0] == HIGH)
  { int onTime = micros();
    if((micros() - onTime) > 50 && programmed == true){
      running = true;
      totalTurns= Turn;
      mode = 3;
    }
  }
  if(buttonState[0] == HIGH  && lastReading[0] == LOW){
   turnOrder[Turn] = 0;
   digitalWrite(led[0], HIGH);
   digitalWrite(led[1], LOW);
   digitalWrite(led[2], LOW);
   Turn++;
 }
 else if(buttonState[1] == HIGH)
 {
   turnOrder[Turn] = 1;
   digitalWrite(led[0], LOW);
   digitalWrite(led[1], HIGH);
   digitalWrite(led[2], LOW);
   Turn++;
 }
 else if(buttonState[2] == HIGH)
 {
  turnOrder[Turn] = 2;
  digitalWrite(led[0], LOW);
  digitalWrite(led[1], LOW);
  digitalWrite(led[2], HIGH);
  Turn++;
}

lastReading[0] = buttonState[0];
}

void run(){
  switch(turnOrder[curTurn]){
   case 1: 
   digitalWrite(led[0], HIGH);
   digitalWrite(led[1], LOW);
   digitalWrite(led[2], LOW);
   waitButton = 0;
   break;
   case 2: 
   digitalWrite(led[0], LOW);
   digitalWrite(led[1], HIGH);
   digitalWrite(led[2], LOW);
   waitButton = 1;
   break;
   case 3: 
   digitalWrite(led[0], LOW);
   digitalWrite(led[1], LOW);
   digitalWrite(led[2], HIGH);
   waitButton = 2;
   break;

 }
 if(digitalRead(button[waitButton]) == HIGH)
 {
   curTurn++;
 }  
 lastReading[0] = buttonState[0];    
} 

void readButtons(){
  for(int i = 0; i < numberOfPlayers; i++){
    lastReading[i] = buttonState[i];
  }  
  for(int i = 0; i < numberOfPlayers; i++){
    buttonState[i] = digitalRead(button[i]);
  }
}
