
#include <Arduino.h>
#include <FS.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WebSocketsClient.h>

#include "Globals.h"

/*Wifi*/
bool shouldSaveConfig = false;
bool jsonReady = false;
int wifiReady = 0;
bool debugWifiManager = true;
bool checkSetups = false;
unsigned long LASTWIFI = 0;
const int timeWaitWifi = 5000;
const int timeWaitWSS = 5000;

/*WebSocket*/
String hostGlobal = "";
char ssid[32] = "";
char pass[32] = "";
char token[32] = "";
char host[32] = "";
char port[16] = "";
char path[16] = "";
char channel[16] = "";
char wss_user[32] = "";
char wss_pass[32] = "";
unsigned long LASTWSS = 0;
String dataReceived = "";

/*Leds*/
int myLed = 33;

/*Reset*/
unsigned long LASTRESET = 0;
const int timeReset = 5000;

void dataManual(char _ssid[32], char _pass[32], char _token[32], char _host[32], char _port[16], char _path[16], char _channel[16], char _wss_user[32], char _wss_pass[32])
{
    hostGlobal = String(_host);
    strcpy(ssid, _ssid);
    strcpy(pass, _pass);
    strcpy(token, _token);
    strcpy(host, _host);
    strcpy(port, _port);
    strcpy(path, _path);
    strcpy(channel, _channel);
    strcpy(wss_user, _wss_user);
    strcpy(wss_pass, _wss_pass);
}

void mountSPIFS()
{
    if (!SPIFFS.begin())
    {
        Serial.println("SPIFFS Mount Failed");
    }
    else
    {
        Serial.println("SPIFFS Mount OK");
    }
}