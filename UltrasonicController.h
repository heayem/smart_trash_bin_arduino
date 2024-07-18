#include <NewPing.h>

#define TRIG_PIN_FILL 14
#define ECHO_PIN_FILL 27
#define TRIG_PIN_DIST 25
#define ECHO_PIN_DIST 26
#define BIN_DEPTH 30 

NewPing levelSensor(TRIG_PIN_FILL, ECHO_PIN_FILL, 200);
NewPing distanceSensor(TRIG_PIN_DIST, ECHO_PIN_DIST, 200);

int level = 0;
int distance = 0;

class UltrasonicController{
public:
    int getLevel(){
        readLevelSensor();
        return level;
    }
    int getDistance(){
        readDistanceSensor();
        return distance;
    }
private:
    void readLevelSensor(){
        int newLevel = levelSensor.ping_cm();
        if(newLevel > 0) {
            level = newLevel;
        }
        if(level > 0 && level <= BIN_DEPTH){
            level = 100 - ((level * 100) / BIN_DEPTH);
        }
    }
    void readDistanceSensor(){
        int newDistance = distanceSensor.ping_cm();
        if(newDistance > 0) {
            distance = newDistance;
            Serial.print("Distance: ");
            Serial.print(distance);
            Serial.println("cm");
        }
    }
};