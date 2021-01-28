#include "ToIoTwithLoRa.h"
#include <cstring>
#include <stdarg.h>
#include "Arduino.h"
#include <RH_RF95.h>
#include <AESLib.h>

#define BAUDRATE 115200

ToIoTwithLoRa::ToIoTwithLoRa()
{
}

void ToIoTwithLoRa::setupToIoTwithLoRa(char* nodeI, int CS, int RST, int INT, float FREQ)
{	
	RFM95_RST = RST;
	RF95_FREQ = FREQ;
	rf95 = new RH_RF95(CS, INT);

	Serial.begin(BAUDRATE);

	pinMode(RFM95_RST, OUTPUT);
	digitalWrite(RFM95_RST, LOW);
	delay(10);
	digitalWrite(RFM95_RST, HIGH);
	delay(10);

	while(!rf95->init()) {
		Serial.println("LoRa radio init failed");
		while(1);
	}

	if(!rf95->setFrequency(RF95_FREQ)) {
		Serial.println("setFrequency failed");
		while(1);
	}

	rf95->setTxPower(18);
}

void ToIoTwithLoRa::setupAES(byte* key, byte* iv)
{
	memcpy(aes_key, key, sizeof(key));
	memcpy(aes_iv, iv, sizeof(iv));
	aes_init();
}

void ToIoTwithLoRa::aes_init()
{
	aesLib.gen_iv(aes_iv);
	aesLib.set_paddingmode((paddingMode)0);
}

void ToIoTwithLoRa::print_iv() {
	byte null_iv[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	char iv[256];
	int ivlen = base64_encode(iv, (char*)null_iv, 16);
	Serial.println(iv);
}


String ToIoTwithLoRa::encrypt(char * msg, byte iv[]) {
	unsigned long ms = micros();
	int msgLen = strlen(msg);
	char encrypted[2 * msgLen];
	aesLib.encrypt64(msg, msgLen, encrypted, aes_key, sizeof(aes_key), iv);
	Serial.print("Encryption took: ");
	Serial.print(micros() - ms);
	Serial.println("us");
	return String(encrypted);
}

String ToIoTwithLoRa::decrypt(char * msg, byte iv[]) {
	unsigned long ms = micros();
	int msgLen = strlen(msg);
	char decrypted[msgLen]; // half may be enough
	aesLib.decrypt64(msg, msgLen, decrypted, aes_key, sizeof(aes_key), iv);
	Serial.print("Decryption [2] took: ");
	Serial.print(micros() - ms);
	Serial.println("us");
	return String(decrypted);
}


void ToIoTwithLoRa::print_key_iv()
{
	int i;
	Serial.println("AES IV: ");
	for(i=0; i<sizeof(aes_iv); i++) {
		Serial.print(aes_iv[i], DEC);
		if((i+1)<sizeof(aes_iv)) {
			Serial.print(",");
		}
	}

	Serial.println("");
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
    
    print_key_iv();
    print_iv();

    byte enc_iv[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    encrypted = encrypt(msg, enc_iv);
    
    sprintf(cipher, "%s", encrypted.c_str());
    Serial.print("[Encrypted]:");
    Serial.println(encrypted);

    rf95->send((uint8_t*)cipher, sizeof((uint8_t*)cipher));
}
