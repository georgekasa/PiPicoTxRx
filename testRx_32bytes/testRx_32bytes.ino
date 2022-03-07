
#include <SPI.h>
#include "printf.h"
#include "RF24.h"

RF24 radio(22, 17); // using pin 7 for the CE pin, and pin 8 for the CSN pin 14 17
uint8_t address[][6] = {"1Node", "2Node"};
bool radioNumber; // 0 uses address[0] to transmit, 1 uses address[1] to transmit
bool role = false; // false= RX node
#define SIZE 20            // this is the maximum for this example. (minimum is 1)
uint8_t counter = 0;       // for counting the number of received payloads


void setup() {


  Serial.begin(115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {} // hold in infinite loop
  }
  radioNumber = 1;
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
  radio.setPayloadSize(SIZE);     // default value is the maximum 32 bytes
  radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0
  radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

  // additional setup specific to the node's role
  if (role) {
    radio.stopListening();  // put radio in TX mode
  } else {
    radio.startListening(); // put radio in RX mode
  }

} 

void loop() {
  if (!role) {
      uint8_t pipe;
      if (radio.available(&pipe)) { 
        float text [5];  
        uint8_t bytes = radio.getPayloadSize();
        radio.read(&text, bytes);     // fetch payload from FIFO
        Serial.print(F("Received: "));
        Serial.println(text[0]);
        Serial.println(text[4]);
    }
    delay(500);  // slow transmissions down by 1 seco
  }
} // loop
