#include "ToIoTwithLoRa.h"
#include "config.h"

double value = 0.0;
ToIoTwithLoRa t;

void setup() 
{
	t.setupToIoTwithLoRa(nodeId, rfm_cs, rfm_rst, rfm_int, rf_freq);
	t.setupAES(AES_key, AES_iv);
	t.aes_init();
}

void loop()
{
	t.pub("sensor-uuid-1", 1, value);

	delay(2000);
	value+=0.1;
}
