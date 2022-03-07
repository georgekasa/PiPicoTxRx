const int buttonUp = 2; 
const int buttonDown = 3;
const int buttonLeft = 6; 
const int buttonRight = 7;
int buttonStateUp = 0; 
int buttonStateDown = 0; 
int buttonStateLeft = 0; 
int buttonStateRight = 0; 
void setup() {
  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);
  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int Potentiometer = analogRead(A0);
  Serial.println(map(Potentiometer, 0, 1023, 0, 5));



  buttonStateUp = digitalRead(buttonUp);
  buttonStateDown = digitalRead(buttonDown);
  buttonStateLeft = digitalRead(buttonLeft);
  buttonStateRight = digitalRead(buttonRight);
  Serial.println(buttonStateUp);
  Serial.println(buttonStateDown);
  Serial.println(buttonStateLeft);
  Serial.println(buttonStateRight);
  delay(1000);
  
}
