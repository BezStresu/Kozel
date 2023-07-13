#include "../../include/robot/SensorsTest.h"
#include <unistd.h>
void SensorsTest::distance_test(){
    pinMode(PIN_DISTANCE_1, OUTPUT);
    pinMode(PIN_DISTANCE_2, INPUT);
    pinMode(PIN_INTENSITY, INPUT);

    //while(true)
    //{
        
        digitalWrite(PIN_DISTANCE_1,HIGH);
        usleep(10);
        digitalWrite(PIN_DISTANCE_1, LOW);
        float t = pulseIn(PIN_DISTANCE_2, HIGH);
        float distance = t/58; //output in cm
        Serial.printf("The distance is: %f [cm]\n", distance);
        int intensity = digitalRead(PIN_INTENSITY);
        Serial.printf("The intensity is %d\n", intensity);
        delay(500);
    //}
    
}

void SensorsTest::acceleration_test(){
    
}




