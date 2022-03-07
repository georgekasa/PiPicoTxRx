#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  const int Forward = 1;
  delay(5000);
  radio.write(&Forward, sizeof(Forward));
  delay(5000);
  const int Reverse = 0;
  radio.write(&Reverse, sizeof(Reverse));
  
}
