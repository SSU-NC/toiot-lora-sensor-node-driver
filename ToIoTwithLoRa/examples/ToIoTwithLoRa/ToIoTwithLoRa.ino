#include "ToIoTwithLoRa.h"
#include "config.h"

double value = 0.0;
ToIoTwithLoRa t;

void setup() 
{
	t.setupToIoTwithLoRa(nodeId, rfm_cs, rfm_rst, rfm_int, rfm_freq);
}

void loop()
{
	t.pub("sensor-uuid-1", 1, value);

	delay(2000);
	value+=0.1;
}
