# EspARP

A ESP32 library designed to interacting directly with the lwIP stack's ARP functionality. The library is intended to provide users with an easy-to-use interface that abstracts the complexities of ARP messaging on an ESP32 platform.



## Usage 

### Send ARP reqeust

```
sendRequest("192.168.1.1"); // Pass target IP using c-string

String target_ip = "192.168.1.1";
sendRequest(target_ip);     // Pass target Ip using String
```


```

```
