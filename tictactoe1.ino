#include <stdlib.h>

class button{
  public:
  bool on;
  int pin;
  button(int pin){
    this->pin = pin;
    on = false;
  }  
};

class ButtonController{
  public:
  button* buttons[9];
  int block;
  ButtonController(){
    block = 0;
    buttons[0] = new button(11);
    buttons[1] = new button(12);
    buttons[2] = new button(13);
    buttons[3] = new button(A0);
    buttons[4] = new button(A1);
    buttons[5] = new button(A2);
    buttons[6] = new button(A3);
    buttons[7] = new button(A4);
    buttons[8] = new button(A5);

  }

  int Click(int pin,int Signal){
    if(Signal == 1023 || Signal == HIGH){
        for(int i= 0;i<9;i++){
            if(pin==buttons[i]->pin && !buttons[i]->on){
                buttons[i]->on = true;
            }
        }
    }
  }
};

ButtonController* buttonCtrl;

class LED{
  public:
  int pin;
  bool on;
  bool player;
  

  LED(int pin){
    on = false;
    this->pin = pin;
  }
  
  bool start(bool player){
    bool on1 = on;
    if(on){
      player = this->player;
    }    
      if(player){
        digitalWrite(pin, HIGH);
      }
      else{
        digitalWrite(pin, HIGH);
        delay(50);
        digitalWrite(pin, LOW);
      }
      this->player = player; 
      on = true;
      return on1;
    }  
};

class TicTakToe{
  LED *leds[9];
  bool player;
  
  public:
  TicTakToe(){
    for(int i=0;i<9;i++){
      leds[i] = new LED(i+2);
    }
    player = true;
  };
  bool win(){
    for(int i=0;i<2;i++){
      if(leds[0]->on == true && leds[0]->player == i && leds[1]->on == true && leds[1]->player == i && leds[2]->on == true && leds[2]->player == i || leds[3]->on == true && leds[3]->player == i && leds[4]->on == true && leds[4]->player == i && leds[5]->on == true && leds[5]->player == i || leds[6]->on == true && leds[6]->player == i && leds[7]->on == true && leds[7]->player == i && leds[8]->on == true && leds[8]->player == i || leds[0]->on == true && leds[0]->player == i && leds[4]->on == true && leds[4]->player == i && leds[8]->on == true && leds[8]->player == i || leds[2]->on == true && leds[2]->player == i && leds[4]->on == true && leds[4]->player == i && leds[6]->on == true && leds[6]->player == i || leds[0]->on == true && leds[0]->player == i && leds[3]->on == true && leds[3]->player == i && leds[6]->on == true && leds[6]->player == i || leds[1]->on == true && leds[1]->player == i && leds[4]->on == true && leds[4]->player == i && leds[7]->on == true && leds[7]->player == i || leds[2]->on == true && leds[2]->player == i && leds[5]->on == true && leds[5]->player == i && leds[8]->on == true && leds[8]->player == i){
        Serial.println("win");  
        buttonCtrl->block = true;
      }
    } 
  }
  void startLED(int ledNUM){
      if(!leds[ledNUM-1]->start(player)){
        player = !player;
      }
  }
  void refresh(){
    for(int i = 0;i<9;i++){
      if(buttonCtrl->buttons[i]->on){
        this->startLED(i+1);
        delay(50); 
      }  
    }  
  }
};

TicTakToe* game;

void setup() {
  // put your setup code here, to run once:

  for(int i=2;i<11;i++){
    pinMode(i, OUTPUT);
  }
  for(int i=11;i<14;i++){
    pinMode(i, INPUT);
  }
  game = new TicTakToe();  
  buttonCtrl = new ButtonController();   
  Serial.begin(9600);
}
void loop() {
  game->win();
  if(!buttonCtrl->block){
    buttonCtrl->Click(11,digitalRead(11));
    buttonCtrl->Click(12,digitalRead(12));
    buttonCtrl->Click(13,digitalRead(13));
    buttonCtrl->Click(A0,analogRead(A0));
    buttonCtrl->Click(A1,analogRead(A1));
    buttonCtrl->Click(A2,analogRead(A2));
    buttonCtrl->Click(A3,analogRead(A3));
    buttonCtrl->Click(A4,analogRead(A4));
    buttonCtrl->Click(A5,analogRead(A5));
  }
  game->refresh();
}