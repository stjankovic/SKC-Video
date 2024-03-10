#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* apiEndpoint = "http://skc.local:3000/start";

const char* ssid = "Yettel_62D720";
const char* password = "SR5YcsRz";


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to the WiFi network");
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client; 
        HTTPClient http;

        http.begin(client, apiEndpoint); // Updated to the new API
        int httpCode = http.GET();

        if (httpCode > 0) {
            String payload = http.getString();
            Serial.println(httpCode);
            Serial.println(payload);
        } else {
            Serial.println("Error in HTTP request");
        }

        http.end();
    }
    delay(10000); // Wait for 10 seconds between requests
}