#include "Timer.h"

  Timer t;
  
  int timeUnit = 200;
  int toneFreq = 700;
  int OutPin = 11;
  // Output LED to display received message.
  int ledOut = 8; 

  int countID = 0;
  char readChars[] = {' ', ' ', ' ', ' ', ' ', ' '};
  
  int countChar = 0;
  int countSpace = 0;

  int LedPin = 7;
  int interruptPin = 2;

  bool enableBttnRead = false;

  int modePin = 3;
  int mode = 0;

  int dotDelay = timeUnit;
  int dashDelay = timeUnit*3;
  
  int letterDelay = timeUnit*2;
  int wordDelay = timeUnit*4;

//TEST
  int cnt = 0;
//============

void setup() {

  t.every(1000,timerISR);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), readButton, RISING);

  pinMode(modePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(modePin), modeChange, RISING);
  
  // Set up serial
  Serial.begin(9600);

  pinMode(ledOut, OUTPUT);
  pinMode(LedPin, OUTPUT);
  pinMode(modePin, INPUT);
  //pinMode(inputPin, INPUT);
}

void loop() {
  
  if(mode == 1) {
    t.update();
    enableBttnRead = true;
    DisplayReadChar();
  } 
  else
  {
    readFromConsole();
    enableBttnRead = false;
  }
}

void modeChange() {
  if(mode == 0) {
    mode = 1;
    Serial.println("READ FROM BUTTON");
  } 
  else 
  {
    mode = 0;
    Serial.println("READ FROM CONSOLE");
  }
}

//=================================================

void readButton() {
  if(enableBttnRead) {
    while(digitalRead(interruptPin)) {
      countChar++;
      delay(10);
    }

    if(countChar > 1500) {
      Serial.println("-");
      readChars[countID] = '-';
    } else if (countChar > 300){
      Serial.println(".");
      readChars[countID] = '.';
    }
    
    if(countID > 4) {
      countID = 0;    
    } else {
      countID++;
    }
  
    countChar = 0;
    countSpace = 0;
  }
}

//==================================================
// Tiimer overflow
void timerISR() {
  digitalWrite(LedPin,!digitalRead(LedPin));
  countSpace++;
}

//====================================================
// Display characters
void DisplayReadChar() {
    if(countSpace > 6) {
    // NEW WORD
    Serial.println("New Word");
    countSpace = 0;
  }
  else if(countSpace == 3) {
    // NEW LETTER
    
    for(int i=0; i<6; i++) {
      Serial.println(readChars[i]);
      //readChars[i] = ' ';
    }
    Serial.println("New Letter");
  }
}

//====================================================
// Read from the console
void readFromConsole() {
  if(Serial.available() > 0) {
    int readChar = Serial.read();

    Serial.print("I received: ");
    Serial.println(readChar, DEC);

    DecideTone(readChar);
  }
}

//===================================================
// Decide which tone shoud be played
void DecideTone(int inChar){
  // Only allow characters that are lowercase letters or numbers(0-9) or SPACE or "."
    if((inChar > 96 && inChar < 123) || (inChar > 47 && inChar < 58) || inChar == 32 || inChar == 46) {
      switch(inChar) {     
        case 97: // a
          playTone('.','-',' ',' ',' ',' ');
        break;
        case 98: // b
          playTone('-','.','.','.',' ',' ');
        break;
        case 99: // c
          playTone('-','.','-','.',' ',' ');
        break;
        case 100: // d
          playTone('-','.','.',' ',' ',' ');
        break;
        case 101: // e
          playTone('.',' ',' ',' ',' ',' ');
        break;
        case 102: // f
          playTone('.','.','-','.',' ',' ');
        break;
        case 103: // g
          playTone('-','-','.',' ',' ',' ');
        break;
        case 104: // h
          playTone('.','.','.','.',' ',' ');
        break;
        case 105: // i
          playTone('.','.',' ',' ',' ',' ');
        break;
        case 106: // j
          playTone('.','-','-','-',' ',' ');
        break;
        case 107: // k
          playTone('-','.','-',' ',' ',' ');
        break;
        case 108: // l
          playTone('.','-','.','.',' ',' ');
        break;
        case 109: // m
          playTone('-','-',' ',' ',' ',' ');
        break;
        case 110: // n
          playTone('-','.',' ',' ',' ',' ');
        break;
        case 111: // o
          playTone('-','-','-',' ',' ',' ');
        break;
        case 112: // p
          playTone('.','-','-','.',' ',' ');
        break;
        case 113: // q
          playTone('-','-','.','-',' ',' ');
        break;
        case 114: // r
          playTone('.','-','.',' ',' ',' ');
        break;
        case 115: // s
          playTone('.','.','.',' ',' ',' ');
        break;
        case 116: // t
          playTone('-',' ',' ',' ',' ',' ');
        break;
        case 117: // u
          playTone('.','.','-',' ',' ',' ');
        break;
        case 118: // v
          playTone('.','.','.','-',' ',' ');
        break;
        case 119: // w
          playTone('.','-','-',' ',' ',' ');
        break;
        case 120: // x
          playTone('-','.','.','-',' ',' ');
        break;
        case 121: // y
          playTone('-','.','-','-',' ',' ');
        break;
        case 122: // z
          playTone('-','-','.','.',' ',' ');
        break;
        case 48: // 0
          playTone('-','-','-','-','-',' ');
        break;
        case 49: // 1
          playTone('.','-','-','-','-',' ');
        break;
        case 50: // 2
          playTone('.','.','-','-','-',' ');
        break;
        case 51: // 3
          playTone('.','.','.','-','-',' ');
        break;
        case 52: // 4
          playTone('.','.','.','.','-',' ');
        break;
        case 53: // 5
          playTone('.','.','.','.','.',' ');
        break;
        case 54: // 6
          playTone('-','.','.','.','.',' ');
        break;
        case 55: // 7
          playTone('-','-','.','.','.',' ');
        break;
        case 56: // 8
          playTone('-','-','-','.','.',' ');
        break;
        case 57: // 9
          playTone('-','-','-','-','.',' ');
        break;
        case 46: // .
          playTone('.','-','.','-','.','-');
        break;
        case 32: // SPACE
          delay(wordDelay);
        break;
      }
    }
}


//====================================================

// Plays the tone sequence based on input
// Max number of characters (i.e dots and dashes) to represent a Letter is 6.
void playTone(char char0, char char1, char char2, char char3, char char4, char char5) {
  
  if(char0 == '.') {
    playDot();
  } 
  else if(char0 == '-') {
    playDash();
  }
//----------------------------------
  if(char1 == '.') {
    playDot();
  } 
  else if(char1 == '-') {
    playDash();
  }
//----------------------------------
  if(char2 == '.') {
    playDot();
  } 
  else if(char2 == '-') {
    playDash();
  }
//----------------------------------
  if(char3 == '.') {
    playDot();
  } 
  else if(char3 == '-') {
    playDash();
  }
//----------------------------------
  if(char4 == '.') {
    playDot();
  } 
  else if(char4 == '-') {
    playDash();
  }
//----------------------------------
  if(char5 == '.') {
    playDot();
  } 
  else if(char5 == '-') {
    playDash();
  }
//--------------------------------
  delay(letterDelay);
}

// Plays the sound for DOT and blink led
void playDot(){
  tone(OutPin,toneFreq,timeUnit);
  digitalWrite(ledOut, HIGH);
  delay(dotDelay);
  digitalWrite(ledOut, LOW);
  delay(timeUnit);
}

// Plays the sound for DASH and blink led
void playDash() {
  tone(OutPin,toneFreq,timeUnit*3);
  digitalWrite(ledOut, HIGH);
  delay(dashDelay);
  digitalWrite(ledOut, LOW);
  delay(timeUnit);
}





