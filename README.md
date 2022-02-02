# SmartSafeBoxIoT
NodeMCU V3 ESP8266, RFID, Solenoid lock, Passive Buzzer

# The Lock System
### - Scan cards
Unlocked by authorized cards only. If the card is scanned incorrectly more than 3 times, a notification will be sent to LINE.

### - Unlock the bolt through the application.
Unlock by blynk application and send notification to LINE Application

# All pin
### - MFRC-522 RFID Module RC522:
   SDA   ---->  D8
   SCK   ---->  D5
   MOSI ---->  D7
   MISO ---->  D6
   Gnd   ---->  Gnd
   RST   ---->  D4
   3.3V  ---->  3.3V
   

### - Passive Buzzer Module:
   VCC   ---->  3.3V
   I/O  ---->  D2
   Gnd   ---->  Gnd


### - Relay 5V:
   VCC   ---->  3.3V
   Gnd   ---->  Gnd
   IN ----> D0
   Normally Open ----> + Battery 9V
   Common ----> + Solenoid lock
##

![Circuit Diagram](https://github.com/Notties/SmartSafeBoxIoT/blob/main/Circuit%20Diagram.png?raw=true)
