#ifndef ToIoTwithLoRaWAN_H
#define ToIoTwithLoRaWAN_H

#include <lorawan.h>
//#include <RH_RF95.h>

class ToIoTwithLoRaWAN
{
    public:
        ToIoTwithLoRaWAN();
        void setupToIoTwithLoRaWAN(char* nodeI, const unsigned long intertimer);
        void pub(char* sensorId, int cnt, ...);
    private:
        char topic[26];
        char* nodeId;
        double arg=0;
        char msg[50];  
        char outStr[250];
        //uint8_t outStr[250];
        byte recvStatus = 0;
        
        unsigned long interval = 10000;    // 1 s interval to send message
        unsigned long previousMillis = 0;  // will store last time message sent
        unsigned int uplink_counter = 0;     // message counter
        //RH_RF95* rf95;
};

#endif