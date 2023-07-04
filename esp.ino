#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h> // Dodaj bibliotekę ArduinoJson

const char* ssid = "FunBox2-F161";
const char* password = "334C6A746F93C9C4D7A1569D96";
const char* serverUrl = "https://paczkomat.pythonanywhere.com/paczkomaty";


const int ledPin2 = 2;
const int ledPin3 = 3;

WiFiClientSecure client;
HTTPClient http;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setInsecure();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (http.begin(client, serverUrl)) {
      int httpCode = http.GET();
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);

        // Parsowanie JSON
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
          Serial.print("JSON parsing error: ");
          Serial.println(error.c_str());
        } else {
          bool otworz = doc[0]["otworz"]; // Pobierz wartość zmiennej "otworz"

          // Przykładowa logika sterowania diodami
          if (otworz) {
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, HIGH);
            Serial.println("LED3 turned ON");
          } else {
            digitalWrite(ledPin2, HIGH);
            digitalWrite(ledPin3, LOW);
            Serial.println("LED2 turned ON");
          }
        }
      } else {
        Serial.print("Error accessing server. Error code: ");
        Serial.println(httpCode);
      }

      http.end();
    } else {
      Serial.println("Unable to connect to server");
    }
  }
  
  delay(1000);  // Poczekaj 5 sekund przed kolejnym sprawdzeniem
}
