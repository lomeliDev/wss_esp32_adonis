
#include <Arduino.h>

#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>
#include <WiFi.h>
#include <WiFiMulti.h>

#include "Auth.h"

#include "File.h"
#include "Globals.h"
#include "Logs.h"
#include "Reset.h"

DNSServer dns;
AsyncWebServer server(80);
AsyncWiFiManager wm(&server, &dns);
WiFiMulti WiFiMulti;

void saveConfigCallback(void)
{
    logS("Should save config");
    shouldSaveConfig = true;
}


void setupWifiManual(void)
{
    WiFiMulti.addAP(ssid, pass);
    while (WiFiMulti.run() != WL_CONNECTED)
    {
        delay(100);
    }

    logS("Conectado ESP32 manual");
    logS("local ip");
    logS(String(WiFi.localIP().toString().c_str()));
    logS(String(WiFi.gatewayIP().toString().c_str()));
    logS(String(WiFi.subnetMask().toString().c_str()));
    logS(String(WiFi.dnsIP().toString().c_str()));
    wifiReady = 1;
}

void setupWifi(void)
{
    logS("setupWifi...");
    wifiReady = 0;
    readJson();

    if (String(ssid) != "" && String(token) == "")
    {
        Reset();
    }

    String mySSID = String(ssid);
    if (mySSID != "")
    {
        WiFiMulti.addAP(ssid, pass);
        while (WiFiMulti.run() != WL_CONNECTED)
        {
            delay(100);
        }

        logS("Conectado ESP32 manual");
        logS("local ip");
        logS(String(WiFi.localIP().toString().c_str()));
        logS(String(WiFi.gatewayIP().toString().c_str()));
        logS(String(WiFi.subnetMask().toString().c_str()));
        logS(String(WiFi.dnsIP().toString().c_str()));
        wifiReady = 1;
    }
    else
    {
        wm.setDebugOutput(debugWifiManager);
        wm.setSaveConfigCallback(saveConfigCallback);
        AsyncWiFiManagerParameter custom_token("token", "Token", token, 32);
        AsyncWiFiManagerParameter custom_host("host", "Host WSS", host, 32);
        AsyncWiFiManagerParameter custom_port("port", "Port", port, 16);
        AsyncWiFiManagerParameter custom_path("path", "Path", path, 16);
        AsyncWiFiManagerParameter custom_channel("channel", "Channel", channel, 16);
        AsyncWiFiManagerParameter custom_wss_user("wss_user", "Wss User", wss_user, 32);
        AsyncWiFiManagerParameter custom_wss_pass("wss_pass", "Wss Password", wss_pass, 32);

        wm.addParameter(&custom_token);
        wm.addParameter(&custom_host);
        wm.addParameter(&custom_port);
        wm.addParameter(&custom_path);
        wm.addParameter(&custom_channel);
        wm.addParameter(&custom_wss_user);
        wm.addParameter(&custom_wss_pass);

        wm.setAPStaticIPConfig(IPAddress(10, 0, 1, 1), IPAddress(10, 0, 1, 1), IPAddress(255, 255, 255, 0));

        if (!wm.autoConnect("ESP32-Rodolfo", "password"))
        {
            logS("failed to connect and hit timeout");
            delay(3000);
            ESP.restart();
            delay(5000);
        }
        logS("connected Wifi :) AQUI");
        strcpy(ssid, String(WiFi.SSID()).c_str());
        strcpy(pass, String(WiFi.psk()).c_str());
        strcpy(token, custom_token.getValue());
        strcpy(host, custom_host.getValue());
        strcpy(port, custom_port.getValue());
        strcpy(host, custom_host.getValue());
        strcpy(path, custom_path.getValue());
        strcpy(channel, custom_channel.getValue());
        strcpy(wss_user, custom_wss_user.getValue());
        strcpy(wss_pass, custom_wss_pass.getValue());

        if (shouldSaveConfig)
        {
            writeJson();
            readJson();
            delay(5000);
            ESP.restart();
        }
        logS("local ip");
        logS(String(WiFi.localIP().toString().c_str()));
        logS(String(WiFi.gatewayIP().toString().c_str()));
        logS(String(WiFi.subnetMask().toString().c_str()));
        logS(String(WiFi.dnsIP().toString().c_str()));
        wifiReady = 1;
    }
}

void resetSettingsWifi(void)
{
    wm.resetSettings();
}
