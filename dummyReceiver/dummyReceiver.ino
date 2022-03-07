#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {

  delay(1000);
  if (radio.available()) {
    int dummy [2] = {0, 0};
    radio.read(&dummy, sizeof(dummy));
    Serial.println(dummy[0]);
    Serial.println(dummy[1]);

  }
}
