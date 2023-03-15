/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2022 mobizt
 *
*/

//Example shows how to connect to Firebase RTDB and perform basic operation for set, get, push and update data to database

//Required WiFiNINA Library for Arduino from https://github.com/arduino-libraries/WiFiNINA

#include "Firebase_Arduino_WiFiNINA.h"

#define DATABASE_URL "pdsarduino-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define DATABASE_SECRET "T2iNWYJx25HmL8fXhqwTt6pIVjZnZ2HxPk31BaQu"
#define WIFI_SSID "SUTD_IOT"
#define WIFI_PASSWORD ""
#include "SparkFun_LIS331.h"
#include <Wire.h>
#include <Thread.h>
#include <ThreadController.h>


LIS331 xl;

// ThreadController that will controll all threads
ThreadController controll = ThreadController();
//My Thread (as a pointer)
Thread* myThread = new Thread();
//His Thread (not pointer)
Thread hisThread = Thread();
//Define Firebase data object
FirebaseData fbdo;

//Define Pins
int motor_pin = 5;
int status_pin = 6;

//global values
int power = 0;
bool enable = false; 
bool start_condition = false;

void setup()
{
//Firebase
  delay(100);
  Serial.println();

  Serial.print("Connecting to Wi-Fi");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //Provide the autntication data
  Firebase.begin(DATABASE_URL, DATABASE_SECRET, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);

  String path = "/pdsproj";
  String jsonStr;

  Serial.print("Set int... ");

  unsigned long long val = 1634631042000;

  //set up motor controller L295N
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(1, HIGH);

 

  // clear internal memory used
  fbdo.clear();
  //end of firebase
  //3 axis accelerometer
  // put your setup code here, to run once:
  pinMode(2,INPUT);       // Interrupt pin input
  Wire.begin();
  xl.setI2CAddr(0x19);    // This MUST be called BEFORE .begin() so 
                          //  .begin() can communicate with the chip
  xl.begin(LIS331::USE_I2C); // Selects the bus to be used and sets
                          //  the power up bit on the accelerometer.
                          //  Also zeroes out all accelerometer
                          //  registers that are user writable.
  // This next section configures an interrupt. It will cause pin
  //  INT1 on the accelerometer to go high when the absolute value
  //  of the reading on the Z-axis exceeds a certain level for a
  //  certain number of samples.
  xl.intSrcConfig(LIS331::INT_SRC, 1); // Select the source of the
                          //  signal which appears on pin INT1. In
                          //  this case, we want the corresponding
                          //  interrupt's status to appear. 
  xl.setIntDuration(10, 1); // Number of samples a value must meet
                          //  the interrupt condition before an
                          //  interrupt signal is issued. At the
                          //  default rate of 50Hz, this is one sec.
  xl.setIntThreshold(2, 1); // Threshold for an interrupt. This is
                          //  not actual counts, but rather, actual
                          //  counts divided by 16.
  xl.enableInterrupt(LIS331::Z_AXIS, LIS331::TRIG_ON_HIGH, 1, true);
                          // Enable the interrupt. Parameters indicate
                          //  which axis to sample, when to trigger
                          //  (in this case, when the absolute mag
                          //  of the signal exceeds the threshold),
                          //  which interrupt source we're configuring,
                          //  and whether to enable (true) or disable
                          //  (false) the interrupt.
  Serial.begin(115200);
  start_condition = true;
  pinMode(status_pin, OUTPUT);
  pinMode(motor_pin, OUTPUT);
  // Configure myThread
  myThread->onRun(accel);
  myThread->setInterval(500);

  // Configure myThread
  hisThread.onRun(detect);
  hisThread.setInterval(250);

  // Adds both threads to the controller
  controll.add(myThread);
  controll.add(&hisThread); // & to pass the pointer to it


}

void accel() //callback for acceleormeter
{
  String path = "/pdsproj";
  int prev = 0;
  int diff =0;
  bool cool = false;
  static long loopTimer = 0;
  int16_t x, y, z;
  if ((millis() - loopTimer > 800) && (start_condition == true))
  { 
    digitalWrite(status_pin,HIGH);
    loopTimer = millis();
    xl.readAxes(x, y, z);  // The readAxes() function transfers the
                           //  current axis readings into the three
                           //  parameter variables passed to it.
   // Calculate magnitude of acceleration
      float accel_mag = sqrt((x * x) + (y*y)+ (z*z));
   // Calculate pitch and roll angles in radians
      float pitch = atan2(x, sqrt(y * y + z * z));
      float roll = atan2(y, sqrt(x*x +z*z));

  // Convert pitch and roll angles to degrees
    float pitch_deg = pitch * 180.0 / PI;
    float roll_deg = roll * 180.0 / PI;
   
    Serial.println("X:" +String(x));
    Serial.println("Y:" + String(y));
    Serial.println("Z:" + String(z));
    Serial.println("Pitch :" + String(pitch_deg));
    Serial.println("Roll :" + String(roll_deg));
    //Serial.println(xl.convertToG(6,x)); // The convertToG() function
    //Serial.println(xl.convertToG(6,y)); // accepts as parameters the
    //Serial.println(xl.convertToG(6,z)); // raw value and the current
    Serial.println(" ");                // maximum g-rating.
    //Firebase.setFloat(fbdo, path + "/push/pitch", pitch_deg);
    Firebase.setFloat(fbdo, path + "/push/roll", roll_deg);
    diff = abs(prev-pitch_deg);
    if ((diff>10) && (enable==true))
    {
      Serial.println("Move");
      analogWrite(motor_pin,power);
      delay(2000);
    }
    else
    {
      analogWrite(motor_pin,0);
    }
    
    prev = pitch; 
  }
  else
  {
        digitalWrite(status_pin,LOW); //light off
  }
  if (digitalRead(2) == HIGH)
  {
    Serial.println("Interrupt");
  }



}

 void detect()
 {
 String path = "/pdsproj";
 Firebase.getString(fbdo, "/pdsproj/pdsproj/enable");
 String temp1 = fbdo.stringData();
 Firebase.getString(fbdo, "/pdsproj/pdsproj/power");
 String temp2 = fbdo.stringData();
 if (temp1 == "true")
 {
  enable = true;
 }
 if (temp1 == "false")
 {
  enable = false;
 }
 power = temp2.toInt();



 }
 


void loop()
{
  controll.run();
}
