#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int pushButtonL = 2;
int pushButtonR = 3;
int buttonStateL = 0;
int buttonStateR = 0;
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  pinMode(pushButtonL, INPUT);
  pinMode(pushButtonR, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  radio.flush_tx();
  buttonStateL = digitalRead(pushButtonL);
  buttonStateR = digitalRead(pushButtonR);
  int array[2] = {1, 0};
  delay(1000);
  radio.write(&array, sizeof(array));
  
}
