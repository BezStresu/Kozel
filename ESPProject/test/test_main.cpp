#include <Arduino.h>
#include <unity.h>
#include <cstdlib>
#include <cstdio>


void test_message(){
    Serial.begin(11520);
    digitalWrite(23, HIGH);
    digitalWrite(22, LOW);
}


void setup(){
    UNITY_BEGIN();
    RUN_TEST(test_message);
    UNITY_END();
}

void loop(){
    int read = digitalRead(23);
    Serial.printf("Value is %d\n", read);
}
