#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Sensor 
const int pin = A0;
int readValue;

// Network ID and password
const char* ssid = "<NETWORK>";
const char* password = "<PASSWORD>";

// Server port
ESP8266WebServer server(80);

void setup(void){
  Serial.begin(9600);

  //Connection to WiFi router
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Trying to connect to WiFi router");

  int tries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++tries);
    Serial.println("...");
  }

  // Prints network ID and IP address
  Serial.print("Connected to ");
  Serial.print(ssid);
  Serial.print(" Network with IP ");
  Serial.println(WiFi.localIP());

  // Path to listen
  server.on("/", handleRoot);

  // Starts server
  server.begin();
  Serial.println("HTTP server has started");
}

void loop(void){
  server.handleClient();
}

// Humidity sensor value
void handleRoot() {
  String msgStart = "{ humidity: ";
  String msgEnd = "}";
  String msgBody = msgStart + analogRead(pin) + msgEnd;
  server.send(200, "application/json", msgBody);
}