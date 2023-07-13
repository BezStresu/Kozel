#ifndef TRANSPORT
#define TRANSPORT

#include <cstdint>
class PilotingMessage;
class Transport{
    public:
        static void read_packet(float* angle, bool* gas, bool* brake, int8_t* direction, bool* track);
        static void send_packet(float ax, float ay, float az, float intensity, float distance);
        static void init();
};

#endif