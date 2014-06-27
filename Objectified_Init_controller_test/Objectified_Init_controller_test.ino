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

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
}

void loop()
{
    buttonState1=digitalRead(button1);
    if(buttonState1 == HIGH ){
         digitalWrite(led1, HIGH);
    }
    else{
        digitalWrite(led1, LOW);
    }
}
