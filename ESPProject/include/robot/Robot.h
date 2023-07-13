#ifndef ROBOT
#define ROBOT



#define PIN_ENGINE_RIGHT_SPEED 25
#define PIN_ENGINE_LEFT_SPEED 26
#define PIN_ENGINE_DIRECTION_1 19
#define PIN_ENGINE_DIRECTION_2 23
#define PIN_ACCELERATION_1 36
#define PIN_ACCELERATION_2 39
#define PIN_ACCELERATION_3 34
#define PIN_ACCELERATION_4 35
#define PIN_ACCELERATION_5 32
#define PIN_ACCELERATION_6 33
#define PIN_INTENSITY 15
//#define PIN_INTENSITY_2 15
//#define PIN_INTENSITY_3 15
#define PIN_DISTANCE_1 13
#define PIN_DISTANCE_2 4

#define VELOCITY_SCALE 1.0f

#define MAX_ANGLE 65.0f

#include <Arduino.h>
#include <Wire.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

class Robot{
    private:
        
        void set_velocity(uint8_t pin, float velocity_factor);
        void set_direction(int direction);
        void set_movement(float angle, bool gas, bool brake);
    public: 
        void set_piloting_data(float angle, bool gas, bool brake, int direction, bool track);
        void init();
        void track_mode(bool track);
        void piloting_mode();

        float get_velocity_factor() const;

        float get_acceleration_x() const;
        float get_acceleration_y() const;
        float get_acceleration_z() const;
        float get_light_intensity() const;
        float get_distance() const;

};

#endif