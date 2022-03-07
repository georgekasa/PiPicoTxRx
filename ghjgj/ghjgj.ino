#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
int motor_control = 6;
int controlDirection = 3;

const byte address[6] = "00001";
void setup() {
  // put your setup code here, to run once:
pinMode(motor_control,OUTPUT);
//pinMode(controlDirection,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
