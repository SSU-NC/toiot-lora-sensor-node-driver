# toiot-lora-sensor-node-driver

## Things to know before you begin.   
* It must be in compliance with the national frequency band regulations.   
* According to the LoRa Alliance document, **the unlicensed ISM band for Lora's use in Korea is specified as 920-923.**(Check this PDF.)     
https://lora-alliance.org/wp-content/uploads/2019/11/rp_2-1.0.0_final_release.pdf
* The 433 MHz band used by the SX1278 LoRa chip is a limited frequency band in Korea.   
* To use LoRa **in Korea, LBT(Listen Before Talk)** should be used in Korea.  
* But in this project, we used 433 MHz for test.   
* Encrypt messages using AES-128.

## Getting Started with LoRa
1. Use the Arduino Library Manager to install the `RadioHead`, `AESLib` library.
2. Download `ToIoTwithLoRa` and put it in the Arduino/libraries folder.
3. Fill in the contents of `config.h` and put it in the sketch folder. You can set this application through this file.
4. Write the main source code like [example](https://github.com/gjlee0802/toiot-lora-sensor-node-driver/blob/main/ToIoTwithLoRa/examples/ToIoTwithLoRa/ToIoTwithLoRa.ino).
   
### Connection
- For Arduino:    
Connect SX1278 with arduino as shown as below.   
![Transmitting-Side-Connecting-LoRa-SX1278-with-Arduino-UNO](https://user-images.githubusercontent.com/49184890/104311794-12a0bf00-5519-11eb-8039-b8d42397c83b.png)
![LoRa_with_UNO](https://user-images.githubusercontent.com/49184890/104308980-cce1f780-5514-11eb-8256-a2de8c06e99f.PNG)   
- For NodeMCU SENDER:    
Connect SX1278 with NodeMCU as shown as below.   
![LoRa_with_NodeMCU](https://user-images.githubusercontent.com/49184890/104408324-2561d500-55a7-11eb-88b7-c84003821d7b.PNG)   

### Installing libraries
- RadioHead: http://www.airspayce.com/mikem/arduino/RadioHead/   
- AESLib: https://www.arduino.cc/reference/en/libraries/aeslib/
- Base64: https://github.com/adamvr/arduino-base64   

### Available board   
- ESP (TESTED)   
- Arduino (NOT TESTED)   


## LoRa Packet Information

### RF95 Packet format
**All messages sent and received by this RH_RF95 Driver conform to this packet format:**
- LoRa mode:   
- 8 symbol PREAMBLE   
- Explicit header with header CRC (default CCITT, handled internally by the radio)   
- 4 octets HEADER: (TO, FROM, ID, FLAGS)   
- 0 to 251 octets DATA   
- CRC (default CCITT, handled internally by the radio)   
