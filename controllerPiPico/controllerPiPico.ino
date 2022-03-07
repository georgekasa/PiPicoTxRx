const int buttonUp = 12; 
const int buttonDown = 13;
const int buttonLeft = 14; 
const int buttonRight = 15;
int buttonStateUp = 0; 
int buttonStateDown = 0; 
int buttonStateLeft = 0; 
int buttonStateRight = 0; 
void setup() {
  pinMode(A0,INPUT);
  analogReadResolution(10);
  pinMode(buttonUp, INPUT);
  pinMode(buttonDown, INPUT);
  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);
  Serial.begin(115200);
}
void movement(int UpButton,int DownButton,int LeftButton,int RightButton, int Pwmstate){//otan afinis to buttob tote paei sto 0
  
}
void loop() {
  // put your main code here, to run repeatedly:
  int Potentiometer = analogRead(A0);//31 pin, A1 32; A2 34pin
  Serial.println(Potentiometer);
  Serial.println(map(Potentiometer, 0, 4095, 0, 5));//12 bits adc



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
