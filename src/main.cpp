#include <Arduino.h>

#include <WiFi.h>
#include <FirebaseESP32.h>
#include "../include/secrets.h"


//declare firebase credentials
#define FIREBASE_HOST "https://realtime-database-4721f-default-rtdb.firebaseio.com/";
#define FIREBASE_AUTH ""; //hidden for now

//declare wifi credentials
const char* ssid = "Wokwi-GUEST"; //provided by wokwi 
const char* password = "";

const int potPin = 34; // Potentiometer pin

FirebaseData firebaseData; //instantiate firebase

void setup(){
  Serial.begin(115200); //starts serial communication
  WiFi.begin(ssid,password); //connect to wifi
  while(WiFi.status() != WL_CONNECTED){ //until wifi connected
    delay(1000); //wait 1 sec
    Serial.print("Connecting to wifi");
  }
  Serial.print("Connected to wifi"); //wifi connected
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //use credentials to login
}

void loop(){
  double sensorValue = analogRead(potPin); // read sensor value
  double powerValue = (sensorValue / 4095.0) * 500.0; //convert to power

  Serial.print("Power Usage: ");
  Serial.print(powerUsage);
  Serial.println(" W");

    // Send data to Firebase
  if (Firebase.setFloat(firebaseData, "/energy_monitor/power", powerValue)) {
      Serial.println("Data sent to Firebase");
  } else {
      Serial.println("Firebase Error: " + firebaseData.errorReason());
  }

  delay(5000);  // Send data every 5 seconds

}