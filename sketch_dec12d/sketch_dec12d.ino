#include "ESP8266WiFi.h"
#include "WiFiClientSecure.h"
#include "SimpleDHT.h"
const char* wifi_ssid = "UPC1427586";             // SSID
const char* wifi_password = "Mm2zsxsynrt7";         // WIFI kód
const char* apiKeyIn = "nbuZndzsAmSOjQvaXVpDgEDV6sPagRAl";      // API KEY megadása
const unsigned int writeInterval = 25000; // írási intervallum (ms-ban)
const char* https_host = "api.asksensors.com";         // ASKSENSORS host név
const int https_port = 443;                        // https port
const char* https_fingerprint =  "E0 B3 5B 92 2B F3 48 FA 1E E3 07 6F 01 06 0D D1 AC B0 9B 85";
int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);
WiFiClientSecure client;
void getTem()
{
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    delay(100);
    return;
  }
  if (!client.connect(https_host, https_port)) {
  delay(200);
  return;
  }
  String url = "/write/";
  url += apiKeyIn;
  url += "?module1=";
  url += ((int)temperature);
  url += "&module2=";
  url += ((int)humidity);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + https_host + "\r\n" +
               "Connection: close\r\n\r\n");
  client.connected();
}
void setup() {
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  client.setInsecure();
}
void loop() {
         getTem();
  delay(1000);

}
