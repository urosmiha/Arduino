#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;

int potpin = 0;  // analog pin used to connect the potentiometer
int val = 500;    // variable to read the value from the analog pin
int val2 = 500;
int val3 = 500;
int val4 = 500;
int pos = 500;

//------------------

//-------- GREEN --------
int green_1_in = 121;
int green_2_in = 538;
int green_3_in = 271;
int green_4_in = 1020;

int green_1_out = 766;
int green_2_out = 538;
int green_3_out = 59;
int green_4_out = 930;

//-------- RED --------
int red_1_in = 200;
int red_2_in = 535;
int red_3_in = 270;
int red_4_in = 1020;

int red_1_out = 766;
int red_2_out = 538;
int red_3_out = 59;
int red_4_out = 950;

//-------- BLUE --------
int blue_1_in = 300;
int blue_2_in = 538;
int blue_3_in = 305;
int blue_4_in = 1023;

int blue_1_out = 766;
int blue_2_out = 538;
int blue_3_out = 59;
int blue_4_out = 950;

//-------- BLACK --------
int black_1_in = 390;
int black_2_in = 538;
int black_3_in = 288;
int black_4_in = 1023;

int black_1_out = 766;
int black_2_out = 538;
int black_3_out = 59;
int black_4_out = 950;

//-----------------

boolean green_p = true;
boolean red_p = true;
boolean blue_p = true;
boolean black_p = true;

int tmp_pos = 0;
int i = 0;

int btn = 0;

int state = 0;
boolean enable = false;

//String penSel = "";

void setup() {
  Serial.begin(9600);  
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(5);
  myservo3.attach(6);
  myservo4.attach(9);

  int tmp_val = 500;
  tmp_val = map(tmp_val, 0, 1023, 0, 180);
  myservo.write(tmp_val);  // attaches the servo on pin 9 to the servo object
  tmp_val = 500;
  tmp_val = map(tmp_val, 0, 1023, 0, 180);
  myservo2.write(tmp_val);
  tmp_val = 70;
  tmp_val = map(tmp_val, 0, 1023, 0, 180);
  myservo3.write(tmp_val);
  tmp_val = 920;
  tmp_val = map(tmp_val, 0, 1023, 0, 180);
  myservo4.write(tmp_val);

  pinMode(13, OUTPUT);
}

void loop() {

   char penSel;     
     
    if(Serial.available() > 0)  
    {          
      digitalWrite(13, HIGH);
        penSel = Serial.read();  
          
//       if(receiveVal == '1')      
//          ledState = 1;     
//       else  
//          ledState = 0;
        enable = true;  
        digitalWrite(13, LOW);     
    }     
    if(enable) {
          if(penSel == 'G') {
            state = 0;    
          } else if(penSel == 'R') {
            state = 1;  
          }else if(penSel == 'B') {
            state = 2;
          }else if(penSel == 'C') {
            state = 3;
          } else {
            state = 4;
          }

          if(penSel == 'A') {
           green_p = true;    
          } else if(penSel == 'Q') {
            red_p = true;  
          }else if(penSel == 'W') {
            blue_p = true;
          }else if(penSel == 'E') {
            black_p = true;
          }
        
        
//          btn = digitalRead(7);  // read input value
        
        //  if(btn == LOW) {
        //    confusedMove();
        //    delay(5000);
        //  }
        
          
//          if(btn == HIGH) {
//            // RESET PEN AVAILABILITY
//            green_p = true;
//            red_p = true;
//            blue_p = true;
//            black_p = true;
//          }
        //  if(btn == LOW) {
        //    if(state == 0) {
        //      state = 1;
        //    } else if (state == 1) {
        //      state = 2;
        //    }else if (state == 2) {
        //      state = 3;
        //    }else if (state == 3) {
        //      state = 0;
        //    }
        //    enable = 1;
        //    Serial.println(state);
        //  }
        
        //  if(enable == 1) {
            if(state == 0) {  // GET the GREEN pen
        
              if(!green_p) {
                confusedMove();
              } else {
                val = green_1_in;
                val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
                myservo.write(val);
                delay(1000);
                
                val = green_3_in;
                val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
                myservo3.write(val);
                delay(1000);
                
                val = green_4_in;
                val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
                myservo4.write(val);
                delay(2000);
          
                green_p = false;
              }
            } 
            else if (state == 1) {  // GET RED pen
              val = red_1_in;
              val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
              myservo.write(val);
              delay(1000);
              
              val = red_3_in;
              val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
              myservo3.write(val);
              delay(1000);
              
              val = red_4_in;
              val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
              myservo4.write(val);
              delay(2000);
        
              red_p = false;
            }
            else if (state == 2) {  // GET BLUE pen
              val = blue_1_in;
              val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
              myservo.write(val);
              delay(1000);
              
              val = blue_3_in;
              val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
              myservo3.write(val);
              delay(1000);
              
              val = blue_4_in;
              val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
              myservo4.write(val);
              delay(2000);
        
              blue_p = false;
            }
            else if (state == 3) {  // GET BLACK pen
                  val = black_1_in;
              val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
              myservo.write(val);
              delay(1000);
              
              val = black_3_in;
              val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
              myservo3.write(val);
              delay(1000);
              
              val = black_4_in;
              val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
              myservo4.write(val);
              delay(2000);
        
              black_p = false;
            } else {
              // Nothing
            }
        
             val = green_3_out;
              val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
              myservo3.write(val);
              delay(1000);
              
              val = green_1_out;
              val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
              myservo.write(val);
              delay(1000);
              
              val = green_4_out;
              val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
              myservo4.write(val);
              delay(1000);
            
        //    enable = 0;
        //}
        
        //    val = analogRead(0);
        //    if (btn == LOW) {
        //      Serial.println("Val 1:");
        //      Serial.println(val);
        //    }
        //    delay(15);
        //    val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
        //    myservo.write(val);        
        //
        //  val2 = analogRead(1);
        //  if (btn == LOW) {
        //    Serial.println("Val 2:");
        //    Serial.println(val2);
        //  }
        //  delay(15);
        //  val2 = map(val2, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
        //  myservo2.write(val2);                  //
        //
        //    val3 = analogRead(2);
        //    if (btn == LOW) {
        //      Serial.println("Val 3:");
        //      Serial.println(val3);
        //    }
        //  delay(15);
        //  val3 = map(val3, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
        //  myservo3.write(val3);                  //
        //
        //     val4 = analogRead(3);
        //     if (btn == LOW) {
        //      Serial.println("Val 4:");
        //      Serial.println(val4);
        //     }
        //  delay(15);
        //  val4 = map(val4, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
        //  myservo4.write(val4);                  //

        enable = false;
  }
}

//String serialRead() {
//
//  String inputString = "";
//
//  if(Serial.available() > 0)  {
//    char inChar = (char)Serial.read();
//
//    inputString += inChar;
//
//    if(inChar == '/n') {
//      return inputString;
//    }
//  }
//
//  return inputString;
//
//}

void confusedMove() {

  val = 1000;
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);
  delay(1000);

  val = 200;
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo3.write(val);
  delay(1000);
   
  val2 = 1000;
  val2 = map(val2, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo2.write(val2);  
  delay(1000); 
  val2 = 500;
  val2 = map(val2, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo2.write(val2);  
  delay(1000);                
}




