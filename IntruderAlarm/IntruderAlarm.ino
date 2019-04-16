#include<Arduino.h>
#include<ESP8266WiFi.h>
#include<CTBot.h>

#define R 14 //D5
#define G 12 //D6
#define B 13 //D7

CTBot intruderAlarmBot;

char ssid[] = "SSID_Name"; // Enter SSID name here
char pass[] = "wifi_password"; // Enter wifi password here
char BotToken[] = "Insert bot token here"; // Bot token

int high = 0; 
int low = 0;

TBMessage msg;

void setup() {
  pinMode(0, INPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.begin(9600);
  intruderAlarmBot.wifiConnect(ssid, pass);
  intruderAlarmBot.setTelegramToken(BotToken);
}

void loop() {
  intruderAlarmBot.getNewMessage(msg);
  Serial.println(msg.text);
  if(msg.text.equalsIgnoreCase("on")) {
    Serial.print(digitalRead(0));
    Serial.print("\tHigh: ");
    Serial.print(high);
    Serial.print("\tLow: ");
    Serial.println(low);
    if (digitalRead(0) == 0) {
      low++;
      digitalWrite(R, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(B, HIGH);
    } 
    else if(digitalRead(0) == 1) {
      high++;
      digitalWrite(R, HIGH);
      digitalWrite(G, LOW);
      digitalWrite(B, LOW);
      intruderAlarmBot.sendMessage(msg.sender.id, "ALERT!!! Possible intruder detected!");
    }
    delay(1000);  
  }
  else if (msg.text.equalsIgnoreCase("off")) {
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
  }
}
