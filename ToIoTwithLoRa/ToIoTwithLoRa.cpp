#include "ToIoTwithLoRa.h"
#include <cstring>
#include <stdarg.h>
#include "Arduino.h"
#include <RH_RF95.h>

ToIoTwithLoRa::ToIoTwithLoRa()
{
}

void ToIoTwithLoRa::setupToIoTwithLoRa(char* nodeI, int CS, int RST, int INT, float FREQ)
{	
	RFM95_RST = RST;
	RF95_FREQ = FREQ;
	rf95 = new RH_RF95(CS, INT);

	Serial.begin(115200);

	pinMode(RFM95_RST, OUTPUT);
	digitalWrite(RFM95_RST, LOW);
	delay(10);
	digitalWrite(RFM95_RST, HIGH);
	delay(10);

	while (!rf95->init()) {
		Serial.println("LoRa radio init failed");
		while(1);
	}

	if(!rf95->setFrequency(RF95_FREQ)) {
		Serial.println("setFrequency failed");
		while(1);
	}

	rf95->setTxPower(18);
}

void ToIoTwithLoRa::pub(char* sensorId, int cnt, ...)
{
    // if not connected
    //    reconnect();
    va_list ap;
    va_start(ap, cnt);
    int res = 0;
    memset(msg, 0, 50);
    res = sprintf(msg, "%s,", sensorId);
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
    Serial.print("[Pub] ");
    Serial.print(topic);
    Serial.print(":");
    Serial.println(msg);
    rf95->send((uint8_t *)msg, 50);
}

