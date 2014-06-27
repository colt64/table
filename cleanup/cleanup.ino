//LED and Button Pins
int led1 = 5;
int led2 = 6;
int led3 = 7;
int button1 = 1;
int button2 = 2;
int button3 = 3;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int lastReading1 = 0;
int holdLength = 1000;

int numPlayers = 3;

int timer = 0;
int blinkRate = 200;
boolean programmed = false;
boolean running = false;
//Track Turn order and create array to hold turns
int Turn = 0;
int turnOrder[15];  //TODO: try higher number of turns
//int curTurn=0;  //not sure this is ever necessary
int totalTurns=0; //TODO: make this local
int waitButton = 0; //TODO: Make this local
unsigned long ledStart = 0; //make this local
int maxBlinks = 6;   //local

int state1 = HIGH;
int state2 = LOW;
int state3 = LOW;



/*Modes:
0 = idle
1 = blink  //TODO: remove mode and putting in method
2 = program
3= run
*/

int Mode = 0;



void setup()
{
  
  //set pins
  pinMode(led1,OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  int players[numPlayers];
  
  
}

void loop(){

    buttonState1=digitalRead(button1);  //TODO: just put these in a method called getButton
   buttonState2=digitalRead(button2);  
    buttonState3=digitalRead(button3);
	
	
     if(buttonState1 == HIGH && lastReading1 == LOW){   //If button is pushed and was not pushed before:
    timer = millis();                                     //Start a timer
    }
    if(buttonState1 == HIGH && lastReading1 == HIGH)        //If button is pushed and was pushed before:
    {
      if((millis() - timer) > holdLength){      //If current time minus the time started is more than 
        switch(Mode){
          case 0:							//TODO: Put this in it's own method
                Mode = 1;  
                break;        
          case 2:
                Mode = 3;
                break;
          case 3:
                Mode = 0;
                break;
        }
      }
    }
    switch(Mode){  //Perform action based on current mode
      case 0:
          walkLED();   //Blink lights in sequence
          break;
      case 1:        //Get rid of this
           blinkLED(6);
           break;
      case 2:       //Accept turn programming
            program();
            break;
      case 3:       //Run through the turns until stopped
            run();
            break;
    }
    //lastReading1=buttonState1;
}

void getButon(){
	foreach
}
void walkLED(){    //Blink LEDs in succession

 unsigned long currentMillis = millis();
 
  
  if(currentMillis - ledStart > blinkRate)
  {
    if(state1 == HIGH)   //TODO: Simplify this
    {
      ledStart = currentMillis;
      state1 = LOW;
      state2 = HIGH;
      state3 = LOW;
        
          //digitalWrite(led3, LOW);
          //digitalWrite(led2, HIGH);
      
    }
      else if(state2 == HIGH)  //Else-if important so that it does not turn on only 3rd LED
    {
      ledStart = currentMillis;
      state1 = LOW;
      state2 = LOW;
      state3 = HIGH;
        
          //digitalWrite(led3, LOW);
          //digitalWrite(led2, HIGH);
      
    }
      else if(state3 == HIGH)
      {
        ledStart = currentMillis;
        state1 = HIGH;
        state2 = LOW;
        state3 = LOW;
        
          //digitalWrite(led3, LOW);
          //digitalWrite(led2, HIGH);
      
      }
   
      
    digitalWrite(led1, state1);   
    digitalWrite(led2, state2);
    digitalWrite(led3, state3);
    
  }
  
}
void blinkLED(int blinks){                 //blinks all LEDs at once
  unsigned long currentMillis = millis();
    if(blinks >= maxBlinks)
    {
     Mode = 2; 
    }
    if(currentMillis - ledStart > blinkRate) //if more than 200ms
      {
        ledStart = currentMillis;
        if(state1 == LOW)
          state1 = HIGH;
        else
          state1 = LOW;
          blinkNumber++;
      }
     digitalWrite(led1, state1);
    digitalWrite(led2, state1);
    digitalWrite(led3, state1);
}

void program(){     //Run the program
   {
   Turn = 0;
   state1 = LOW;
   state2 = LOW;
   state3 = LOW;
   digitalWrite(led1, state1);   
   digitalWrite(led2, state2);
   digitalWrite(led3, state3);
    if(buttonState1 == HIGH && lastReading1 == HIGH)
    {
      if((millis() - timer) > holdLength && programmed == true){
      running = true;
      totalTurns= Turn;
       Mode = 3;
      
      }
    }
   if(buttonState1 == HIGH)
   {
     //turnOrder[Turn] = 1;
     digitalWrite(led1, HIGH);
     digitalWrite(led2, LOW);
     digitalWrite(led3, LOW);
     //Turn++;
   }
  else if(buttonState2 == HIGH)
   {
     //turnOrder[Turn] = 2;
     digitalWrite(led1, LOW);
     digitalWrite(led2, HIGH);
     digitalWrite(led3, LOW);
     //Turn++;
   }
   else if(buttonState3 == HIGH)
   {
    //turnOrder[Turn] = 3;
     digitalWrite(led1, LOW);
     digitalWrite(led2, LOW);
     digitalWrite(led3, HIGH);
    //Turn++;
   }
   
   lastReading1 = buttonState1;
   }
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
