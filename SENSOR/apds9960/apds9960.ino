#include <Wire.h>
#include <SparkFun_APDS9960.h>

// https://how2electronics.com/interfacing-apds9960-gesture-rgb-color-sensor-with-arduino/

#define APDS9960_INT  2

SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;

void setup() {
    Serial.begin(9600);
    Serial.println();
    Serial.println(F("--------------------------------"));
    Serial.println(F("APDS-9960 - GestureTest"));
    Serial.println(F("--------------------------------"));

    attachInterrupt(0, interruptRoutine, FALLING);

    if ( apds.init() ) {
        Serial.println(F("APDS-9960 initialization complete"));
    }
    else {
        Serial.println(F("Something went wrong during APDS-9960 init!"));
    }

     if ( apds.enableGestureSensor(true) ) {
        Serial.println(F("Gesture sensor is now running"));
     }
     else {
        Serial.println(F("Something went wrong during gesture sensor init!"));
     }
}

void loop() {
    if ( isr_flag == 1 ) {
        detachInterrupt(0);
        handleGesture();
        isr_flag = 0;
        attachInterrupt(0, interruptRoutine, FALLING);
    }
}

void interruptRoutine() {
    isr_flag = 1;
}

void handleGesture() {
    if (apds.isGestureAvailable()) {
        switch(apds.readGesture()) {
            case DIR_UP:
            Serial.println("UP");
            break;
            case DIR_DOWN:
            Serial.println("DOWN");
            break;
            case DIR_LEFT:
            Serial.println("LEFT");
            break;
            case DIR_RIGHT:
            Serial.println("RIGHT");
            break;
            case DIR_NEAR:
            Serial.println("NEAR");
            break;
            case DIR_FAR:
            Serial.println("FAR");
            break;
            default:
            Serial.println("NONE");
        }
    }
}