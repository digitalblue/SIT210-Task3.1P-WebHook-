// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT_Particle.h>


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
	float f = dht.getTempFarenheit();
	
	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t) || isnan(f)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}
	
	// Compute heat index
    // Must send in temp in Fahrenheit!
	float hi = dht.getHeatIndex();
	float dp = dht.getDewPoint();
	float k = dht.getTempKelvin();
	
	Serial.print("Humid: "); 
	Serial.print(h);
	Serial.print("% - ");
	Serial.print("Temp: "); 
	Serial.print(t);
	Serial.print("*C ");
	Serial.print(f);
	Serial.print("*F ");
	Serial.print(k);
	Serial.print("*K - ");
	Serial.print("DewP: ");
	Serial.print(dp);
	Serial.print("*C - ");
	Serial.print("HeatI: ");
	Serial.print(hi);
	Serial.println("*C");
	Serial.println(Time.timeStr());
    
    digitalWrite(led, HIGH);   // Turn ON the LED

    //String temp = String(t);
    Particle.publish("temp", String::format("{\"hum\": %4.2f, \"temp\": %4.2f}", h, t), PRIVATE);
    Particle.publish("hum", String(h), PRIVATE);
    Particle.publish("readings", String::format("{\"Hum(\%)\": %4.2f, \"Temp(°C)\": %4.2f, \"DP(°C)\": %4.2f, \"HI(°C)\": %4.2f}", h, t, dp, hi));
    delay(10000);               // Wait for 10 seconds

    digitalWrite(led, LOW);    // Turn OFF the LED
    delay(20000);               // Wait for 20 seconds
}