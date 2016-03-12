//ПРИЕМНИК

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

const uint64_t pipe = 0xF0F1F2F3F4LL;  //идентификатор приема "труба"
RF24 radio(9,10);                      //CE, CSN

void setup() {
  pinMode(5, OUTPUT);
  
  radio.begin();
  delay(2);
  radio.setChannel(9);                 //канал (0-127)
  radio.setDataRate(RF24_250KBPS);     //скорость, RF24_250KBPS (на nRF24L01 "без +" не работает), RF24_1MBPS, RF24_2MBPS
                                       //меньше скорость, выше чувствительность приемника
  radio.setPALevel(RF24_PA_HIGH);      //мощность передатчика, RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm,
  radio.openReadingPipe(1, pipe);      //открываем первую трубу с идентификатором "pipe", таких труб может быть 6
  radio.startListening();              //включаем применик, начинаем слушать трубу
  //radio.stopListening();             //останавливаем прием если нужно что-то передать
}

void loop() {
  int data;
  if (radio.available()) {            //проверяем, не пришло ли чего в буфер
   radio.read(&data, sizeof(data));    //читаем данные в переменную, указываем, сколько байт читаем

    if (data == 1) {
      digitalWrite(5, HIGH);
    }
    if (data == 2) {
      digitalWrite(5, LOW);
    }
  }
}
