#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>


// SPI CONFIG
#define LORA_SCK 5        // GPIO5 - SX1276 SCK
#define LORA_MISO 19     // GPIO19 - SX1276 MISO
#define LORA_MOSI 27    // GPIO27 -  SX1276 MOSI
#define LORA_CS 18     // GPIO18 -   SX1276 CS
#define LORA_RST 14   // GPIO14 -    SX1276 RST
#define LORA_IRQ 26  // GPIO26 -     SX1276 IRQ (interrupt request)

void setup() {

  Serial.begin(115200);
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  pinMode(LED_BUILTIN, OUTPUT);

  if(!LoRa.begin(433E6)){
    Serial.println("LoRa comunication failed");
    while(1);
  }
}

String arriveMessagePhone;

void sendMessage(String outgoing){
  LoRa.beginPacket();
  LoRa.print(outgoing);
  LoRa.endPacket();
}

void onReceive(int packetSize){
  if (packetSize == 0)return;
  String incomming = "";
  while (LoRa.available()){
    incomming += (char)LoRa.read();
  }

  Serial.println(incomming);
}

void loop() {
 if(Serial.available() > 0){
   arriveMessagePhone = Serial.readString();
   sendMessage(arriveMessagePhone);
 }

 onReceive(LoRa.parsePacket());
}
