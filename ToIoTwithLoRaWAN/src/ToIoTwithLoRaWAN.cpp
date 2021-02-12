#include "ToIoTwithLoRaWAN.h"

ToIoTwithLoRaWAN::ToIoTwithLoRaWAN()
{
}

void ToIoTwithLoRaWAN::setupToIoTwithLoRaWAN(char* nodeI, const unsigned long intertimer)
{
    Serial.begin(115200);
    if(!lora.init()){
        Serial.println("RFM95 not detected");
        delay(5000);
        return;
    }
    nodeId = nodeI;
    interval = intertimer;
    snprintf(topic, 26, "data/%s", nodeId);
}

void ToIoTwithLoRaWAN::pub(char* sensorId, int cnt, ...)
{
    // todo: connection check
    
    if(millis() - previousMillis > interval) {
        va_list ap;
        va_start(ap, cnt);
        //uint8_t res = 0;
        memset(msg, 0, 50);
        //res = sprintf(msg, "%s:%s,", topic, sensorId);
        sprintf(msg, "%s:%s,",topic,sensorId);

        for(int i=0; i<cnt; i++)
        {
            arg = va_arg(ap, double);
            if(i == cnt-1)
            {
                //res += vsprintf(msg+res, "%lf", ap);
                sprintf(msg, "%s%lf",msg,arg);
            }
            else
            {
                //res += vsprintf(msg+res, "%lf,", ap);
                sprintf(msg, "%s%lf,",msg,arg);
            }
        }
        va_end(ap);

        previousMillis = millis(); 
        lora.sendUplink(msg, strlen(msg), 0, 1);
        Serial.print("[Pub] ");
        Serial.println(msg);
        uplink_counter++;
    }
    
    lora.update();

    recvStatus = lora.readData(outStr);
    if(recvStatus) {
        Serial.print("[Recv] ");
        Serial.println(outStr);
    }
    
}