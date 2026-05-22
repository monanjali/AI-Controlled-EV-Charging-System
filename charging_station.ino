#include <WiFi.h>
#include <HTTPClient.h>
// WiFi credentials
const char* ssid = "Redmi 12";
const char* password = "puji1234";
// Server endpoint
const char* server = "http://192.168.187.76:3000/api/voltage";
// Voltage sensor analog pins
#define SOLAR_PIN 34
#define DC_PIN 35
#define REF_VOLTAGE 3.3
#define ADC_RESOLUTION 4095.0
#define VOLTAGE_SCALE 5.0

void setup() {
Serial.begin(115200);
WiFi.begin(ssid, password);
Serial.print("Connecting to WiFi");
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}
Serial.println("\nWiFi connected.");
}
void loop() {
int raw_solar = analogRead(SOLAR_PIN);
int raw_dc = analogRead(DC_PIN);
float solar_voltage = (raw_solar * REF_VOLTAGE / ADC_RESOLUTION) * VOLTAGE_SCALE;
float dc_voltage = (raw_dc * REF_VOLTAGE / ADC_RESOLUTION) * VOLTAGE_SCALE;
Serial.printf("Solar Voltage: %.2f V, DC Voltage: %.2f V\n", solar_voltage, dc_voltage);
if (WiFi.status() == WL_CONNECTED) {
HTTPClient http;
http.begin(server);
http.addHeader("Content-Type", "application/json");
String jsonPayload = "{\"solar\":" + String(solar_voltage,2) +
",\"dc\":" + String(dc_voltage,2) + "}";
int httpResponseCode = http.POST(jsonPayload);
http.end();
}
delay(3000);
}