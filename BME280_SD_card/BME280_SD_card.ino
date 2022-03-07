#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "SparkFunBME280.h"
BME280 mySensorA; //Uses default I2C address 0x77
//BME280 mySensorB; //Uses I2C address 0x76 (jumper closed)
File myFile;
const int chipSelect = 4;
const int tempPin = 1;
int val;
void setup()
{
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  Serial.begin(9600);
  Serial.println("Example showing alternate I2C addresses");

  Wire.begin();

  mySensorA.setI2CAddress(0x77); //The default for the SparkFun Environmental Combo board is 0x77 (jumper open).
  //If you close the jumper it is 0x76
  //The I2C address must be set before .begin() otherwise the cal values will fail to load.

  if(mySensorA.beginI2C() == false) Serial.println("Sensor A connect failed");

   Serial.print("Initializing SD card...");
   if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
   }
  Serial.println("initialization done.");
 
}

void loop()
{
  //Serial.print("Humidity: ");
  //Serial.print(mySensorA.readFloatHumidity(), 0);

  //Serial.print(" Pressure: ");
  //Serial.print(mySensorA.readFloatPressure(), 0);

  //Serial.print(" Temp: ");
  //Serial.print(mySensorA.readTempC(), 2);
  //Serial.print(mySensorA.readTempF(), 2);
  digitalWrite(3, HIGH);
  write_on_sd_card();
  //Serial.println();

  delay(1000);
}
void write_on_sd_card(){
  myFile = SD.open("BME_280.txt", FILE_WRITE);
  if (myFile){
      Serial.println(mySensorA.readTempC());
       myFile.print("Humidity: ");
       myFile.println(mySensorA.readFloatHumidity(), 0);
       myFile.print("Pressure: ");
       myFile.println(mySensorA.readFloatPressure(), 0);
       myFile.print("Temp: ");
       myFile.println(mySensorA.readTempC(), 2);

       //LM35//
       val = analogRead(tempPin);
       myFile.print("Temp LM35: ");
       myFile.println(( val/1023.0)*467);
       Serial.println(( val/1023.0)*467);
  }
  myFile.close();
}
