#include <WiFi.h>
#include <esp32ARP.h>

const char* ssid =     "*****";
const char* password = "*****";
esp32ARP arp; 

void setup() {
  Serial.begin(115200);
  delay(2000);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) delay(1500);

  arp.init(); // Initialize after connected to WiFi
}

void loop() {
  arp.sendRequest(WiFi.gatewayIP()); // Broadcast ARP requst for the gateway IP
  delay(1000);  // Wait 1 second for gateway to respond
  
  mac_addr_t mac;
  arp.lookupEntry(WiFi.gatewayIP(), mac); // Check ARP table for respond
  printlnMacAddr(mac); // Print out the MAC address of the gateway
}
