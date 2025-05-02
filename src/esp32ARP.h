#ifndef ESP32ARP_H
#define ESP32ARP_H

#include "Arduino.h"
#include "esp_netif.h"
#include "esp_netif_net_stack.h"
#include "lwip/tcpip.h"
#include "lwip/etharp.h"
#include "lwip/sys.h"
#include <WiFi.h>
#include <cstring>
#include <cstdint>

class esp32ARP {
private:
  esp_netif_t* esp_netif_;
  struct netif *netif_;

  /* Requesting ARP package to send to lwip */
  inline void etharpRequestHandler_(const ip4_addr_t *target_ip);
  /* Find IP entrie from ARP table */
  inline int etharpFindAddrHandler_(const ip4_addr_t *target_ip, uint8_t *mac_addr = nullptr);

public:
  esp32ARP();

  /* Broadcast ARP package to look for certain IP */
  int sendRequest(char cstring_target_ip[]);
  int sendRequest(String sting_target_ip);

  /* Find entrie from ARP table */
  int lookupEntry(char cstring_target_ip[], uint8_t mac_addr[6]);
  int lookupEntry(String string_target_ip, uint8_t mac_addr[6]);

};

#endif
