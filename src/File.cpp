
#include <Arduino.h>

#include <ArduinoJson.h>
#include "SPIFFS.h"

#include "File.h"
#include "Globals.h"
#include "Logs.h"

void readJson(void)
{
    logS("readJson...");
    jsonReady = false;

    if (SPIFFS.exists("/wss.json"))
    {
        File configFile = SPIFFS.open("/wss.json", "r");
        if (configFile)
        {
            size_t size = configFile.size();
            std::unique_ptr<char[]> buf(new char[size]);
            configFile.readBytes(buf.get(), size);
            String myJson = buf.get();
            String jsonRead = "";

            if (myJson.indexOf("{") >= 0 && myJson.indexOf("}") >= 0)
            {
                int n = myJson.length();
                char jsonCH[n + 1];
                strcpy(jsonCH, myJson.c_str());
                for (int i = 0; i < n; i++)
                {
                    jsonRead += String(myJson[i]);
                    if (myJson[i] == '}')
                    {
                        break;
                    }
                }
            }
            else
            {
                logS(F("no JSON "));
                return;
            }

            StaticJsonDocument<1024> doc;
            DeserializationError error = deserializeJson(doc, jsonRead);
            if (error)
            {
                logS(F("deserializeJson() failed: "));
                return;
            }

            const char *_host = doc["host"];
            hostGlobal = String(_host);
            strcpy(ssid, doc["ssid"]);
            strcpy(pass, doc["pass"]);
            strcpy(token, doc["token"]);
            strcpy(host, doc["host"]);
            strcpy(port, doc["port"]);
            strcpy(path, doc["path"]);
            strcpy(channel, doc["channel"]);
            strcpy(wss_user, doc["wss_user"]);
            strcpy(wss_pass, doc["wss_pass"]);
            jsonReady = true;
        }
        else
        {
            logS("failed to load json config");
        }
        configFile.close();
    }
    else
    {
        logS("failed json config not exists");
    }
}

void writeJson(void)
{
    logS("");
    logS("writeJson...");
    jsonReady = false;
    DynamicJsonDocument json(1024);
    json["ssid"] = ssid;
    json["pass"] = pass;
    json["token"] = token;
    json["host"] = host;
    json["port"] = port;
    json["path"] = path;
    json["channel"] = channel;
    json["wss_user"] = wss_user;
    json["wss_pass"] = wss_pass;
    File configFile = SPIFFS.open("/wss.json", "w");
    if (!configFile)
    {
        logS("failed to open config file for writing");
    }
    else
    {
        serializeJsonPretty(json, Serial);
        serializeJson(json, configFile);
        shouldSaveConfig = false;
        jsonReady = true;
    }
    configFile.close();
}
