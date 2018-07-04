  int timeUnit = 100;
  int toneFreq = 700;
  int OutPin = 11;

  int dotDelay = timeUnit*2;
  int dashDelay = timeUnit*4;
  int wordDelay = timeUnit*3;
  int laterDelay = timeUnit*2;

void setup() {

  // Set up serial
  Serial.begin(9600);

// HELLO WORLD TEST ****************************
/*
  delay(1000);
  //------------- H -----------------
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  // Letter space
  delay(laterDelay);
  //--------------- E -------------------
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  // Letter space
  delay(laterDelay);
  //---------------- L -----------------
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  // Letter space
  delay(laterDelay);
  //--------------- L -----------------
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  // Letter space
  delay(laterDelay);
  //----------- O --------------------
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  //----------------- SPACE ---------
  delay(wordDelay);
  //--------------- W -------------
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  // Letter space
  delay(laterDelay);
  //--------------- O ------------
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  //---------------- R ------------
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  // Letter space
  delay(laterDelay);
  //--------------- L --------------
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  // Letter space
  delay(laterDelay);
  //--------------- D -------------
  tone(OutPin,toneFreq,timeUnit*3);
  delay(dashDelay);
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  tone(OutPin,toneFreq,timeUnit);
  delay(dotDelay);
  */
//*************************************************
}

void loop() {
  if(Serial.available() > 0) {
    int incomingByte = Serial.read();

    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);

    if(incomingByte == 101) {
      tone(OutPin,toneFreq,timeUnit);
      delay(dotDelay);
      // Letter space
      delay(laterDelay);
    } else if(incomingByte == 104) {
      tone(OutPin,toneFreq,timeUnit);
      delay(dotDelay);
      tone(OutPin,toneFreq,timeUnit);
      delay(dotDelay);
      tone(OutPin,toneFreq,timeUnit);
      delay(dotDelay);
      tone(OutPin,toneFreq,timeUnit);
      delay(dotDelay);
      // Letter space
      delay(laterDelay);
    } else if(incomingByte == 108) {
       tone(OutPin,toneFreq,timeUnit);
    delay(dotDelay);
    tone(OutPin,toneFreq,timeUnit*3);
    delay(dashDelay);
    tone(OutPin,toneFreq,timeUnit);
    delay(dotDelay);
    tone(OutPin,toneFreq,timeUnit);
    delay(dotDelay);
    // Letter space
    delay(laterDelay);
    } else if(incomingByte == 111) {
      tone(OutPin,toneFreq,timeUnit*3);
      delay(dashDelay);
      tone(OutPin,toneFreq,timeUnit*3);
      delay(dashDelay);
      tone(OutPin,toneFreq,timeUnit*3);
      delay(dashDelay);
      // Letter space
     delay(laterDelay);
    } else if(incomingByte == 32) {
      delay(wordDelay);
    }
  }
}
