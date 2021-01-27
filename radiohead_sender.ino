#include <SPI.h> //Import SPI librarey 
#include <RH_RF95.h> // RF95 from RadioHead Librarey 
#include <Wire.h>

#define RFM95_CS 15 //CS if Lora connected to pin 10
#define RFM95_RST 16 //RST of Lora connected to pin 9
#define RFM95_INT 4 //INT of Lora connected to pin 2

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 434.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() 
{
 
//Initialize Serial Monitor
  Serial.begin(115200);
  
// Reset LoRa Module 
  pinMode(RFM95_RST, OUTPUT); 
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

//Initialize LoRa Module
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  

 //Set the default frequency 434.0MHz
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }

  rf95.setTxPower(18); //Transmission power of the Lora Module
}

int value = 0;

void loop()
{
  Serial.print("Send: ");
  char radiopacket[2] = {'0','0'};
  sprintf(radiopacket, "%02d", value);
  rf95.send((uint8_t *)radiopacket, 2);
  Serial.println(radiopacket);
  value++;
  if(value > 99)
    value = 0;
  delay(1000);
}
