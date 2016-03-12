//ПЕРЕДАТЧИК

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

const int buttonPin = 5;
int buttonState = 0;
int flag = 0;

const uint64_t pipe = 0xF0F1F2F3F4LL;  //идентификатор передачи "труба"
RF24 radio(9,10);                      //CE, CSN

void setup() {
  pinMode(buttonPin, INPUT);
  
  radio.begin();
  delay(2);
  radio.setChannel(9);                 //канал (0-127)
  radio.setDataRate(RF24_250KBPS);     //скорость, RF24_250KBPS (на nRF24L01 "без +" не работает), RF24_1MBPS, RF24_2MBPS
                                       //меньше скорость, выше чувствительность приемника
  radio.setPALevel(RF24_PA_HIGH);      //мощность передатчика, RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm,
  radio.openWritingPipe(pipe);         //открываем трубу на передачу
}

void loop() {
  buttonState = digitalRead(buttonPin);
    
    if (buttonState == HIGH) {
    flag = 1;
  } else {
    flag = 2;
  }
  
  int data = flag;
  radio.write(&data, sizeof(data));    //отправляем данные и указываем сколько байт
}
