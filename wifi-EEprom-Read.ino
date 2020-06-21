#include <ESP8266WiFi.h>
#include <EEPROM.h>

String ssid;
String pass;

IPAddress IP;
IPAddress gateway(192,168,0,2);
IPAddress subnetmask(255,255,255,0);
IPAddress dns1(1,1,1,1);

void setup() {

  Serial.begin(115200);
  EEPROM.begin(4096); 
  IP = IPAddress(EEPROM.read(0),EEPROM.read(1),EEPROM.read(2),EEPROM.read(3)); // IP
  
  for (int i = 0; i < 36; i++){
    ssid += char(EEPROM.read(i+4)); // SSID
  }
  
  for (int i = 0; i < 40; i++){
    pass += char(EEPROM.read(i+40)); // Password
  }
  WiFi.begin(ssid.c_str(),pass.c_str());
  WiFi.config(IP,gateway,subnetmask,dns1);
  while(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Right. connected with these Parameters :");
  Serial.print("ESP IP Address:");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet mask:");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway:");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS:");
  Serial.println(WiFi.dnsIP());
  Serial.print("Host Name:");
  Serial.println(WiFi.hostname());
}

void loop() {

}










