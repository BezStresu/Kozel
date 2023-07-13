
#include "../include/transport/Transport.h"
#include "../include/robot/Robot.h"
#include "../include/robot/SensorsTest.h"
#include <BluetoothSerial.h>
Robot robot;
SensorsTest test;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif




void collect_data(){
  Serial.println("Waiting for packet ...");
  float angle;
  bool gas, brake, track;
  int8_t direction;

  Transport::read_packet(&angle, &gas, &brake, &direction, &track);

  Serial.println("Received some important data, processing ...");
 // Serial.println("Created piloting message instance");
  // change piloting on robot
  Serial.printf("Receiving piloting message: [angle= %f brake = %s, gas = %s, direction = %d, track = %s]\n",
    angle, brake ? "true" : "false",
    gas ? "true" : "false", direction, track ? "true" : "false");
  
  robot.set_piloting_data(angle, gas, brake, direction, track);
}

void watch_and_send_data(){
  Transport::send_packet(robot.get_acceleration_x(), robot.get_acceleration_y(), robot.get_acceleration_z(),
     robot.get_light_intensity(), robot.get_distance());
}

void setup() {
  Serial.begin(115200);

  Transport::init();
  robot.init();
  pinMode(LED_BUILTIN, OUTPUT); 
}
void loop() {
  collect_data();
  watch_and_send_data();
  delay(1000);

}