#include <SoftwareSerial.h>
#include <PololuLedStrip.h>

// LedStrip object and pin it will use
PololuLedStrip<6> ledStrip;
rgb_color colors[9];

SoftwareSerial BTSerial(10, 11); // RX | TX

String content = "";
char character;

bool ai_turn = false;
int in_cmd;
bool play = false;
int lvl = 0;

int board[9] = {0,0,0,0,0,0,0,0,0};

void setup()
{
  pinMode(9, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("Hello");
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
  BTSerial.write("Starting New Game... \n");
}

void loop()
{
  initGame();

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available() > 0) {
    
    in_cmd = BTSerial.read();

//    Serial.println(in_cmd);
    in_cmd = in_cmd - 48;
//    Serial.println(field);
  
    if(in_cmd == 0) {   // Reset game
      play = false;
      initGame();
    } else if (in_cmd > 0 && in_cmd < 10) {
      if(checkMove(in_cmd-1) == false) {
        BTSerial.write("Try Again \n");
      } else {
        board[in_cmd-1] = 1;
        ai_turn = true;
        updateBoard();
        checkWinner();
      }
    } else {
//      BTSerial.write("You can't do that! \n");
    }
  }

  if(ai_turn) {
    BTSerial.write("AI is thinking... \n");
    int index;
    
    delay(2000);
    if(lvl == 1) {
      index = playSemiHard();
    } else if(lvl == 2) {
      index = playHard();
    } else {
      index = playEasy();
    }
    board[index] = 2;
    ai_turn = false;
    updateBoard();
    checkWinner();
    BTSerial.write("AI played \n");
    BTSerial.write("Your turn now \n");
  }

// 
//  if (Serial.available()) {
//    BTSerial.write(Serial.read());
//  }
}

int playEasy() {

  int ai_move = (in_cmd + random(0, 8)) / 2;
//  Serial.println(ai_move);
  while(!checkMove(ai_move)) {
    ai_move = (in_cmd + random(0, 8)) / 2;
//    Serial.println(ai_move);
  }

  return ai_move;
}

// Randomly mess up
int playSemiHard() {
  int error = random(0,100);
  int ai_move;

  if(error % 20 == 0) {
    Serial.println("Random Played");
    while(!checkMove(ai_move)) {
      ai_move = (in_cmd + random(0, 8)) / 2;
    }
  } else {
    ai_move = playHard();
  }

  Serial.println("Played");
  return ai_move;
}

int playHard() {
  int ai_move = tryWin();;
  int i = 0;
  while(!checkMove(ai_move)) {
    for(i = 0; i < 9; i++) {
      if(board[0] == board[1] && board[0] == 1 && board[2] == 0) {
        ai_move = 2;
      } else if(board[0] == board[2] && board[0] == 1 && board[1] == 0) {
        ai_move = 1;
      } else if(board[1] == board[2] && board[1] == 1 && board[0] == 0) {
        ai_move = 0;
        
      } else if(board[0] == board[3] && board[0] == 1 && board[6] == 0) {
        ai_move = 6;
      } else if(board[0] == board[6] && board[0] == 1 && board[3] == 0) {
        ai_move = 3;
      } else if(board[3] == board[6] && board[5] == 1 && board[0] == 0) {
        ai_move = 0;
      }
  
      else if(board[5] == board[4] && board[5] == 1 && board[3] == 0) {
        ai_move = 3;
      } else if(board[5] == board[3] && board[5] == 1 && board[4] == 0) {
        ai_move = 4;
      } else if(board[4] == board[3] && board[4] == 1 && board[5] == 0) {
        ai_move = 5;
      }
  
      else if(board[6] == board[7] && board[6] == 1 && board[8] == 0) {
        ai_move = 8;
      } else if(board[6] == board[8] && board[6] == 1 && board[7] == 0) {
        ai_move = 7;
      } else if(board[7] == board[8] && board[7] == 1 && board[6] == 0) {
        ai_move = 6;
      }
  
      else if(board[1] == board[4] && board[1] == 1 && board[7] == 0) {
        ai_move = 7;
      } else if(board[1] == board[7] && board[1] == 1 && board[4] == 0) {
        ai_move = 4;
      } else if(board[4] == board[7] && board[4] == 1 && board[1] == 0) {
        ai_move = 1;
      }
  
      else if(board[2] == board[5] && board[2] == 1 && board[8] == 0) {
        ai_move = 8;
      } else if(board[2] == board[8] && board[2] == 1 && board[5] == 0) {
        ai_move = 5;
      } else if(board[5] == board[8] && board[3] == 1 && board[2] == 0) {
        ai_move = 2;
      }
  
      else if(board[0] == board[4] && board[0] == 1 && board[8] == 0) {
        ai_move = 8;
      } else if(board[0] == board[8] && board[0] == 1 && board[4] == 0) {
        ai_move = 4;
      } else if(board[4] == board[8] && board[4] == 1 && board[0] == 0) {
        ai_move = 0;
      }
  
      else if(board[2] == board[4] && board[2] == 1 && board[6] == 0) {
        ai_move = 6;
      } else if(board[2] == board[6] && board[2] == 1 && board[4] == 0) {
        ai_move = 4;
      } else if(board[4] == board[6] && board[4] == 1 && board[2] == 0) {
        ai_move = 2;
      }
  
      else {
        ai_move = (in_cmd + random(0, 8)) / 2;
      }
    }
  }
  return ai_move;
}

int tryWin(){

    int index = 0;
    int i = 0;
    for(i = 0; i < 9; i++) {
      if(board[0] == board[1] && board[0] == 2 && board[2] == 0) {
        index = 2;
      } else if(board[0] == board[2] && board[0] == 2 && board[1] == 0) {
        index = 1;
      } else if(board[1] == board[2] && board[1] == 2 && board[0] == 0) {
        index = 0;
        
      } else if(board[0] == board[3] && board[0] == 2 && board[6] == 0) {
        index = 6;
      } else if(board[0] == board[6] && board[0] == 2 && board[3] == 0) {
        index = 3;
      } else if(board[3] == board[6] && board[5] == 2 && board[0] == 0) {
        index = 0;
      }
  
      else if(board[5] == board[4] && board[5] == 2 && board[3] == 0) {
        index = 3;
      } else if(board[5] == board[3] && board[5] == 2 && board[4] == 0) {
        index = 4;
      } else if(board[4] == board[3] && board[4] == 2 && board[5] == 0) {
        index = 5;
      }
  
      else if(board[6] == board[7] && board[6] == 2 && board[8] == 0) {
        index = 8;
      } else if(board[6] == board[8] && board[6] == 2 && board[7] == 0) {
        index = 7;
      } else if(board[7] == board[8] && board[7] == 2 && board[6] == 0) {
        index = 6;
      }
  
      else if(board[1] == board[4] && board[1] == 2 && board[7] == 0) {
        index = 7;
      } else if(board[1] == board[7] && board[1] == 2 && board[4] == 0) {
        index = 4;
      } else if(board[4] == board[7] && board[4] == 2 && board[1] == 0) {
        index = 1;
      }
  
      else if(board[2] == board[5] && board[2] == 2 && board[8] == 0) {
        index = 8;
      } else if(board[2] == board[8] && board[2] == 2 && board[5] == 0) {
        index = 5;
      } else if(board[5] == board[8] && board[3] == 2 && board[2] == 0) {
        index = 2;
      }
  
      else if(board[0] == board[4] && board[0] == 2 && board[8] == 0) {
        index = 8;
      } else if(board[0] == board[8] && board[0] == 2 && board[4] == 0) {
        index = 4;
      } else if(board[4] == board[8] && board[4] == 2 && board[0] == 0) {
        index = 0;
      }
  
      else if(board[2] == board[4] && board[2] == 2 && board[6] == 0) {
        index = 6;
      } else if(board[2] == board[6] && board[2] == 2 && board[4] == 0) {
        index = 4;
      } else if(board[4] == board[6] && board[4] == 2 && board[2] == 0) {
        index = 2;
      }
  
      else {
        index = in_cmd-1;
      }
//      Serial.println(ai_move);
    }
    
  return index;
}

bool checkMove(int index) {
//  if(index > 8) {
//    return false;
//  }
  if(board[index] != 0) {
    return false;
  }
  return true;
}

void updateBoard() {
  int i = 0;
  int tmp = 0;
//      Serial.println("Board");
  for(i = 0; i < 9; i++) {

//    Serial.print(board[i]);
    tmp = i;
    if(board[tmp] == 1) {
//      Serial.println("tmp:");
//      Serial.println(tmp);
      if(tmp == 3) {
        tmp = 5;
      } else if(tmp == 5) {
        tmp = 3;
      }
//      Serial.println(tmp);
      colors[tmp] = rgb_color(255,0,0); // Red
    } else if(board[tmp] == 2) {
      if(tmp == 3) {
        tmp = 5;
      } else if(tmp == 5) {
        tmp = 3;
      }
      colors[tmp] = rgb_color(0,0,255); // Blue
    } 
//    else if(board[tmp] == 0) {
//      colors[tmp] = rgb_color(0,0,0); // Empty
//    }
  }
//  Serial.println("-----");
  ledStrip.write(colors, 9);
  printToPhone();
}

void printToPhone() {

  int i = 0;
  int j = 0;
  for(i = 0; i < 3; i++) {
    int k = 0;
    for(k = 0; k < 3; k++) {
      BTSerial.write(" | ");
      if(board[j] == 1) {
        BTSerial.write("X");
      } else if(board[j] == 2) {
        BTSerial.write("O");
      } else {
        char inx = j + 1 + '0';
        BTSerial.write(inx);
      }
      j++;
    }
    BTSerial.write(" | \n");
    BTSerial.write("---------------- \n");
  }
}

int checkWinner() {
  int game_over = 0;  // Also indicates winner 1,2,3(tied)
  int i = 0;
  
    if(board[0] == board[1] && board[0] == board[2]) {
      game_over = board[0];
    }
    else if(board[0] == board[4] && board[0] == board[8]) {
      game_over = board[0];
    }
    else if(board[0] == board[3] && board[0] == board[6]) {
      game_over = board[0];
    }
    else if(board[1] == board[4] && board[1] == board[7]) {
      game_over = board[1];
    }
    else if(board[2] == board[4] && board[2] == board[6]) {
      game_over = board[2];
    }
    else if(board[2] == board[5] && board[2] == board[8]) {
      game_over = board[2];
    }
    else if(board[3] == board[4] && board[3] == board[5]) {
      game_over = board[3];
    }
    else if(board[6] == board[7] && board[6] == board[8]) {
      game_over = board[6];
    } else {
      for(int i=0; i<9; i++) {    // Check for tied
        if(board[i] == 0) {
          return 0;               // break completely
        }
      }
      game_over = 3;  // Tied
    }

    if(game_over == 0) {
      return 0;
    }

    if(game_over == 1) {
      BTSerial.write("X Wins \n");
    } else if(game_over == 2) {
      BTSerial.write("O Wins \n");
    } else if(game_over == 3) {
      BTSerial.write("A Tie \n");
    }

    int j = 0;
    for(j = 0; j < 10; j++) {
      for(i = 0; i < 9; i++) {
        if(board[i] == game_over) {
          colors[i] = rgb_color(0,0,0);
          board[i] = 0;
        } else if (board[i] == 0) {
          if(game_over == 1) {
            colors[i] = rgb_color(255,0,0); // Red
            board[i] = 1;
          } else if(game_over == 2) {
            board[i] = 2;
            colors[i] = rgb_color(0,0,255); // Blue
          }            
        }
      }
      ledStrip.write(colors, 9);
      delay(500);
    }

    while(1){
      
    }
}

void resetGame() {
  int i = 0;
  for(i = 0; i < 9; i++) {
    colors[i] = rgb_color(0,0,0);
    board[i] = 0;
  }
  ledStrip.write(colors, 9);
  ai_turn = false;
}

int initGame() {
  if(play) {
    return 0;
  }
  resetGame();
 
  BTSerial.write("Select Level: 0-1-2 \n");

  lvl = 3;
  while(lvl > 2) {
     if (BTSerial.available() > 0) {
        lvl = BTSerial.read();
        lvl = lvl - 48;
//        Serial.println(lvl);
     }
  }
  printToPhone();
  play = true;
  BTSerial.write("Your turn \n");
  return 0;
}


