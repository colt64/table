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

/*modes:
0 = idle
1 = blink
2 = program
3= run
*/

void loop(){
  readButtons();
  switch(mode){
  case 0:         //walk, when dm buttom high go to 1
    walk();
    break;        
  case 1:         //blink, then go to 2
    blinkLED();
    mode = 2;
    break;
  case 2:         //program the turn order with button pushes
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
    if(buttonState[0] == HIGH){
      mode = 1;
    }
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
  
}


void run(){

} 

void readButtons(){
  for(int i = 0; i < numberOfPlayers; i++){
    lastReading[i] = buttonState[i];
  }  
  for(int i = 0; i < numberOfPlayers; i++){
    buttonState[i] = digitalRead(button[i]);
  }
}
