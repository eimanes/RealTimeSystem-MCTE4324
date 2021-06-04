
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h> 
 
// You should get Auth Token in the Blynk App.
char auth[] = "UNWiJix8XhyRRPAmvG2x837qTpE737oC";
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "hotcepuit";
char pass[] = "izzathaziq";
 
int led_1 = 32; 
int led_2 = 34; 
 
void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
 
}
 
void loop()
{
  Blynk.run();
}
