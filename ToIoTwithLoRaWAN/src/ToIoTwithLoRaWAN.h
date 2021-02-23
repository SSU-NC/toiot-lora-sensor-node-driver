#ifndef ToIoTwithLoRaWAN_H
#define ToIoTwithLoRaWAN_H

#include <lorawan.h>

class ToIoTwithLoRaWAN
{
    public:
        ToIoTwithLoRaWAN();
        void setupToIoTwithLoRaWAN(char* nodeI, const unsigned long intertimer, unsigned int QOS);
        void pub(char* sensorId, int cnt, ...);
    private:
        char topic[26];
        char* nodeId;
        double arg=0;
        char msg[50];
        char last_msg[50];
        char outStr[50];
        byte recvStatus = 0;
        
        unsigned long interval = 10000;    // 10 s interval to send message
        unsigned long previousMillis = 0;  // will store last time message sent
        unsigned int uplink_counter = 0;     // message counter

        unsigned int QOS;
        bool sender_lock;

        int actuator();
        // actuator sleep
        int Actuator_list[5] = {NULL, NULL, NULL, NULL, NULL};
        unsigned long Actuator_previousMillis[5];
        unsigned long Actuator_interval[5];
};

#endif