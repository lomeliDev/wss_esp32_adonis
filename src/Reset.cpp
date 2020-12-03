
#include <Arduino.h>


#include "Reset.h"

#include "Auth.h"
#include "File.h"
#include "Globals.h"
#include "Logs.h"


void setupReset(void){
    pinMode(RSTUsiuario, INPUT_PULLUP);
}


void Reset(void){
    logS("Reset...");
    logS("Desconectando...");
    resetSettingsWifi();
    WiFi.disconnect(true);
    WiFi.disconnect(true, true);
    WiFi.begin("0","0");
    delay(2000);
    logS("Reiniciando...");
    strcpy(ssid, "");
    strcpy(pass, "");
    strcpy(token, "");
    strcpy(host, "");
    strcpy(port, "");
    strcpy(path, "");
    strcpy(channel, "");
    strcpy(wss_user, "");
    strcpy(wss_pass, "");
    writeJson();
    shouldSaveConfig = false;
    resetSettingsWifi();
    ESP.restart();
}


void loopReset(void){
    if (digitalRead(RSTUsiuario) == HIGH)
    {
        LASTRESET = millis();
        int x = 0;
        while (x == 0)
        {
            if (digitalRead(RSTUsiuario) == HIGH)
            {
                delay(500);
            } else {
                x = 1;
            }
        }
        if ((millis() - LASTRESET) >= timeReset)
        {
            Reset();
        }
        LASTRESET = 0;
    }
}