//Initializing LED Pin
int motor_control = 6;//the PWM pins are 3, 5, 6, 9, 10 and 11
int motor_direction = 11;
void setup() {
  Serial.begin(9600);
  //Declaring LED pin as output
  pinMode(motor_control, OUTPUT);
  pinMode(motor_direction, OUTPUT);
}
void loop() {
  //Fading the LED

    analogWrite(motor_control, 50);
    Serial.println("20");
    delay(4000);
    analogWrite(motor_control, 100);
    Serial.println("100");    
    delay(4000);
    analogWrite(motor_control, 200);
    Serial.println("200");  
    delay(4000);                                                                    
}
