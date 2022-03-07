
#include <SPI.h>
#include "printf.h"
#include "RF24.h"

RF24 radio(22,17); // using pin 7 for the CE pin, and pin 8 for the CSN pin
uint8_t address[][6] = {"1Node", "2Node"};
bool radioNumber; // 0 uses address[0] to transmit, 1 uses address[1] to transmit
bool role = true; // true = TX node
#define SIZE 20            // this is the maximum for this example. (minimum is 1)



///////////////////////////
//////Controller//////////
const int adc_bits = 10; 
const int buttonUp = 12; 
const int buttonDown = 13;
const int buttonLeft = 14; 
const int buttonRight = 15;
int buttonStateUp = 0; 
int buttonStateDown = 0; 
int buttonStateLeft = 0; 
int buttonStateRight = 0; 

///////////////////////////

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {} // hold in infinite loop
  }

  Serial.println(F("Starting ..."));

  radioNumber = 0;
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
  radio.setPayloadSize(SIZE);     // default value is the maximum 32 bytes
  radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0
  radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1
  if (role) {
    radio.stopListening();  // put radio in TX mode
  }
  /////////////////////
  ///CONTROLLER///////
  ///////////////////
  pinMode(A0,INPUT);
  analogReadResolution(adc_bits);
  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);
  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);
} // setup()


void loop() {

  if (role) {
    // This device is a TX node
    radio.flush_tx();
    int Potentiometer = analogRead(A0);//#pin 31, A1  #pin 32, A2 #34pin
    float theMessage [5] ={0.0, 0.0, 0.0, 0.0, 0.0};
    theMessage[0] = map(Potentiometer, 0, pow(2, adc_bits - 1), 0, 5);
    theMessage[1] = digitalRead(buttonUp);
    theMessage[2] = digitalRead(buttonDown);
    theMessage[3] = digitalRead(buttonLeft);
    theMessage[4] = digitalRead(buttonRight);


    
    bool report = radio.write(&theMessage, 5*sizeof(float));
      if (report) {//writeFast
        Serial.println("Transmission ok");
       // radio.reUseTX();
      } else {
        Serial.println(F("Transmission failed! ")); 
      }
    }
    delay(500);  // slow transmissions down by 1 seco
} // loop
