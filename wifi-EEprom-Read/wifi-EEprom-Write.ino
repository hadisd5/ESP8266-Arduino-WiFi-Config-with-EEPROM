#include <ESP8266WiFi.h>
#include <EEPROM.h>

String ssid ;
String pass ;
String Data;
String IP_str;
IPAddress IP;

void setup() {

  Serial.begin(115200);
  EEPROM.begin(500); 
  Serial.println(" ");
  Serial.println("Ready for Commands erase,read,write");
}

void loop() {
  if (Serial.available()){
    Data = Serial.readString();
    if (Data == "write")write_EEPROM(); 
    if (Data == "read")read_EEPROM();
    if (Data == "erase")erase_EEPROM(); 
  }
}

void read_EEPROM(){
  Serial.println(" ");
  Serial.println("Now Reading From EEprom");
  Serial.print("IP-Address first place : ");
  Serial.println(EEPROM.read(0));
  Serial.print("IP-Address second place : ");
  Serial.println(EEPROM.read(1));
  Serial.print("IP-Address third place : ");
  Serial.println(EEPROM.read(2));
  Serial.print("IP-Address fourth place ");
  Serial.println(EEPROM.read(3));
  Serial.print("EEPROM Address ((4 to 39)) place : ");

  String ssidname="";
  for (int i = 0; i < 36; i++){
      ssidname += char(EEPROM.read(i+4));
  }
  Serial.println(ssidname);
  Serial.print("EEPROM Address ((40 to 79)) place : ");
  
  // Read Password
  String key="";
  for (int i = 0; i < 40;i++){
    key += char(EEPROM.read(i+40));
  }
  Serial.println(key);
}

void  write_EEPROM(){
  Serial.println(" ");
  
  // IP Address 
  Serial.println("type IP for example(192.168.0.1): ");
  while(!Serial.available()){}
  IP_str = Serial.readString();
  String_to_IP(IP_str,IP);
  
  EEPROM.put(0,IP[0]);
  EEPROM.put(1,IP[1]);
  EEPROM.put(2,IP[2]);
  EEPROM.put(3,IP[3]);
  Serial.println("IP-Address is: "+IP_str);
  
  // SSID 
  Serial.println(" ");
  Serial.println("type SSID(max 40 character): ");
  while(!Serial.available()){}
  ssid = Serial.readString();
  for (int i = 0; i<ssid.length();i++)
    {
      EEPROM.write(i+4, ssid[i]);
    }
  Serial.println("SSID is: "+ssid);
  
  // PASSWORD
  Serial.println(" ");
  Serial.println("type PASSWORD(max 40 character): ");
  while(!Serial.available()){}
  pass = Serial.readString();
  for (int i = 0; i <= pass.length();i++){
    EEPROM.write(i+40, pass[i]);
  }
  Serial.println("Password is: "+pass);;
  //
  EEPROM.commit();
  Serial.println(" ");
  Serial.println("Writing to EEPROM Finished"); 
  delay (2000);
}

void erase_EEPROM(){
  Serial.println(" ");
  Serial.println("Erase All EEPROM with 0 ");
  for (int i=0;i<4096;i++){
    EEPROM.write(i,0);
  } 
  EEPROM.commit();
  Serial.println("EEPROM Erasing Finished");
  delay(2000);
}

void String_to_IP(String str,IPAddress& IP_addr)   
{   
  int c1 = str.indexOf('.'); //first place to cut string
  int c2 = str.indexOf('.',c1+1); //second place
  int c3 = str.indexOf('.',c2+1); //Third place
  int ln = str.length();//last place to stop
  IP_addr[0] = str.substring(0,c1).toInt();
  IP_addr[1] = str.substring(c1+1,c2).toInt();
  IP_addr[2] = str.substring(c2+1,c3).toInt();
  IP_addr[3] = str.substring(c3+1,ln).toInt();
}











 

