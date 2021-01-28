#ifndef ToIoTwithLoRa_H
#define ToIoTwithLoRa_H

#include "Arduino.h"
#include <RH_RF95.h>
#include <AESLib.h>

class ToIoTwithLoRa
{
	public:
		ToIoTwithLoRa();
		void setupToIoTwithLoRa(char* nodeI, int CS, int RST, int INT, float FREQ);
		void pub(char* sensorId, int cnt, ...);
		void setupAES(byte* key, byte* iv);
		void aes_init();
	private:
		unsigned long lastMsg = 0;
		char topic[26];
		char msg[256];
		char* nodeId;
		
		// for LoRa
		
		RH_RF95 *rf95;
		int RFM95_RST;
		float RF95_FREQ;
		
		// for AES
		AESLib aesLib;

		byte aes_key[16] = { 0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30 };
		byte aes_iv[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		String encrypted;
		char cipher[512];

		void print_key_iv();
		void print_iv();
		String encrypt(char* msg, byte iv[]);
		String decrypt(char* msg, byte iv[]);
};
#endif
