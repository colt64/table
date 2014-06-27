//LED and Button Pins for Players
const int numberOfPlayers = 3;     
int button[numberOfPlayers];       
int buttonState[numberOfPlayers];
int lastReading[numberOfPlayers]; 
int led[numberOfPlayers];     

//Turn Order and Tracking
int turn = 0;
int turnOrder[15];

//Application State
boolean running = false;
int mode = 0;

//Configuration
int blinkRate = 5;

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
  switch(mode){
  case 0:         //walk, when dm buttom high go to 1
    mode = walk();
    break;        
  case 1:         //blink, then go to 2
    mode = blinkAllLEDs();
    break;
  case 2:         //program the turn order with button pushes
    mode = program();
    break;
  case 3:         //run the game
    run();
    break;
  }
}

int walk(){
  for(int i = 0; i < numberOfPlayers; i++){
    digitalWrite(led[i], HIGH);
    delay(blinkRate);
    digitalWrite(led[i], LOW);
    if(digitalRead(button[0]) == HIGH){
      return 1;
    }
  }
  return 0;
}

int blinkAllLEDs(){
  int maxBlinks = 6;
  for(int i=0; i<maxBlinks; i++){
    for(int j=0; j < numberOfPlayers; j++){
      digitalWrite(led[j], HIGH);
    }
    delay(blinkRate);
    for(int j=0; j < numberOfPlayers; j++){
      digitalWrite(led[j], LOW);
    }
    delay(blinkRate);
  }
  return 2;
}

int program(){
  turnoffLEDs();
  readButtons();
  setTurns();
  if(buttonState[0] == HIGH && lastReading[0] == HIGH){
      running = true;
      turnOrder[turn] = -1;
      return 3;
   }
}


void run(){
  for(int i=0; turnOrder[i] >= 0; i++){
      blinkLED(turnOrder[1],1);
  }
} 

void readButtons(){
  for(int i = 0; i < numberOfPlayers; i++){
    lastReading[i] = buttonState[i];
    buttonState[i] = digitalRead(button[i]);
  }  
}

void turnoffLEDs(){
 for(int i = 0; i < numberOfPlayers; i++){
    digitalWrite(led[i], LOW);
  }
}

void setTurns(){
  for(int i = 0; i < numberOfPlayers; i++){
    if(buttonState[i] == HIGH){
        turnOrder[turn] = i;
        turn++;
        blinkLED(i,2);
    }
  }
}

//blink LED X, Y number of times
void blinkLED(int X, int Y){
  turnoffLEDs();
  for(int i=0; i<Y; i++){
    digitalWrite(led[X], HIGH);
    delay(blinkRate);
    digitalWrite(led[X], LOW);
    delay(blinkRate);
  }
 

}