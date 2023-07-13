#include "../../include/robot/Robot.h"

Adafruit_ADXL345_Unified accelerometr;

void Robot::set_piloting_data(float angle, bool gas, bool brake, int direction, bool track){
    set_direction(direction);
    set_movement(angle, gas, brake);

    // tracking line will be handled later
}


void Robot::track_mode(bool track){
    if(track){
        //tracking mode code
        Serial.printf("Track mode is anable\n");
        while (track)
        {
            
        }
        
    }
    else if(!track){
        //do nothing
        Serial.printf("Track mode is not anable\n");
    }
    else{
        Serial.printf("There are some problem with track mode\n");
    }
}

float Robot::get_acceleration_x() const{
    return accelerometr.getX() * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
}
float Robot::get_acceleration_y() const{
    return accelerometr.getY() * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
}
float Robot::get_acceleration_z() const{
    return accelerometr.getZ() * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
}
float Robot::get_light_intensity() const{
    return digitalRead(PIN_INTENSITY);
}
float Robot::get_distance() const{
    digitalWrite(PIN_DISTANCE_1,HIGH);
    usleep(10);
    digitalWrite(PIN_DISTANCE_1, LOW);
    float t = pulseIn(PIN_DISTANCE_2, HIGH);
    float distance = t/58;
    //Serial.printf("The distance is: %f [cm]\n", distance);
    return distance;
}

void Robot::set_movement(float angle, bool gas, bool brake){
    if(brake){
        set_velocity(PIN_ENGINE_RIGHT_SPEED, 0);
        set_velocity(PIN_ENGINE_LEFT_SPEED, 0);
        Serial.println("Setting velocity to 0");
    }
    else{
        if(gas){
            // we don't care about angle, just for test
            Serial.println("Setting velocity to max after pressing gas");
            if(angle >= 0){
                // turn right
                set_velocity(PIN_ENGINE_LEFT_SPEED, 1.0);
                set_velocity(PIN_ENGINE_RIGHT_SPEED, (MAX_ANGLE - angle)/MAX_ANGLE);
            }
            else{
                // turn left
                set_velocity(PIN_ENGINE_RIGHT_SPEED, 1.0);
                set_velocity(PIN_ENGINE_LEFT_SPEED, (MAX_ANGLE + angle)/MAX_ANGLE);
            }
        }
    }
}
void Robot::set_direction(int direction){
    if(direction == 1){
        digitalWrite(PIN_ENGINE_DIRECTION_1, HIGH);
        digitalWrite(PIN_ENGINE_DIRECTION_2, LOW);
    }
    else if(direction == -1){
        digitalWrite(PIN_ENGINE_DIRECTION_1, LOW);
        digitalWrite(PIN_ENGINE_DIRECTION_2, HIGH);
    }
    else{
        Serial.printf("Unknown direction: %d\n", direction);
    }
}
void Robot::set_velocity(uint8_t pin, float velocity_factor){
    float value = velocity_factor * 255.0f;
    float scaled_value = value * VELOCITY_SCALE;
    analogWrite(pin, (int)scaled_value);
}


void Robot::init(){
    pinMode(PIN_ENGINE_DIRECTION_1, OUTPUT);
    pinMode(PIN_ENGINE_DIRECTION_2, OUTPUT);
    pinMode(PIN_ENGINE_LEFT_SPEED, OUTPUT);
    pinMode(PIN_ENGINE_RIGHT_SPEED, OUTPUT);
    pinMode(PIN_DISTANCE_1, OUTPUT);
    pinMode(PIN_DISTANCE_2, INPUT);
    pinMode(PIN_INTENSITY, INPUT);
}