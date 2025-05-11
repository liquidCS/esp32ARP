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

// Storing Mac address
struct mac_addr {
    uint8_t addr[6]; 
};
typedef mac_addr mac_addr_t;


class esp32ARP {
private:
  esp_netif_t *esp_netif_;
  struct netif *netif_;

  /* Requesting ARP package to send to lwip */
  inline int etharpRequestHandler_(const ip4_addr_t *target_ip);
  /* Find IP entrie from ARP table */
  inline int etharpFindAddrHandler_(const ip4_addr_t *target_ip, uint8_t *mac_addr = nullptr);

public:
  /* Initialize */
  int init();

  /* Broadcast ARP package to look for certain IP */
  int sendRequest(const char cstring_target_ip[]);
  int sendRequest(const String sting_target_ip);
  int sendRequest(const uint32_t uint32_target_ip);

  /* Find entrie from ARP table */
  int lookupEntry(const char cstring_target_ip[], mac_addr_t &mac_addr);
  int lookupEntry(const String string_target_ip, mac_addr_t &mac_addr);
  int lookupEntry(const uint32_t uint32_target_ip, mac_addr_t &mac_addr);

};


/* Print MAC address */
void printMacAddr(const mac_addr_t &mac_addr);
void printlnMacAddr(const mac_addr &mac_addr);

#endif
