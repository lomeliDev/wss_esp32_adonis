
#include <Arduino.h>

#include "Logs.h"
#include "Globals.h"
#include "wss.h"


void logS(String _msg){
    if(_msg != ""){
        String s = "{\"key\":\"Log\",\"request\":\""+String(_msg)+"\"}";
        Serial.println(s);
    }
}

void WriteS(String _msg){
    _msg.replace("{", "[");
    _msg.replace("}", "]");
    _msg.replace("\"", "\\\"");
    String s = "{\"key\":\"SendSerial\",\"request\":\"" + String(_msg) + "\"}";
    Serial.println(s);
}

void WritePasarelaWSS(String _msg){
    _msg.replace("\"", "\\\"");
    String dataTX = "{\"t\": 7,\"d\": {\"topic\": \"atm\",\"event\": \"pasarela\",\"data\": \""+_msg+"\"}}";
    WSTxt(dataTX);
}

