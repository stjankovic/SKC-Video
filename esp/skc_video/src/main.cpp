#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* apiEndpoint = "http://skc.local:3000/start";
const char* ssid = "Yettel_62D720";
const char* password = "SR5YcsRz";

// Button pin setup
const int buttonPin = D1; // Use the GPIO pin number where your button is connected

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(buttonPin, INPUT_PULLUP); // Initialize the button pin as input with internal pull-up resistor

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to the WiFi network");
}

void loop() {
  int buttonState = digitalRead(buttonPin); // Read the state of the button
  
  if (buttonState == LOW) { // Check if the button is pressed
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client; 
      HTTPClient http;

      http.begin(client, apiEndpoint); // Specify the URL

      // Set appropriate headers, if required by the API
      http.addHeader("Content-Type", "application/json");

      // Prepare your data as a JSON string or in the format required by your API
      String postData = "{\"name\": \"Stefan\"}";

      // Send a POST request with your data
      int httpCode = http.POST(postData);

      // Check the returning http response code
      if (httpCode > 0) {
        Serial.println("Trigger Received OK");
      } else {
        Serial.println("Error in HTTP request");
      }

      http.end(); //Close connection
    }

    // Debounce delay to avoid multiple triggers from a single press
    delay(500); // Adjust this value if needed
  }
}
