/*

}*/
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifimulti;
void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.mode(WIFI_STA);
  wifimulti.addAP("Janis", "Rociof36050g*");
}

void loop() {
  if((wifimulti.run() == WL_CONNECTED)) {
      WiFiClient client;
      HTTPClient http;
      Serial.println("[HTTP] Iniciando");
      http.begin(client,"http://arduino.tips/asciilogo.txt");
    
      Serial.println("[HTTP] Get...");
      http.GET();
      String respuesta = http.getString();
      Serial.print(respuesta);
      http.end();
      delay(90000);
  }
}
