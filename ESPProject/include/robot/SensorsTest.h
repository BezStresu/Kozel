#ifndef SENSORSTEST
#define SEBSORSTEST

#define PIN_ENGINE_RIGHT_SPEED 25
#define PIN_ENGINE_LEFT_SPEED 26
#define PIN_ENGINE_DIRECTION_1 22
#define PIN_ENGINE_DIRECTION_2 23
#define PIN_ACCELERATION_1 36
#define PIN_ACCELERATION_2 39
#define PIN_ACCELERATION_3 34
#define PIN_ACCELERATION_4 35
#define PIN_ACCELERATION_5 32
#define PIN_ACCELERATION_6 33
#define PIN_INTENSITY 15
#define PIN_DISTANCE_1 13
#define PIN_DISTANCE_2 4

#define VELOCITY_SCALE 1.0f;

#include <Arduino.h>


class SensorsTest{
    private:
        ///
    public:
        void distance_test();
        void acceleration_test();
        void intensity_test();
        void engine_test();


};






#endif