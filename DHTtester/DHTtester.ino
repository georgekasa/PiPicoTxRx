
#include "DHT.h"
#define DHTPIN 7     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT21   // DHT 21 (AM2301)


#include <LiquidCrystal.h>

// Initialize the library by associating any needed LCD  pins
// with the Arduino Uno pins 
const int rs = 12, en = 11, d4 = 5, d5 = 6, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(5000);

  float h = dht.readHumidity();//get Data from the Sensor Humidity and Temperature
  float t = dht.readTemperature();
  float f = dht.readTemperature(false);


  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

 
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  // Print Values
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println();
  
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.print(t);
  lcd.print(F("°C "));
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
  lcd.print(h);
  lcd.print(F("% "));

  
  if (f <=0 ){
  digitalWrite(8, LOW);   
  digitalWrite(9, LOW);   
  digitalWrite(10, HIGH);  //Turn Blue Led On
  }else if(f> 0 && f<= 35){
  digitalWrite(8, LOW);   
  digitalWrite(9, HIGH);  //Turn Green Led On
  digitalWrite(10, LOW);  
  }else if(f>35){
  digitalWrite(8, HIGH);   
  digitalWrite(9, LOW);  //Turn Red Led On
  digitalWrite(10, LOW);  
    if (f >42){
     // Serial.println("It's Boiling!!!"); 
       // lcd.setCursor(0, 0);
      //  lcd.print("Temperature:");
      //  lcd.print(t);
      //  lcd.print(F("°C "));
     //   lcd.setCursor(0, 1);
     //   lcd.print("It's Boiling!");
    } 
  }else{
   lcd.setCursor(0, 0);
   lcd.print("Something Went Wrong!");
   lcd.print(t);
   digitalWrite(8, HIGH);   //Turn Red Led On
   digitalWrite(9, LOW);  
   digitalWrite(10, LOW);  
    }
 
}
