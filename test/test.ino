const int numberOfPlayers = 7;    //Number of players including the DM
int button[numberOfPlayers];      //array to hold button pins
int led[numberOfPlayers];         //array to hold led pins

void setup() {
  //loop to assign button and leds to pins
  for(int i = 0; i < numberOfPlayers; i++){
    button[i] = i*2;
    pinMode(button[i], INPUT);
    led[i] = i*2+1;
    pinMode(led[i], OUTPUT);
  }
}

void loop(){
  for(int i = 0; i < numberOfPlayers; i++){
     digitalWrite(led[i], digitalRead(button[i]));
  }
}
