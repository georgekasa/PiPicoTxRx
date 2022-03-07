#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "RTClib.h"
#include "SparkFunBME280.h"
BME280 mySensorA; //Uses default I2C address 0x77
//BME280 mySensorB; //Uses I2C address 0x76 (jumper closed)
File myFile;
RTC_DS3231 rtc;
const int chipSelect = 4;
const int tempPin = 1;
int val =0 ;
int counter = 0;
int oldDate [2];
int TimeForFormat[3];
String Filename;
void setup()
{
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
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
   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
   oldDate[0] = 01;
   oldDate[1] = 14;
   rtc.adjust(DateTime(2021,oldDate[0],oldDate[1],19,55,0));
    //////////////////SET DATE////////////////////////////////////////////////////

   Filename = "BME"+setStructureForDate(oldDate)+".txt";
   
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
  if (counter ==0){
  digitalWrite(0, HIGH);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  counter++;
  }else if (counter == 1){
  digitalWrite(0, LOW);
  digitalWrite(1, HIGH);
  digitalWrite(2, LOW); 
  counter++;
  }else if (counter ==2){
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, HIGH);
  counter = 0;
  }

  write_on_sd_card();
  //Serial.println();
  
  delay(1000);
}
void write_on_sd_card(){
  myFile = SD.open(Filename, FILE_WRITE);//prosixi edo mexri kapoion length text name perni
  if (myFile){
       DateTime now = rtc.now();
       TimeForFormat[0] = now.hour();
       TimeForFormat[1] = now.minute();
       TimeForFormat[2] = now.second(); 
      // Serial.println(sizeof(TimeForFormat)/ sizeof(TimeForFormat[0]));
       myFile.println(setStructureForDate(TimeForFormat));
       Serial.println(setStructureForDate(TimeForFormat));
       Serial.println(mySensorA.readTempC());
       myFile.print("Humidity: ");
       myFile.println(mySensorA.readFloatHumidity(), 0);
       myFile.print("Pressure: ");
       myFile.println(mySensorA.readFloatPressure(), 0);
       myFile.print("Temp: ");
       myFile.println(mySensorA.readTempC(), 2);
       set_FileName(now.month(), now.day());
       //LM35//
       val = analogRead(tempPin);
       myFile.print("Temp LM35: ");
       myFile.println(( val/1023.0)*467);
       Serial.println(( val/1023.0)*467);
  }
  myFile.close();
  
}

void set_FileName(int dateToTest, int Month){
  if (dateToTest != oldDate){
    int dummy[] = {Month, dateToTest};
    Filename = "BME" + setStructureForDate(dummy) +".txt";
    oldDate[0] = Month;
    oldDate[1] = dateToTest;}
}

String setStructureForDate(int Array []){
  String dummy ="", date = "";
  //array = hour;minuted;seconds
  //Serial.println(sizeof(Array));
  for (int i =0; i< sizeof(Array); i++){
  
    dummy = String(Array[i]);
    if (dummy.length() <2){
      date += String(0) + String(Array[i]);
    }else{
      date += String(Array[i]);
    }
  }
  return date;
}
