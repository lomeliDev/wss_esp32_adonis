#include <Arduino.h>
#include <WSS_esp32_Adonis.h>

#define RSTUsiuario     5 //Pin Reset

void setup()
{
  Serial.begin(38400);
  mountSPIFS();
  setupReset();
  LASTWIFI = millis();
}

void loop()
{
  attWSS();
  loopReset();
  if (wifiReady == 3)
  {
    if (dataReceived != "")
    {
      Serial.println("\n\n");
      Serial.println(dataReceived);
      Serial.println("\n\n");
      dataReceived = "";
    }
  }
}