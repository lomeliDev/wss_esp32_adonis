#include <Arduino.h>
#include <WSS_esp32_Adonis.h>

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