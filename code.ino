#include "DigiKeyboard.h"

#define MENU 237
#define ESC 229
#define AUTOPLAY 227
#define ZOOM 232
#define LEFT 236
#define UP 234
#define RIGHT 225
#define DOWN 238
#define ENTER 233

#define IR_PIN 2
#define DATA_SIZE 20
#define START_BIT 4000
int i, s, data[DATA_SIZE];

void setup() 
{
  pinMode(IR_PIN, INPUT);
}

void loop() 
{
  DigiKeyboard.update();
  DigiKeyboard.sendKeyStroke(0);
  
  s = pulseIn(IR_PIN, HIGH);
  if(s > START_BIT)
  {
    for(i = 0; i < DATA_SIZE; i++)
      data[i] = pulseIn(IR_PIN, HIGH);
    
    int result = 0;
    for(i = 12; i < DATA_SIZE; i++)
      if(data[i] > 1000)
        result |= (1 << (DATA_SIZE - 1 - i));

    switch(result)
    {
      case MENU: break;
      case ESC: DigiKeyboard.sendKeyStroke(41); break;
      case AUTOPLAY: break;
      case ZOOM: break;
      case LEFT: DigiKeyboard.sendKeyStroke(0x50); break;
      case RIGHT: DigiKeyboard.sendKeyStroke(0x4f); break;
      case UP: DigiKeyboard.sendKeyStroke(0x52); break;
      case DOWN: DigiKeyboard.sendKeyStroke(0x51); break;
      case ENTER: DigiKeyboard.sendKeyStroke(KEY_ENTER); break;
    }

    delay(400);
  }
}
