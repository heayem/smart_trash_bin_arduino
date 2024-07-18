#include <Arduino.h>
#include <WiFiController.h>
#include <UltrasonicController.h>
#include <FirebaseController.h>
#include <ServoController.h>

WiFiController wifiController;
UltrasonicController ultrasonicController;
ServoController servoController;
FirebaseController firebaseController;

const unsigned long lidDuration = 5000;
unsigned long openLidTime = 0;
bool lidOpen = false;

const unsigned long sendDuration = 5000;
unsigned long sendTime = 0;

void setup() {
    Serial.begin(9600);
    wifiController.setup();
    servoController.setup();
    firebaseController.setupFirebase();
}

void loop() {
    if(WiFi.status() != WL_CONNECTED){
        wifiController.setup();
    }
    int level = 0;
    int distance = 0;
    float lat = 0;
    float lng = 0;
    level = ultrasonicController.getLevel();
    distance = ultrasonicController.getDistance();
    if(!lidOpen && distance < 30){
        servoController.openLid();
        delay(3000);
        lidOpen = true;
    }
    if(lidOpen && distance > 30){
        servoController.closeLid();
        lidOpen = false;
    }
    if(millis() - sendTime >= sendDuration){
        firebaseController.sendToFirebase(level, lat, lng);
        sendTime = millis();
    }
    delay(500);
}