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

int onTime = 0;
int blinkRate = 200;
boolean programmed = false;
boolean running = false;
//Track Turn order and create array to hold turns
int Turn = 0;
int turnOrder[15];
int curTurn=0;
int totalTurns=0;
int waitButton = 0;
unsigned long ledStart = 0;
int blinkNumber = 0;
int maxBlinks = 6;

int state1 = HIGH;
int state2 = LOW;
int state3 = LOW;

/*Modes:
0 = idle
1 = blink
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
  Serial.begin(300);
  
}

void loop()
{
  
  buttonState1=digitalRead(button1);
   buttonState2=digitalRead(button2);
    buttonState3=digitalRead(button3);
     if(buttonState1 == HIGH && lastReading1 == LOW){
    onTime = millis();
    }
    if(buttonState1 == HIGH && lastReading1 == HIGH)
    {
      if((millis() - onTime) > 1000 && programmed == false){
      Mode = 1;
      programmed = true;
      }
    }
 /*   
  if(buttonState == HIGH)
   {
     
     if(Mode == 0)
     {
       Mode = 1;
     }
     else{
       Mode = 0;
     }
   } */
  if(Mode == 0){
  unsigned long currentMillis = millis();
  //"Walking" or successive blinking
  if(currentMillis - ledStart > blinkRate)
  {
    if(state1 == HIGH)
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
    lastReading1 = buttonState1;
  }
  }
  else if(Mode == 1)
  {
    unsigned long currentMillis = millis();
    if(blinkNumber >= maxBlinks)
    {
     Mode = 2; 
    }
    if(currentMillis - ledStart > blinkRate)
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
  else if(Mode == 2)
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
      if((millis() - onTime) > 1000 && programmed == true){
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
 else if(Mode == 3 && running == true)
{
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
    
  
   Serial.println(Mode, DEC);
  
}
