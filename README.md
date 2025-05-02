# espARPsp32ARP

A ESP32 library designed to interacting directly with the lwIP stack's ARP functionality. This library provide users with an easy-to-use interface that abstracts the complexities of ARP messaging on an ESP32 platform.


## Usage 

### Send ARP reqeust
#### Initialize ARP
``` C++
#include <esp32ARP.h>
esp32ARP arp;
arp.init() // Initialize
```
#### Broadcast a ARP request to the network
``` C++
// Pass target IP using c-string
arp.sendRequest("192.168.1.1"); 

// Pass target Ip using String
String target_ip = "192.168.1.34";
arp.sendRequest(target_ip);
```

#### Lookup ARP table entry
``` C++
uint8_t mac1[6], mac2[6];

// Pass lookup IP using c-string
arp.lookupEntry("192.168.1.1", &mac1);

// Pass lookup Ip using String
String lookup_ip = "192.168.1.34";
arp.lookupEntry(lookup_ip, &mac2);     
```
