#include "Adafruit_DHT_Particle.h"

#define DHTPIN D6   // what pin we're connected to
#define DHTTYPE DHT22		// DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);
int led = D7;  // The on-board LED

void setup() {
    pinMode(led, OUTPUT);
  
    Serial.begin(9600); 
    Serial.println("DHTxx test!");
    Particle.publish("state", "DHTxx test start");

    dht.begin();
    delay(2000);
}

void loop() {
    // Read temp and humidity 
    float h = dht.getHumidity();
    float t = dht.getTempCelcius();
	
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
	    Serial.println("Failed to read from DHT sensor!");
	    return;
    }
    
    digitalWrite(led, HIGH); // Turn ON the LED
    Particle.publish("temp", String::format("{\"hum\": %4.2f, \"temp\": %4.2f}", h, t), PRIVATE);
    delay(10000); // Wait for 10 seconds

    digitalWrite(led, LOW); // Turn OFF the LED
    delay(20000); // Wait for 20 seconds
}