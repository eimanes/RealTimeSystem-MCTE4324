#include <SPI.h>
#include <LoRa.h>
#include <HardwareSerial.h>
#include <TinyGPS++.h>

//define the pins used by the transceiver module (LORA)
#define ss 5
#define rst 14
#define dio0 2

// GPS
static const int RXPin = 16, TXPin = 17;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

int counter = 0;

void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  Serial1.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);
  
  while (!Serial);
  Serial.println("LoRa Sender");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {

  if (Serial1.available() > 0) {
    gps.encode(Serial1.read());
    if (gps.location.isUpdated()) {
  

  //Send LoRa packet to receiver
    LoRa.beginPacket();
  
    Serial.println("---------------------------------");
    Serial.print("Sending packet: ");
    Serial.println(counter);
    Serial.println("---------------------------------");
    Serial.println("----------------------- location -----------------------");
      
    // Latitude in degrees (double)
    Serial.print("Latitude = "); 
    Serial.println(gps.location.lat(), 6);      
    // Longitude in degrees (double)
    Serial.print("Longitude = "); 
    Serial.println(gps.location.lng(), 6); 
       
    // Raw latitude in whole degrees
    Serial.print("Raw latitude = "); 
    Serial.print(gps.location.rawLat().negative ? "-" : "+");
    Serial.println(gps.location.rawLat().deg); 
    // ... and billionths (u16/u32)
    Serial.println(gps.location.rawLat().billionths);
      
    // Raw longitude in whole degrees
    Serial.print("Raw longitude = "); 
    Serial.print(gps.location.rawLng().negative ? "-" : "+");
    Serial.println(gps.location.rawLng().deg); 
    // ... and billionths (u16/u32)
    Serial.println(gps.location.rawLng().billionths);
    
    LoRa.print(counter);
    LoRa.endPacket();

    counter++;

    delay(1000);
  }
  }
}
