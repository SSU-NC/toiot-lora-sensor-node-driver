/**
 * Example of OTAA device      
 * Authors: 
 *        Ivan Moreno
 *        Eduardo Contreras
 *  June 2019
 * 
 * This code is beerware; if you see me (or any other collaborator 
 * member) at the local, and you've found our code helpful, 
 * please buy us a round!
 * Distributed as-is; no warranty is given.
 */
#include "ToIoTwithLoRaWAN.h"
#include "config.h"

const sRFM_pins RFM_pins = {
  .CS = 15,
  .RST = 16,
  .DIO0 = 4,
  .DIO1 = 5,
  .DIO2 = 3,
  .DIO5 = 15,
};

ToIoTwithLoRaWAN t;
double value = 0.0; 

void setup() {
  t.setupToIoTwithLoRaWAN(nodeId, interval);

  // Set LoRaWAN Class change CLASS_A or CLASS_C
  lora.setDeviceClass(CLASS_A);

  // Set Data Rate
  lora.setDataRate(SF8BW125);

  // set channel to random
  lora.setChannel(0);
  
  // Put OTAA Key and DevAddress here
  lora.setDevEUI(devEui);
  lora.setAppEUI(appEui);
  lora.setAppKey(appKey);

  // Join procedure
  bool isJoined;
  do {
    Serial.println("Joining...");
    isJoined = lora.join();
    
    //wait for 3s to try again
    delay(3000);
  }while(!isJoined);
  Serial.println("Joined to network");
}

void loop() {
  t.pub("sensor-uuid-1", 1,value);
  value+=0.1;
  wdt_reset();
}