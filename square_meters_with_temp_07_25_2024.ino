/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with 
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 This example code is in the public domain.
 */
// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include "Adafruit_SHTC3.h"

Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();
byte celsius;
byte fahrenheit;

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int meterP_H9 = 9;           // the PWM pin the LED is attached to
int meterP_M3 = 3;
int meterP_S5 = 5;
int meterP_T11 = 11;
// buttons for setting the time
const int sw_control = 4;
const int sw_hours = 7;
const int sw_minutes = 8;

int saved_second = 0;
int old_second = 0;
int seconds = 0;
int hours = 0;
int minutes = 0;
 // variable for reading the pushbutton status
int buttonState = 0;    
int outer;    
const int ledPin =  13; 
int count;
int meter_hour_A[12] = {0,13,29,44,60,72,88,103,118,132,145,160};
//                      0  1  2  3  4  5  6   7   8   9  10  11  
int meter_minute_A[60] = {0,3,6,9,12,15,18,21,24,27,30,33,36,39,41,44,48,51,54,57,60,63,66,69,72,75,78,81,84,87,90,93,96,99,102,105,108,111,114,117,120,123,126,129,133,136,139,142,145,148,151,154,157,160,163,166,169,172,175,178};
//                        0 1 2 3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31  32 33 34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54  55  56  57  58  59   

int meter_second_A[60] = {0,3,6,9,12,15,18,21,24,27,30,33,36,39,41,44,48,51,54,57,60,63,66,69,72,75,78,81,84,87,90,93,96,99,102,105,108,111,114,117,120,123,126,129,133,136,139,142,145,148,151,154,157,160,163,166,169,172,175,178};
//                        0 1 2 3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33  34  35  36  37  38  39  40  41  42  43  44  45  56  47  48  49  50  51  52  53  54  55  56  57 58   59   

int meter_temp_A[30] = {  0,6,12,18,24,30,36,42,48,54,60,66,72,78,84,90,96,102,108,114,120,126,136,142,148,154,160,166,172,178};
//                        0 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16  17  18  19  20  21  22  23  24  25  26  27  28  29   


int meter_temp;
int meter_hour;
int meter_minute;
int meter_second;
int hour_offset;
int minute_offset;
int second_offset;
int offset;
int year;
int month;
int day;
//int pulse_6=6;
//int pulse_10=10;
//int pulse_11=11;
//int fivevolt = 227;
int counts = 0;
int counter = 0;
int loop_flag = 0; 

// the setup routine runs once when you press reset:
void setup() {
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  Serial.begin(9600);

  delay(3000); // wait for console opening

  if (! rtc.begin()) {
   Serial.println("Couldn't find RTC");
    while (1);
  }
if (! shtc3.begin()) {
    Serial.println("Couldn't find SHTC3");
     while (1) delay(1);
  }
  Serial.println("Found SHTC3 sensor");

//  if (rtc.lostPower()) {
//    Serial.println("RTC lost power, lets set the time!");
// following line sets the RTC to the date & time this sketch was compiled
//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
// This line sets the RTC with an explicit date & time, for example to set
// January 21, 2014 at 3am you would call:
 //************ 
 //************ set the date/time/ ************** 
 //  rtc.adjust(DateTime(2024, 7, 23, 1, 48, 30));


// }
  

// Positive H, M, S, pins  
  pinMode(meterP_H9, OUTPUT);
  pinMode(meterP_M3, OUTPUT);
  pinMode(meterP_S5, OUTPUT);
  pinMode(meterP_T11, OUTPUT);
  analogWrite(meterP_H9, 0);
  analogWrite(meterP_M3, 0); 
  analogWrite(meterP_S5, 0);  
  analogWrite(meterP_T11,0);
// Setup Time Control Switches
  pinMode(ledPin,OUTPUT);
  pinMode(sw_control, INPUT);
  pinMode(sw_hours, INPUT);
  pinMode(sw_minutes, INPUT);
  digitalWrite(ledPin, LOW);
  Serial.println("begin");
 
//   analogWrite (3,5);
   
//   delay (10000);
//   analogWrite (3,180);
   
//   delay (10000);
   
//  for (outer=0; outer<50; outer++) {
//  for (count=5;  count<190; count++) {
//     analogWrite(3, count);
//     Serial.println(count, DEC);
//     delay (100);
//  }
  
//  }
}

// the loop routine runs over and over again forever:
void loop() {
/*   
   while (1==1) {
    for (meter_hour=0; meter_hour<=11; meter_hour++) {
       analogWrite(meterP_H9,meter_hour_A[meter_hour]);
       delay(200);
    }
    analogWrite(meterP_H9,0);
   
    for (meter_minute=0; meter_minute<=59; meter_minute++) {
       analogWrite(meterP_M3,meter_minute_A[meter_minute]);
      delay(50);
   }
   analogWrite(meterP_M3,0);
   

    for (meter_second=0; meter_second<=59; meter_second++) {
       analogWrite(meterP_S5,meter_second_A[meter_second]);
      delay(50);
   
   analogWrite(meterP_S5,0);
   
   for (meter_temp=0; meter_temp<=30; meter_temp++) {
       analogWrite(meterP_T11,meter_temp_A[meter_temp]);
      delay(50);
   }
   analogWrite(meterP_T11,0);
   */
    
  
    buttonState = digitalRead(sw_control);
    if (buttonState == LOW) {
//  get the current time      
      DateTime now = rtc.now();
//  get the temp and humidity
      sensors_event_t humidity, temp;
      shtc3.getEvent(&humidity, &temp);
//  populate temp and humidity objects with fresh data
      fahrenheit=(temp.temperature*1.8)+32;
      if (fahrenheit>79)
         fahrenheit=79;
      if (fahrenheit<0)
         fahrenheit=0;
// get the time from the RTC
      year     =   now.year();
      day      =   now.day();
      month    =   now.month();
      meter_hour = now.hour();
      meter_minute = now.minute();
      meter_second = now.second();
      saved_second= meter_second;
      meter_temp=fahrenheit-50;
      if (saved_second != old_second)
      {
       old_second = saved_second;  
       if (meter_second>=60)  
        meter_second=0;
        
      
// for 12 hour meter subtrack the pm hours
     if (meter_hour >= 12)        
          meter_hour = 0;
     hours=0;
    
// hours and minutes plus fractions of the hour and minutes
          if (meter_hour<10)
            Serial.print("0");
          Serial.print(meter_hour,DEC);
          Serial.print(":");
          if (meter_minute<10)
            Serial.print("0");
          Serial.print(meter_minute,DEC);
          Serial.print(":");
          if (meter_second<10)
            Serial.print("0");
          Serial.print(meter_second,DEC);
          Serial.print(" Temp:");
          Serial.print(fahrenheit,DEC);
          Serial.print(" temp index: ");
          Serial.print(meter_temp,DEC);
          Serial.println();

          write_hour();
          write_minute();
          write_second();
          write_temp();
          delay(800);
    }
    }
    else
    {
     digitalWrite(ledPin, HIGH);
     meter_second=0;
     write_second();
 //    while (digitalRead(sw_control) == HIGH) 
     delay (500);
     loop_flag=1;
     while (loop_flag) 
     {
     //Hours set
      digitalWrite(ledPin,LOW);
      delay(200);
      digitalWrite(ledPin,HIGH);
      delay(200);
      buttonState = digitalRead(sw_hours);
      if (buttonState == HIGH)
      {
        while (digitalRead(sw_hours) == HIGH) 
          delay (200);
        minute_offset=0;
        meter_hour=meter_hour+1;
        if (meter_hour>12)
          meter_hour=0;
        Serial.print(meter_hour, DEC);
        Serial.println();
        write_hour();    
       }
//minutes set  
       buttonState = digitalRead(sw_minutes);
       if (buttonState == HIGH)
       {
       while (digitalRead(sw_minutes) == HIGH) 
          delay (200);
       meter_minute=meter_minute+1;
       if (meter_minute>=60)
          meter_minute=0;
       Serial.print(meter_minute, DEC); 
       Serial.println();  
       write_minute();    
       }
//return button
       buttonState = digitalRead(sw_control);
       if (buttonState == LOW)
       {
        delay (500);
        Serial.print("control button pressed to return");
        Serial.println();
        loop_flag=0;
        digitalWrite(ledPin, LOW);
        rtc.adjust(DateTime(year, month, day, meter_hour, meter_minute, 0));
        }
     }
     
     }
   }

//  write to hour meter  
    void write_hour()
    {
      if (meter_minute>29)
        analogWrite(meterP_H9,meter_hour_A[meter_hour]+7); 
      else 
        analogWrite(meterP_H9,meter_hour_A[meter_hour]);
    }
// write to minute meter  
    void write_minute()  
    {
     analogWrite(meterP_M3,meter_minute_A[meter_minute]);
    }
 // write to second meter
    void write_second()
    {
     analogWrite(meterP_S5,meter_second_A[meter_second]);
    }
     void write_temp()
    {
      analogWrite(meterP_T11,meter_temp_A[meter_temp]); 
    }
    

