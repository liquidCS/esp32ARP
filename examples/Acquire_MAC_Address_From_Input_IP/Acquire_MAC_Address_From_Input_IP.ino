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
  if(Serial.available() > 0) {
    String input_ip = Serial.readStringUntil('\n');

    if(arp.sendRequest(input_ip) != 0) return; // Send ARP request
    delay(1000);
      
    mac_addr_t mac;
    if(arp.lookupEntry(input_ip, mac) == 0) {
      Serial.print(input_ip);
      Serial.print("'s MAC address is ");
      printlnMacAddr(mac);
    }
    else {
      Serial.println("Error: Can't get MAC address");
    }
  }
}
