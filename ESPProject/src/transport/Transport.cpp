#include "../../include/transport/Transport.h"
#include <BluetoothSerial.h>




BluetoothSerial bluetooth_serial;


void Transport::init(){
    bluetooth_serial.setPin("6969");
    bluetooth_serial.begin("BT-HC-06");
}

const int32_t MAGIC_NUMBER = 0xCDB4287F;


void Transport::send_packet(float ax, float ay, float az, float intensity, float distance){
    int size = 24;
    uint8_t packet[size];
    *(int32_t*)packet = MAGIC_NUMBER;
    *(float*)&packet[4] = ax;
    *(float*)&packet[8] = ay;
    *(float*)&packet[12] = az;
    *(float*)&packet[16] = intensity;
    *(float*)&packet[20] = distance;
    for(int i = 0; i < size; i++){
        Serial.printf("Sending byte %d\n", packet[i]);
        bluetooth_serial.write(packet[i]);
    }
}

void Transport::read_packet(float* angle, bool* gas, bool* brake, int8_t* direction, bool* track){
    int index = 0;
    uint8_t* magic_ptr = (uint8_t*)&MAGIC_NUMBER;
    while(true){
        int16_t read = bluetooth_serial.read();
        if(read != -1){
            if(magic_ptr[index] == (uint8_t)read){
                index++;
                Serial.printf("Reading magic byte %d\n", read);
                if(index == 4){
                    break;
                }
            }
            else{
                index = 0;
            }
        }
    }
    int size = 8;
    uint8_t packet[size];
    index = 0;
    while(true){
        int16_t read = bluetooth_serial.read();
        if(read != -1){
            packet[index] = (uint8_t)read;
            Serial.printf("Reading packet byte %d for index %d\n", read, index);
            index++;
            if(index == size){
                break;
            }
        }
    }
    *angle = *(float*)packet;
    *gas = *(bool*)&packet[4];
    *brake = *(bool*)&packet[5];
    *direction = *(int8_t*)&packet[6];
    *track = *(bool*)&packet[7];
}