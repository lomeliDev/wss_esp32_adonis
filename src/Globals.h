
#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <FS.h>
#include "SPIFFS.h"
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WebSocketsClient.h>

/*Wifi*/
extern bool shouldSaveConfig;
extern bool jsonReady;
extern int wifiReady;
extern bool debugWifiManager;
extern bool checkSetups;
extern unsigned long LASTWIFI;
extern const int timeWaitWifi;
extern const int timeWaitWSS;

/*WebSocket*/
extern String hostGlobal;
extern char ssid[32];
extern char pass[32];
extern char token[32];
extern char host[32];
extern char port[16];
extern char path[16];
extern char channel[16];
extern char wss_user[32];
extern char wss_pass[32];
extern unsigned long LASTWSS;
extern String dataReceived;


/*Leds*/
extern int myLed;

/*Reset*/
extern unsigned long LASTRESET;
extern const int timeReset;

void dataManual(char _ssid[32], char _pass[32], char _token[32], char _host[32], char _port[16], char _path[16], char _channel[16], char _wss_user[32], char _wss_pass[32]);
void mountSPIFS();

#endif