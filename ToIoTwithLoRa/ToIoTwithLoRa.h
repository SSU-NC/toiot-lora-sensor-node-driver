#ifndef ToIoTwithLoRa_H
#define ToIoTwithLoRa_H

#include "Arduino.h"
#include <RH_RF95.h>

class ToIoTwithLoRa
{
	public:
		ToIoTwithLoRa();
		void setupToIoTwithLoRa(char* nodeI, int CS, int RST, int INT, float FREQ);
		void pub(char* sensorId, int cnt, ...);
	private:
		unsigned long lastMsg = 0;
		char topic[26];
		char msg[50];
		char* nodeId;
		RH_RF95 *rf95;
		int RFM95_RST;
		float RF95_FREQ;

};
#endif
