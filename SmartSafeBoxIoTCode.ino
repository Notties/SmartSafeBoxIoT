#include <SPI.h>
#include "MFRC522.h"
#include <TridentTD_LineNotify.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
#define LINE_TOKEN "aMuxPGS7kMVr13k5NGOtSOMiyn9clSxQYHwezqg4xqf" //LINE_TOKEN 
#define RST_PIN  D4
#define SS_PIN  D8
#define RELAY  D0 //RELAY Pin 

WidgetLCD lcd(V0); //WidgetLCD in Blynk
MFRC522 mfrc522(SS_PIN, RST_PIN);
char auth[] = "D5P0dGj3mpBo9cPHgdtZdLa1qhZ2zEbx"; //auth Blynk
char ssid[] = "Test"; //Wifiname
char pass[] = "12310834"; //Paassowrd Wifi

String rfid_in = "";
int buzzer = D2;
int cnt = 0; //cnt check count

void setup() {
  Serial.begin(9600); //start Serial 9600
  pinMode(RELAY, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW), delay(50), digitalWrite(buzzer, HIGH);
  SPI.begin();
  mfrc522.PCD_Init();
  
  Serial.println("");
  LINE.setToken(LINE_TOKEN);
  Blynk.begin(auth, ssid, pass);
  lcd.clear();
  DisplayWAiT_CARD();
  digitalWrite(RELAY, HIGH);
  
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    rfid_in=rfid_read();
    Serial.println(">>>> " + rfid_in);
    
    delay(1000);
  
  if(rfid_in=="3A 85 A1 A2"){ //found card
      digitalWrite(buzzer, LOW), delay(200), digitalWrite(buzzer, HIGH);
      digitalWrite(RELAY, LOW);
      lcd.print(0, 0, "CARD ACCESS OPEN");
      lcd.print(3, 1, rfid_in);
      LINE.notify("CARD ACCESS OPEN >> "+rfid_in);
      
      delay(2000);
      digitalWrite(RELAY, HIGH);
	  cnt = 0;
  }else if(rfid_in=="F3 F8 E3 9A"){ //found card
      digitalWrite(buzzer, LOW), delay(200), digitalWrite(buzzer, HIGH);
      digitalWrite(RELAY, LOW);
      lcd.print(0, 0, "CARD ACCESS OPEN");
      lcd.print(3, 1, rfid_in);
      LINE.notify("CARD ACCESS OPEN >> "+rfid_in);
      
      delay(2000);
      digitalWrite(RELAY, HIGH);
	  cnt = 0;
  }else{ //not found card
      for (int i = 0; i <= 2; i++)delay(100), digitalWrite(buzzer, LOW), delay(100), digitalWrite(buzzer, HIGH);
      digitalWrite(RELAY, HIGH);
      lcd.print(0, 0, " Card not Found ");
      lcd.print(0, 1, "                ");
      lcd.print(0, 1, "ID : ");
      lcd.print(5, 1, rfid_in);
      cnt++;
      
      delay(2000);
  }
  if(cnt == 3){ //when cnt count > 3
    LINE.notify("CARD NOT FOUND [3]>> "+rfid_in); //send message line notify
    cnt = 0; //reset cnt = 0
  }
  }

  Blynk.run();
  DisplayWAiT_CARD();
}

void DisplayWAiT_CARD() { //Display LCD Bylnk wait for ScanCard
  lcd.print(0, 0, "   ATTACH THE   ");
  lcd.print(0, 1, "      CARD      ");
}

BLYNK_WRITE(V1) { //Press button unlock from blynk app
  int pinValue = param.asInt();
  if (pinValue == 1)
  {
    digitalWrite(buzzer, LOW), delay(200), digitalWrite(buzzer, HIGH);
    digitalWrite(RELAY, LOW);
    lcd.clear();
    lcd.print(0, 0, "UNLOCK >> BLYNK");
    LINE.notify("Unlock From Blynk");
      
    delay(2000);
    digitalWrite(RELAY, HIGH);

    lcd.clear();
    DisplayWAiT_CARD();
  }
}

BLYNK_WRITE(V2) { //Press button lock from blynk app
  int pinValue = param.asInt();
  if (pinValue == 1)
  {
    digitalWrite(RELAY, HIGH);
    lcd.clear();
    lcd.print(0, 0, "LOCK >> BLYNK");
    LINE.notify("Lock From Blynk");
    delay(2000);

    lcd.clear();
    DisplayWAiT_CARD();
  }
}

String rfid_read() { //RFID Read
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  return content.substring(1);
}
