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

    http.begin(client, apiEndpoint); // Specify the URL

    // Set appropriate headers, if required by the API (e.g., for content type or authentication)
    http.addHeader("Content-Type", "application/json");

    // Prepare your data as a JSON string or in the format required by your API
    String postData = "{\"name\": \"Stefan\"}";

    // Send a POST request with your data
    int httpCode = http.POST(postData);

    // Check the returning http response code
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
    } else {
      Serial.println("Error in HTTP request");
    }

    http.end(); //Close connection
  }
  delay(10000); // Wait for 10 seconds between requests
}
