#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>
#define FIREBASE_HOST "https://finalprojectar-28391.firebaseio.com/"///////// Addres Realtime Database
#define FIREBASE_AUTH "lEcynnm4wrMbl0VbTCpmI2vGuJAKL5Lo2bRvL5Ik"////////// 
WiFiClient client;           // initialize the library instance:
//#define WIFI_SSID "asekalebor"
//#define WIFI_PASSWORD "mugiwaraboy"
#define WIFI_SSID "Infinix"
#define WIFI_PASSWORD "wanipiro"
FirebaseData firebaseData;
#define E 0
#define LL 1
#define L 2
#define H 3
#define HH 4
#define PIN_INTERNET D7
int MikroPLC_addres[12];
void defaultDataMikroPLC(){
  MikroPLC_addres[0] = 0;
  MikroPLC_addres[1] = 0;
  MikroPLC_addres[2] = 0;
  MikroPLC_addres[3] = 0;
  MikroPLC_addres[4] = 0;
  MikroPLC_addres[5] = 0;
  MikroPLC_addres[6] = 0;
  MikroPLC_addres[7] = 0;
  MikroPLC_addres[8] = 0;
  MikroPLC_addres[9] = 0;
  MikroPLC_addres[10] = 0;
  MikroPLC_addres[11] = 0;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_INTERNET,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.setAutoReconnect(true);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    
    Serial.print(".");
    delay(300);
  }
  
  if (!ModbusRTUServer.begin(1, 9600)) {
    Serial.println("Failed to start Modbus RTU Server!");
    while (1);
  }
//  ModbusRTUServer.configureHoldingRegisters(0x00, 12);
  ModbusRTUServer.configureCoils(0x00, 12);
  defaultDataMikroPLC();
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}
int i = 1;

void loop() {
  // put your main code here, to run repeatedly:
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  ModbusRTUServer.poll();
//  MikroPLC_addres[0] = ModbusRTUServer.holdingRegisterRead(0x00);
//  MikroPLC_addres[1] = ModbusRTUServer.holdingRegisterRead(0x01);
//  MikroPLC_addres[2] = ModbusRTUServer.holdingRegisterRead(0x02);
//  MikroPLC_addres[3] = ModbusRTUServer.holdingRegisterRead(0x03);
  MikroPLC_addres[4] = ModbusRTUServer.coilRead(0x00);
  MikroPLC_addres[5] = ModbusRTUServer.coilRead(0x01);
  MikroPLC_addres[6] = ModbusRTUServer.coilRead(0x02);
  MikroPLC_addres[7] = ModbusRTUServer.coilRead(0x03);
  MikroPLC_addres[8] = ModbusRTUServer.coilRead(0x04); // internet
  MikroPLC_addres[9] = ModbusRTUServer.coilRead(0x05); // pump
//  Serial.print(MikroPLC_addres[0]);
//  Serial.print(MikroPLC_addres[1]);
//  Serial.print(MikroPLC_addres[2]);
//  Serial.print(MikroPLC_addres[3]);
  Serial.print("::");
  Serial.print(MikroPLC_addres[4]);
  Serial.print(MikroPLC_addres[5]);
  Serial.print(MikroPLC_addres[6]);
  Serial.print(MikroPLC_addres[7]);
  Serial.print(MikroPLC_addres[9]);
  Serial.print("::");
  Serial.println();
  float LEVEL_SEND;
  if(MikroPLC_addres[4] == 1){
    LEVEL_SEND = LL;
//    Serial.println("LL");
  }
  if(MikroPLC_addres[4] == 1 && MikroPLC_addres[5] == 1 ){
    LEVEL_SEND = L;
//    Serial.println("L");
  }
  if(MikroPLC_addres[4] == 1 && MikroPLC_addres[5] == 1 && MikroPLC_addres[6] == 1 ){
    LEVEL_SEND = H;
//    Serial.println("H");
  }
  if(MikroPLC_addres[4] == 1 && MikroPLC_addres[5] == 1 && MikroPLC_addres[6] == 1 && MikroPLC_addres[7] == 1 ){
    LEVEL_SEND = HH;
//    Serial.println("HH");
  }
//  else{
//    /// ditambahkan safety sensor rusak
//    LEVEL_SEND = E;
//    Serial.println("E");
//  }
  //ModbusRTUServer.coilWrite(0x05,1);
  
  kirimFirebaseFloat("Sensor/Level",LEVEL_SEND);
  if(MikroPLC_addres[9]){
    kirimFirebaseString("Output/Pump","ON");
  }
  else{
    kirimFirebaseString("Output/Pump","OFF");
  }
 //+
  cek_Output(i);
  i++;
  if(i>3)i=1;
  uint16_t dt_bit;
  if(WiFi.status() == WL_CONNECTED){
    dt_bit = 0x01;
    Serial.println("Internet Connected");
    digitalWrite(PIN_INTERNET,HIGH);
      
  }
  else if (WiFi.status() != WL_CONNECTED) {
    dt_bit = 0;
    Serial.println("Internet Not Connected");
    digitalWrite(PIN_INTERNET,LOW);
//    if(ModbusRTUServer.coilWrite(0x04,dt_bit)){
//      Serial.println("Sended");
//    }
//    else{
//      Serial.println(" Not Sended");
//    }
  }
  //delay(100);
  
}
