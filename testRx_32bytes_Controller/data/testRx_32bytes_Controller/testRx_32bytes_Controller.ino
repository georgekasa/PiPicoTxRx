
#include <SPI.h>
#include "printf.h"
#include "RF24.h"

RF24 radio(22, 17); // using pin 7 for the CE pin, and pin 8 for the CSN pin 14 17
uint8_t address[][6] = {"1Node", "2Node"};
bool radioNumber; // 0 uses address[0] to transmit, 1 uses address[1] to transmit
bool role = false; // false= RX node
#define SIZE 20            // this is the maximum for this example. (minimum is 1)
int counter = 0;       // for counting the number of received payloads
const int STBY = 11; 
const int Motor1DirectionPWM_A = 12; 
const int Motor1DirectionPWM_B = 13; 
const int Motor2DirectionPWM_A = 14; 
const int Motor2DirectionPWM_B = 15; 
 //TO KITRONIC exei tin vlakia IN1 & IN2 na mporeis na peksis me auta ta pwm kai to direction den exei dedicated pins gia PWM mono
boolean movedLeft = false;
boolean movedRight = false;

void setup(){


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
  radio.setPayloadSize(4);     // default value is the maximum 32 bytes
  radio.enableDynamicPayloads();
  radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0
  radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1
  float ackData = 1.0;
  radio.writeAckPayload(1, &ackData, sizeof(ackData)); // pre-load data

  // additional setup specific to the node's role
  if (role) {
    radio.stopListening();  // put radio in TX mode
  } else {
    radio.startListening(); // put radio in RX mode
  }
  //////Control/////////////////////////
  pinMode(STBY, OUTPUT);
  pinMode(Motor1DirectionPWM_A, OUTPUT);
  pinMode(Motor1DirectionPWM_B, OUTPUT);
  pinMode(Motor2DirectionPWM_A, OUTPUT);
  pinMode(Motor2DirectionPWM_B, OUTPUT);
  //initialize
  digitalWrite(STBY, LOW);//
  digitalWrite(Motor1DirectionPWM_A, LOW);//
  digitalWrite(Motor1DirectionPWM_B, LOW);//
  digitalWrite(Motor2DirectionPWM_A, LOW);//
  digitalWrite(Motor2DirectionPWM_B, LOW);//
} 

void loop() {
  if (counter ==0 ){Synchronize();}
  digitalWrite(STBY, HIGH);
  radio.setPayloadSize(SIZE);
  if (!role) {
      uint8_t pipe;
      if (radio.available(&pipe)) { 
        float text [5];  
        uint8_t bytes = radio.getPayloadSize();
        radio.read(&text, bytes);     // fetch payload from FIFO
        movement(text[1], text[2], text[3], text[4], text[0]);
        Serial.println(text[1]);
        Serial.println(F("Received: "));
    }
    delay(300);  // slow transmissions down by 1 seco
  }
} // loop

int returnGear(float GearLevel){
  if ( GearLevel == 0){
    return 0;
  }else if (GearLevel == 1){
    return 50;
  }else if (GearLevel == 2){
    return 100;
  }else if (GearLevel == 3){
    return 150;
  }else if (GearLevel == 4){
    return 200;
  }else{
    return 255;
  }
}
void movement(float Up, float Down, float Left, float Right, float GearLevel){
  int PwmMotor1Value = returnGear(GearLevel);
  Serial.println(PwmMotor1Value);
  if ( Up == 1.0 && Left == 1.0){
    digitalWrite(Motor1DirectionPWM_B, LOW);//UP
    digitalWrite(Motor2DirectionPWM_B, LOW);//LEFT
    analogWrite(Motor1DirectionPWM_A, PwmMotor1Value);
    analogWrite(Motor2DirectionPWM_A, 200);
    movedLeft = true;
    movedRight = false;
  }else if ( Up == 1.0 && Right == 1.0){
    digitalWrite(Motor1DirectionPWM_B, LOW);//UP
    digitalWrite(Motor2DirectionPWM_A, LOW);//RIGHT
    analogWrite(Motor1DirectionPWM_A, PwmMotor1Value); 
    analogWrite(Motor2DirectionPWM_B, 200);
    movedRight = true;
    movedLeft = false;
  }else if ( Down == 1.0 && Left == 1.0){
    digitalWrite(Motor1DirectionPWM_A, LOW);//DOWN
    digitalWrite(Motor2DirectionPWM_B, LOW);//LEFT
    analogWrite(Motor1DirectionPWM_B, PwmMotor1Value);   
    analogWrite(Motor2DirectionPWM_A, 200);
    movedLeft = true;
    movedRight = false;
  }else if ( Down == 1.0 && Right == 1.0){
    digitalWrite(Motor1DirectionPWM_A, LOW); //DOWN
    digitalWrite(Motor2DirectionPWM_A, LOW);  //RIGHT
    analogWrite(Motor1DirectionPWM_B, PwmMotor1Value); 
    analogWrite(Motor2DirectionPWM_B, 200);
    movedRight = true;
    movedLeft = false;
  }else if ( Up == 1.0){
    if (movedRight){
      digitalWrite(Motor2DirectionPWM_B, LOW);//turn left theli servo kanonika auto
      analogWrite(Motor2DirectionPWM_A, 200);
    }else if (movedLeft){
      digitalWrite(Motor2DirectionPWM_A, LOW);
      analogWrite(Motor2DirectionPWM_B, 200);
    } 
    digitalWrite(Motor1DirectionPWM_B, LOW);
    analogWrite(Motor1DirectionPWM_A, PwmMotor1Value);

    movedLeft = false;
    movedRight = false;
  }else if (Down == 1.0){
    if (movedRight){
      digitalWrite(Motor2DirectionPWM_B, LOW);//turn left theli servo kanonika auto
      analogWrite(Motor2DirectionPWM_A, 200);
    }else if (movedLeft){
      digitalWrite(Motor2DirectionPWM_A, LOW);
      analogWrite(Motor2DirectionPWM_B, 200);
    } 
    digitalWrite(Motor1DirectionPWM_A, LOW);
    analogWrite(Motor1DirectionPWM_B, PwmMotor1Value);
    movedLeft = false;
    movedRight = false;
  }else if (Left == 1.0){
    digitalWrite(Motor2DirectionPWM_B, LOW);
    analogWrite(Motor2DirectionPWM_A, 200);
    digitalWrite(Motor1DirectionPWM_A, LOW);//idle mode
    digitalWrite(Motor1DirectionPWM_B, LOW);//idle mode
    movedLeft = true;
    movedRight = false;
  }else if (Right == 1.0){
    digitalWrite(Motor2DirectionPWM_A, LOW);
    analogWrite(Motor2DirectionPWM_B, 200);
    digitalWrite(Motor1DirectionPWM_A, LOW);//idle mode
    digitalWrite(Motor1DirectionPWM_B, LOW);//idle mode
    movedRight = true;
    movedLeft = false;
  }else{
    analogWrite(Motor1DirectionPWM_A, 0);//idle mode
    analogWrite(Motor1DirectionPWM_B, 0);
    analogWrite(Motor2DirectionPWM_A, 0);
    analogWrite(Motor2DirectionPWM_B, 0);
    movedRight = false;
    movedLeft = false;
  }
}

void Synchronize(){
radio.setPayloadSize(4);
float dummy = 1;
  while( true ){
      float dataReceived = 0.0;
      if ( radio.available() ) {
          radio.read( &dataReceived, sizeof(dataReceived) );
          Serial.print("received ack");
          Serial.println(dataReceived);
            if (dataReceived == 1.0){
            radio.writeAckPayload(1, &dummy, sizeof(dummy));
            counter = 1;
            break;
            }
      }
      delay(100);
  }
}
