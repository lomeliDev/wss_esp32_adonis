
#include <Arduino.h>

#include <ArduinoJson.h>
#include <WebSocketsClient.h>

#include "wss.h"
#include "Auth.h"
#include "dataReceived.h"
#include "Globals.h"
#include "Logs.h"

WebSocketsClient webSocket;
uint16_t cntrConexiones = 0;

String converter(uint8_t *str)
{
	return String((char *)str);
}

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{
	String dataResponse = converter(payload);
	switch (type)
	{
	case WStype_DISCONNECTED:
		logS("[WSc] Disconnected!");
		break;
	case WStype_CONNECTED:
		logS("[WSc] WStype_CONNECTED!");
		webSocket.sendTXT("{\"t\": 1,\"d\": {\"topic\": \"" + String(channel) + "\"}}");
		cntrConexiones++;
		break;

	case WStype_TEXT:
		//logS("[WSc] WStype_TEXT!");
		if (dataResponse.indexOf("{\"t\":3") >= 0)
		{
			logS("[WSc] Connected to WSS Channel");
			if (wifiReady == 2)
			{
				wifiReady = 3;
			}
		}
		else
		{
			if (dataResponse.indexOf("{\"t\":7") >= 0)
			{
				LASTWSS = 0;
				dataReceived = "";
				StaticJsonDocument<1024> doc;
				DeserializationError error = deserializeJson(doc, dataResponse);
				if (error)
				{
					logS("Json Decode Error WSS");
				}
				else
				{
					String data = doc["d"]["data"];
					if (data.indexOf(String(token)) >= 0)
					{
						dataReceived = data;
					}
				}
			}
		}
		break;
	case WStype_BIN:
	case WStype_ERROR:
	case WStype_PING:
	case WStype_PONG:
	case WStype_FRAGMENT_TEXT_START:
	case WStype_FRAGMENT_BIN_START:
	case WStype_FRAGMENT:
	case WStype_FRAGMENT_FIN:
		break;
	default:
		logS("[WSc] NO IDENTIFICADO");
		break;
	}
}

void setupWss(void)
{
	if (wifiReady == 1)
	{
		logS("WSS Token : " + String(token));
		logS("WSS Host : " + String(hostGlobal));
		logS("WSS Port : " + String(port));
		logS("WSS Path : " + String(path));
		logS("WSS Channel : " + String(channel));
		webSocket.begin(hostGlobal, String(port).toInt(), path);
		webSocket.onEvent(webSocketEvent);

		if(String(wss_user) != "" && String(wss_pass) != ""){
			webSocket.setAuthorization(wss_user, wss_pass);
		}
		
		webSocket.setReconnectInterval(3000);
		wifiReady = 2;
	}
}

void WSTxt(String str)
{
	webSocket.sendTXT(str);
}

void WSLoop(void)
{
	webSocket.loop();
}

void attWSS(void)
{
	if (LASTWIFI > 0)
	{
		if (wifiReady == 0 && (millis() - LASTWIFI) >= timeWaitWifi)
		{
			LASTWIFI = millis();
			if(String(ssid) != "" && String(pass) != ""){
				setupWifiManual();
			} else {
				setupWifi();
			}
		}
		else
		{
			if (wifiReady == 1 && (millis() - LASTWIFI) >= timeWaitWSS)
			{
				setupWss();
				LASTWIFI = 0;
			}
		}
	}

	if (wifiReady == 2 && checkSetups == false)
	{
		checkSetups = true;
	}

	if (wifiReady >= 2)
	{
		webSocket.loop();
	}

	if (wifiReady == 3)
	{
		loopDataReceived();
	}
}
