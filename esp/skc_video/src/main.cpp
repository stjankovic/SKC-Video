#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* apiEndpoint = "http://skc.local:3000/start";

// First network credentials
const char* ssid1 = "SKC1";
const char* password1 = "skckg1234";

// Second network credentials
const char* ssid2 = "Yettel_62D720";
const char* password2 = "SR5YcsRz";

const int buttonPin = D1; // Use the GPIO pin number where your button is connected
const int maxAttempts = 15; // Maximum attempts for the first network

void connectWiFi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to the WiFi network");
  } else {
    Serial.println("\nFailed to connect.");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);

  // Try to connect to the first network
  connectWiFi(ssid1, password1);

  // If not connected, try the second network
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi(ssid2, password2);
  }
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, apiEndpoint);
      http.addHeader("Content-Type", "application/json");

      String postData = "{\"name\": \"Stefan\"}";
      int httpCode = http.POST(postData);

      if (httpCode > 0) {
        Serial.println("Trigger Received OK");
      } else {
        Serial.println("Error in HTTP request");
      }

      http.end();
    }

    delay(500); // Debounce delay
  }
}
