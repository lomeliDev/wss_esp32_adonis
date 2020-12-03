#include <Arduino.h>
#include <WSS_esp32_Adonis.h>

void setup()
{
  Serial.begin(38400);
  mountSPIFS();
  setupReset();
  LASTWIFI = millis();
  dataManual("ssid", "ssid_pwd", "wss_token", "wss_host", "wss_port", "wss_path", "wss_channel", "wss_user", "wss_pass");
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