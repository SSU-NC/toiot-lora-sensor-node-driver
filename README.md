# toiot-lora-sensor-node-driver

## Getting Started with LoRa

### Things to know before you begin.   
* It must be in compliance with the national frequency band regulations.   
* According to the LoRa Alliance document, **the unlicensed ISM band for Lora's use in Korea is specified as 920-923.**   
* The 433 MHz band used by the SX1278 LoRa chip is a limited frequency band in Korea.   
* To use LoRa **in Korea, LBT(Listen Before Talk)** should be used in Korea.   
* But in this project, we used 433 MHz for test.   
* Encrypt messages using AES-128.
   
- For Arduino:    
Connect SX1278 with arduino as shown as below.   
![Transmitting-Side-Connecting-LoRa-SX1278-with-Arduino-UNO](https://user-images.githubusercontent.com/49184890/104311794-12a0bf00-5519-11eb-8039-b8d42397c83b.png)
![LoRa_with_UNO](https://user-images.githubusercontent.com/49184890/104308980-cce1f780-5514-11eb-8256-a2de8c06e99f.PNG)   
- For NodeMCU SENDER:    
Connect SX1278 with NodeMCU as shown as below.   
![LoRa_with_NodeMCU](https://user-images.githubusercontent.com/49184890/104408324-2561d500-55a7-11eb-88b7-c84003821d7b.PNG)   

### Installing libraries
- RadioHead: http://www.airspayce.com/mikem/arduino/RadioHead/   
- Base64: https://github.com/adamvr/arduino-base64   
- AESLib: https://www.arduino.cc/reference/en/libraries/aeslib/

### Available board   
- ESP (TESTED)   
- Arduino (NOT TESTED)   
