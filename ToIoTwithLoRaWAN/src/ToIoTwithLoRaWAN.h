#ifndef ToIoTwithLoRaWAN_H
#define ToIoTwithLoRaWAN_H

#include <lorawan.h>

class ToIoTwithLoRaWAN
{
    public:
        ToIoTwithLoRaWAN();
        void setupToIoTwithLoRaWAN(char* nodeI, const unsigned long intertimer);
        void pub(char* sensorId, int cnt, ...);
    private:
        unsigned long lastMsg = 0;
        char topic[26];
        char* nodeId;
        
        char msg[50];  
        char outStr[255];
        byte recvStatus = 0;
        
        unsigned long interval = 1000;    // 1 s interval to send message
        unsigned long previousMillis = 0;  // will store last time message sent
        unsigned int counter = 0;     // message counter
};

#endif