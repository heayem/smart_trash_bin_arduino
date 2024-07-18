#include <ESP32Servo.h>

Servo myServo;

#define PIN 13
#define DISTANCE_THRESHOLD 30

class ServoController{
public:
    void setup(){
        int pos = 0;
        myServo.attach(PIN);
        myServo.write(pos);
    }
    void openLid(){
        myServo.write(40);
    }
    void closeLid(){
        myServo.write(0);
    }
};