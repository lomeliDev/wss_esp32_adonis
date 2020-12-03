
#include <Arduino.h>
#include <ArduinoJson.h>

#include "dataReceived.h"
#include "Globals.h"
#include "logs.h"
#include "Reset.h"

void loopDataReceived(void)
{
    if (dataReceived != "")
    {
        if (dataReceived.indexOf("RESET") >= 0)
        {
            Reset();
            dataReceived = "";            
        }

    }
}
