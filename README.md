# WSS ESP32 AdonisJS

La libreria sirve para mantener una conexion por medio de websocket hacia un servicio de adonisjs.



## Usage

Se recomienda usar PlatformIO para instalar la libreria. Agrega al archivo `platformio.ini`


Directly from Github:

```
lib_deps =
  https://github.com/lomeliDev/wss_esp32_adonis.git
```

## Ejemplos

La libreria cuenta con 3 modelos de conexion, conexion wifi manual, otra con wifimanager usando spifs para guardar los datos, en la version de wifimanager podemos reiniciar el dispositivo  con sus conexiones que guardo wifimanager.

## Auth WSS
Si requerimos autentificacion debemos mandar los campos wss_user y wss_pass , si no lo requerimos mandarlos vacio, tanto en conexion manual y con wifimanager

Conexion Manual:

```
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
```

## SPIFS WIFIMANAGER
Si utilizas la version de wifimanager es necesario subir al filesystem de spifs un archivo el cual debe llamarse `wss.json`

```
{
    "ssid": "",
    "pass": "",
    "token": "",
    "host": "",
    "port": "",
    "path": "",
    "channel": "",
    "wss_user": "",
    "wss_pass": ""    
}
```

Con WifiManager y pin de Reset:

```
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
```


## WSS DATA
En los 3 ejemplos existe una variable tipo string `dataReceived` la cual contiene el ultimo mensaje que mando el servicio de websocket, con esta variable podemos interpretar sus respuestas, la respuesta que nos regresa es un json. Despues de leer la variable debemos limpiarla.



## Compatible Hardware

Por el momento solo funciona para el ESP32.

## License

This code is released under the MIT License.


