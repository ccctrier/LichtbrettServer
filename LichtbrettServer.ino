#include "Tlc5940.h"


void setup()
{
  /* Call Tlc.init() to setup the tlc.
     You can optionally pass an initial PWM value (0 - 4095) for all channels.*/
  Tlc.init(0);
  Tlc.update();
  Serial.begin(9600);
}

namespace Command {
  const unsigned char flushFrame =1;
  const unsigned char setAll =2;
  const unsigned char frame =3;
  const unsigned char indexedFrame =4;
  const unsigned char set =5;
}

void loop() {

  while(Serial.available()) {
      unsigned char command = Serial.read();
      switch(command) {
        case(Command::flushFrame):{
            Tlc.update();
            break;
        }
        case(Command::setAll):{
            uint16_t value=0;
            uint16_t recieved=0;
            while(recieved < sizeof(value)){
              recieved = Serial.readBytes((char*)&value + recieved ,sizeof(value)-recieved);
            }
            Tlc.setAll(value);
            break;
        }
        case(Command::frame):{
            for(uint16_t i =0; i< 3*16; i++){
                uint16_t value=0;
                uint16_t recieved=0;
                while(recieved < sizeof(value)){
                  recieved = Serial.readBytes((char*)&value + recieved ,sizeof(value)-recieved);
                }
                Tlc.set(i,value);
            }
            break;
        }
        case(Command::indexedFrame):{
            uint16_t num=0;
            uint16_t recieved=0;
            while(recieved < sizeof(num)){
              recieved = Serial.readBytes((char*)&num + recieved ,sizeof(recieved)-recieved);
            }
            recieved = 0;
            for(size_t i=0; i<num; i++){
              uint16_t index=0;
              uint16_t value=0;
              while(recieved < sizeof(index)){
                recieved = Serial.readBytes((char*)&index + recieved ,sizeof(index)-recieved);
              }
              recieved =0;
              while(recieved < sizeof(value)){
                recieved = Serial.readBytes((char*)&value + recieved ,sizeof(value)-recieved);
              }
              Tlc.set(index,value);
            }
            break; 
        }
        case(Command::set):{
            uint16_t recieved=0;
            uint16_t index=0;
            uint16_t value=0;
            while(recieved < sizeof(index)){
              recieved = Serial.readBytes((char*)&index + recieved ,sizeof(index)-recieved);
            }
            recieved =0;
            while(recieved < sizeof(value)){
              recieved = Serial.readBytes((char*)&value + recieved ,sizeof(value)-recieved);
            }
            Tlc.set(index,value);
            break;
        }
    }
  } 
}

