#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal_I2C.h>


#define NUMCOMMANDS 4
//#define giveRandomCommand() rand()%4
#define THROTTLEUP 3
#define PRESSBUTTON 2
#define TURNRIGHT 1
#define TURNLEFT 0

#define getThrottleAngle() analogRead(A1)
#define getSteeringAngle() analogRead(A0)
#define lightGreen(ledHigh) digitalWrite(8, HIGH); ledHigh = true
#define getRedButtonPressed() digitalRead(2)

int val = 0;
int start;
int command;
bool running = false;
int score = 0;
bool ledHigh = false;
int commandEntered = 10000;
int dingTime = 10000;
bool commandPlayed = true;
bool dingPlayed = true;
int timeLeft = 20000;
double thisTime = 1;
int steeringMiddle;
LiquidCrystal_I2C lcd(0x27,  20, 2);
bool inputValid = false;
//#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))   // Using a soft serial port
//#include <SoftwareSerial.h>
//SoftwareSerial softSerial(/*rx =*/10, /*tx =*/11);
//#define FPSerial softSerial
//#else
#define FPSerial Serial
//#endif

DFRobotDFPlayerMini myDFPlayer;

void failure(){
  running = false;
  inputValid = false;
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  myDFPlayer.play(3);
}

int giveRandomCommand(){
      command = rand()%4;
      /*switch(command) {
        case TURNLEFT:
          myDFPlayer.play(6);
          break;
        case TURNRIGHT:
          myDFPlayer.play(5);
          break;
        case PRESSBUTTON:
          myDFPlayer.play(4);
          break;
        case THROTTLEUP:
          myDFPlayer.play(9);
          break;
      }*/
      return command;
}

void setup() {
  // put your setup code here, to run once:
  FPSerial.begin(9600);
  //Serial.begin(115200);
  pinMode(9, OUTPUT);
  pinMode(2, INPUT);
  pinMode(7, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(score);
  digitalWrite(9, LOW);
  steeringMiddle = analogRead(A0);
  //Serial.println("here");
  if (!myDFPlayer.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    //Serial.println(F("Unable to begin:"));
    //Serial.println(F("1.Please recheck the connection!"));
    //Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  //Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(30);
  //myDFPlayer.play(1);
}

void loop() {
  //Serial.println(digitalRead(7));
  if(running){
  //Serial.println("here");
  // put your main code here, to run repeatedly:
  int curTime = millis();
  int throttleAngle = getThrottleAngle();
  int steeringAngle = getSteeringAngle();
  bool buttonPressed = getRedButtonPressed();
  int lightStart = 1000;
  //val = analogRead(A1);
  int input = -1;
  int timePassed = curTime-start;
  int soundToPlay = -1;
  ///dingTime = 1000000;
  //commandEntered=curTime;
  //dingTime=curTime;
  if(curTime-commandEntered>2000 && !dingPlayed){
    dingPlayed = true;
    myDFPlayer.play(2);
    dingTime = millis();
    commandPlayed = false;
    lightGreen(ledHigh);
  }
  if(curTime-dingTime>2000 && !commandPlayed){
    if(score>=99){
      running = false;
      inputValid = false;
      myDFPlayer.play(7);
    }
    else {
      inputValid = true;
      digitalWrite(8, LOW);
      commandPlayed = true;
      switch(command) {
        case TURNLEFT:
          myDFPlayer.play(6);
          break;
        case TURNRIGHT:
          myDFPlayer.play(5);
          break;
        case PRESSBUTTON:
          myDFPlayer.play(4);
          break;
        case THROTTLEUP:
          myDFPlayer.play(9);
          break;
        }
      start = millis();
    }
  }
  /*if(timePassed>1000){
    start = millis();
    command = giveRandomCommand();
  }*/
  //end the blink of the led
  /*if(ledHigh && timePassed>250){
    ledHigh = false;
  }*/
  //assign the correct inputs
  if(timePassed>2000){
    if(steeringAngle > steeringMiddle+25)//537)//512
      input = TURNRIGHT;
    if(steeringAngle < steeringMiddle-25)//487)
      input = TURNLEFT;
  }
  if(throttleAngle > 800 && timePassed>2000 ){
    input = THROTTLEUP;
    //myDFPlayer.play(8);
    soundToPlay = 8;
  }
  if(buttonPressed && timePassed>500){
    input = PRESSBUTTON;
    //myDFPlayer.play(1);
    soundToPlay = 1;
  }
  //end assign the correct inputs
  //if the input is correct, light up the led, restart the countdown, give a new command, and increment the score
  if(command==input && inputValid){
    //Serial.println("good job");
    //myDFPlayer.play(2);
    //start = millis();
    inputValid = false;
    dingPlayed = false;
    command = giveRandomCommand();
    //Serial.println(command);
    score++;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(score);
    //delay(1000);
    if(soundToPlay>-1){
      myDFPlayer.play(soundToPlay);
    }
    thisTime/=1.0392;
    timeLeft=10000*thisTime+10000;
    commandEntered = millis();
  }
  else if(command!=input && input!=-1 && dingPlayed && commandPlayed){
    failure();
  }
  if(digitalRead(7)){
    running = false;
  }
  if(timePassed>timeLeft){
    failure();
  }
  }
  else
    if(!running){
      running = digitalRead(7);
      //Serial.println("this");
      //Serial.println(running);
      if(running){
        start = millis();
        score = 0;
        command = giveRandomCommand();
        inputValid = true;
        timeLeft = 20000;
        thisTime = 1;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(score);
        digitalWrite(9, LOW);
        switch(command) {
          case TURNLEFT:
            myDFPlayer.play(6);
            break;
          case TURNRIGHT:
            myDFPlayer.play(5);
            break;
          case PRESSBUTTON:
            myDFPlayer.play(4);
            break;
          case THROTTLEUP:
            myDFPlayer.play(9);
            break;
        }
      }
      dingPlayed = true;
      commandPlayed = true;
      //lcd.setCursor(0,0);
      //lcd.print(score);
      //Serial.println(command);
    }
  //Serial.println(val);
}
