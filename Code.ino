#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Your WiFi SSID";
const char* password = "Your WiFi password";
const char* serverName = "http://your-website.com/Data.php"; 

const int tempPin = A0; 
const int soilPin = A1; 
const int phPin = A2; 

void setup() {
  Serial.begin(115200);
  delay(1000);

  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

 
  pinMode(tempPin, INPUT);
  pinMode(soilPin, INPUT);
  pinMode(phPin, INPUT);
}

void loop() {

  float temp = analogRead(tempPin) * 0.48828125; 
  int soilMoisture = analogRead(soilPin); 
  int pH = analogRead(phPin); 
 
  String postData = "temp=" + String(temp) + "&soil=" + String(soilMoisture) + "&ph=" + String(pH);
  HTTPClient http;
  http.begin(serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(postData);
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    Serial.println("Server response: " + response);
  }
  else {
    Serial.println("Error in HTTP request");
  }
  http.end();

  delay(300000); 
}