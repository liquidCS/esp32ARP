#include "esp32ARP.h"

/* ===== PRIVATE ===== */

inline int esp32ARP::etharpRequestHandler_(const ip4_addr_t *target_ip) {
  LOCK_TCPIP_CORE();
  int request_status = etharp_request(netif_, target_ip);
  UNLOCK_TCPIP_CORE();
  return request_status;
} 

inline int esp32ARP::etharpFindAddrHandler_(const ip4_addr_t *target_ip, uint8_t *mac_addr) {
  const ip4_addr_t *ipaddr_ret;
  struct eth_addr *eth_ret;

  int find_status = etharp_find_addr(netif_, target_ip, &eth_ret, &ipaddr_ret);
  if(find_status >= 0) {
    if(mac_addr != nullptr) {
      memcpy(mac_addr, &eth_ret->addr, sizeof(uint8_t)*6); // Copy MAC addr from ARP table to output
    }
    return ERR_OK;
  } else {
    return find_status; 
  }
}


/* ===== PUBLIC ===== */

int esp32ARP::init() {
  esp_netif_ = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
  if(esp_netif_ == nullptr) {
    Serial.println("Can't get esp_netif. Please make sure WiFi is properly connected and initialized");
    return ERR_IF;
  }

  netif_ = (struct netif *)esp_netif_get_netif_impl(esp_netif_);
  if(netif_ == nullptr) {
    Serial.println("Can't get netif");
    return ERR_IF;
  }
  return ERR_OK;
}

/* Send ARP request */ 
int esp32ARP::sendRequest(const char cstring_target_ip[]) {
  ip4_addr_t target_ip;
  if(!ip4addr_aton(cstring_target_ip, &target_ip)) {
    Serial.println("Error: Invalid target IP address.");
    return ERR_VAL;
  }
  return etharpRequestHandler_(&target_ip);
}

int esp32ARP::sendRequest(const String sting_target_ip) {
  ip4_addr_t target_ip;
  if(!ip4addr_aton(sting_target_ip.c_str(), &target_ip)) {
    Serial.println("Error: Invalid target IP address.");
    return ERR_VAL;
  }
  return etharpRequestHandler_(&target_ip);
}

int esp32ARP::sendRequest(const uint32_t uint32_target_ip) {
  ip4_addr_t target_ip = {uint32_target_ip};
  return etharpRequestHandler_(&target_ip);
}

/* Find entrie from ARP table */
int esp32ARP::lookupEntry(const char cstring_target_ip[], mac_addr_t &mac_addr) {
  ip4_addr_t target_ip;
  if(!ip4addr_aton(cstring_target_ip, &target_ip)) {
    Serial.println("Error: Invalid target IP address.");
    return ERR_VAL;
  }
  return etharpFindAddrHandler_(&target_ip, mac_addr.addr);
}

int esp32ARP::lookupEntry(const String string_target_ip, mac_addr_t &mac_addr) {
  ip4_addr_t target_ip;
  if(!ip4addr_aton(string_target_ip.c_str(), &target_ip)) {
    Serial.println("Error: Invalid target IP address.");
    return ERR_VAL;
  }
  return etharpFindAddrHandler_(&target_ip, mac_addr.addr);
}

int esp32ARP::lookupEntry(const uint32_t uint32_target_ip, mac_addr_t &mac_addr) {
  ip4_addr_t target_ip = {uint32_target_ip};
  return etharpFindAddrHandler_(&target_ip, mac_addr.addr);
}


/* ===== Useful functions ===== */

void printMacAddr(const mac_addr_t &mac_addr) {
  Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X", mac_addr.addr[0], mac_addr.addr[1], mac_addr.addr[2], mac_addr.addr[3], mac_addr.addr[4], mac_addr.addr[5]);
}

void printlnMacAddr(const mac_addr_t &mac_addr) {
  Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\n", mac_addr.addr[0], mac_addr.addr[1], mac_addr.addr[2], mac_addr.addr[3], mac_addr.addr[4], mac_addr.addr[5]);
}
