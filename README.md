# esp32ARP

A ESP32 library designed to interact with the lwIP stack's ARP functionality. This library provide users with an easy-to-use interface that abstracts the complexities of ARP messaging on an ESP32 platform.



## Examples
An example of how to acquire the MAC address of the gateway.
``` cpp
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
```

## Fucntions 

### Initialize and setup 
Must connect to Wi-Fi before initialization.
``` cpp
#include <esp32ARP.h>

esp32ARP arp;
arp.init(); 
```
### Send ARP reqeust
Broadcast a ARP request to the network.
``` cpp
// Pass target IP using c-string
arp.sendRequest("192.168.1.1"); 

// Pass target Ip using String
String target_ip = "192.168.1.34";
arp.sendRequest(target_ip);
```
### Lookup ARP table entry
Check ARP table entry to see if the device on the IP has responded.
``` cpp
mac_addr_t mac1, mac2;

// Pass lookup IP using c-string
arp.lookupEntry("192.168.1.1", mac1);

// Pass lookup Ip using String
String lookup_ip = "192.168.1.34";
arp.lookupEntry(lookup_ip, mac2);     
```
## Data Type
### mac_addr_t
``` cpp
struct mac_addr {
  uint8_t addr[8]
};
typedef mac_addr mac_addr_t;
```
