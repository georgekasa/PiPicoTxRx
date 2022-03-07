#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
int motor_control_PWM1 = 6;
int controlDirection1 = 3;
int motor_control_PWM2 = 5;
int controlDirection2 = 2;

const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);
  pinMode(motor_control_PWM1,OUTPUT);
  pinMode(controlDirection1,OUTPUT);
  digitalWrite(controlDirection1,LOW);
  pinMode(motor_control_PWM2,OUTPUT);
  pinMode(controlDirection2,OUTPUT);
  digitalWrite(controlDirection2 ,LOW);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
 // Serial.println("hi");
  delay(1000);
  if (radio.available()) {
    int dummy [2] = {0, 0};
    radio.read(&dummy, sizeof(dummy));
    Serial.println(dummy[0]);
    Serial.println(dummy[1]);
    if (dummy[0] == 1){
      digitalWrite(controlDirection2,HIGH);
      analogWrite(motor_control_PWM2 , 150);   
    }else if( dummy[1] == 1){
      digitalWrite(controlDirection1,HIGH);
      analogWrite(motor_control_PWM1, 150); 
    }
  }
}
