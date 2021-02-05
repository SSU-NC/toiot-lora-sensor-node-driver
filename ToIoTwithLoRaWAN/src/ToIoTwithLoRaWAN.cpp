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
    va_list ap;
    va_start(ap, cnt);
    int res = 0;
    memset(msg, 0, 50);
    res = sprintf(msg, "%s:%s,", topic, sensorId);

    for(int i=0; i<cnt; i++)
    {
        if(i == cnt-1)
        {
            res += vsprintf(msg+res, "%lf", ap);
        }
        else
        {
            res += vsprintf(msg+res, "%lf,", ap);
        }
        va_arg(ap, double);
    }
    va_end(ap);
    if(millis() - previousMillis > interval) {
        previousMillis = millis(); 
        Serial.print("[Pub] ");
        Serial.println(msg);
        
        lora.sendUplink(msg, strlen(msg), 0, 1);
        counter++;
    }
    recvStatus = lora.readData(outStr);
    if(recvStatus) {
        Serial.println(outStr);
    }
    // Check Lora RX
    lora.update();
}