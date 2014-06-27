//LED and Button Pins for Players
const int numberOfPlayers = 3;     
int button[numberOfPlayers];       
int led[numberOfPlayers];     

//Turn Order and Tracking
int turn = 0;
int turnOrder[15];

//Application State
boolean running = false;
boolean programmed = false;
int mode = 0;

//Configuration
int blinkRate = 5;
int stupid = 0;

void setup(){ 
  //loop to assign button and LEDs to pins
  for(int i = 0; i < numberOfPlayers; i++){
    button[i] = i*2;
    pinMode(button[i], INPUT);
    led[i] = i*2+1;
    pinMode(led[i], OUTPUT);
  }
}

void loop(){
  switch(mode){
  case 0:         //walk, when DM button is high go to 1
    walk();
    mode = digitalRead(button[0]);
    break;        
  case 1:         //blink, then go to 2
    blinkAllLEDs(3);
    mode = 2;
    break;
  case 2:         //program the turn order with button pushes
    program();
    break;
  case 3:         //run the game
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

void program(){
  if(programmed){
    running = true;
    turnOrder[turn] = -1;
    mode = 3;
    return;
  }
  setTurns();
}

void run(){
  for(turn=0; turnOrder[turn] >= 0; stupid++ ){
      blinkLED(turnOrder[turn],1);
      if(digitalRead(button[0])){
        blinkAllLEDs(3);
        turn++;
      }

  }
  blinkAllLEDs(3);
} 

void setTurns(){
  for(int i = 0; i < numberOfPlayers; i++){
    if(digitalRead(button[i])){
      turnOrder[turn] = i;
      turn++;
      blinkLED(i,3);
      if(i == 0 && digitalRead(button[i])){
        programmed = true;
      }
    }
  }
}

//blink LED X, Y number of times
void blinkLED(int X, int Y){
  for(int i=0; i<Y; i++){
    digitalWrite(led[X], HIGH);
    delay(blinkRate);
    digitalWrite(led[X], LOW);
    delay(blinkRate);
  }
}

//blink all LEDs, Y number of times
void blinkAllLEDs(int maxBlinks){
  for(int i=0; i<maxBlinks; i++){
    for(int j=0; j < numberOfPlayers; j++){
      digitalWrite(led[j], HIGH);
    }
    delay(blinkRate);
    for(int j=0; j<numberOfPlayers; j++){
      digitalWrite(led[j], LOW);
    }
    delay(blinkRate);
  }
}