#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <TimeLib.h> 
#include <time.h>

const char *ssid = "ESP8266-AP";
const char *password = "123456789";
const char *serverIP = "192.168.4.1";

int seconds = 0;
int digitalPin = 4;
bool isReadden = false;
int count = 0;
int newCount = 0;

String outputData = "";

WiFiClient client;

void detectMetal(int detected) {
  if (detected == LOW && isReadden == false) {
    count++;
    isReadden = true;
  }
  if (detected == HIGH) isReadden = false;
}

void displayClock() {

  int currentHour = hour();
  int currentMinute = minute();
  int currentSecond = second();
  outputData = "";
  outputData += String(currentHour);
  outputData += ":";
  outputData += String(currentMinute);
  outputData += ":";
  outputData += String(currentSecond);
  outputData += ". Index: "; 
}

void sendDataToServer(String data) {
  HTTPClient http;
  String url = "http://" + String(serverIP) + "/clients";
  http.begin(client, url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String postData = "data=" + data;
  int httpCode = http.POST(postData);
  // if (httpCode != HTTP_CODE_OK) {
  //   Serial.print("Error sending data. HTTP code: ");
  //   Serial.println("httpCode");
  // }
  http.end();
}

void setup() {
  setTime(12, 30, 0, 12, 10, 2023);
  Serial.begin(115200);
  pinMode(digitalPin, INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");
  // String receivedCommand = getCommandFromServer();
  // Serial.print("Received command: ");
  // Serial.println(receivedCommand);
}

void loop() {
  displayClock();
  int sensorValue = digitalRead(digitalPin);
  detectMetal(sensorValue);
  if (newCount != count && seconds >= 400000) {
    newCount = count;
    seconds = 0;
    outputData += String(newCount);
    Serial.println(outputData);
    sendDataToServer(outputData);
  } else {
    seconds++;
  }
}

// String getCommandFromServer() {
//   HTTPClient http;
//   String url = "http://" + String(serverIP) + "/clients";
//   http.begin(client, url);
//   int httpCode = http.GET();
//   String receivedCommand = "";
//   if (httpCode == HTTP_CODE_OK) {
//     receivedCommand = http.getString();
//   } else {
//     Serial.print("Error requesting command. HTTP code: ");
//     Serial.println(httpCode);
//   }
//   http.end();
//   return receivedCommand;
// }
