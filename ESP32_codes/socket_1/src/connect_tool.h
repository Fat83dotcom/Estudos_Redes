#ifndef CONNECT_TOOL_H
#define CONNECT_TOOL_H

/* 
Este arquivo implementa o WiFiManager com uma configuração mínima
*/

#include <Arduino.h>
#include <WiFiManager.h>
#include <WiFi.h>

WiFiManager wfm;
WiFiClient espClient;
WiFiServer espServer(80);

void reconnectWifi(){
  while (1) {
    wfm.autoConnect("BrainStorm Tecnologia - IOT");
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println(WiFi.SSID());
      Serial.println(WiFi.localIP());
      break;
    }
    else{
      wfm.resetSettings();
      if (!wfm.startConfigPortal("BrainStorm Tecnologia - IOT")) {                                      // Nome da Rede e Senha gerada pela ESP
        Serial.println("Falha ao conectar");
        delay(2000);
        ESP.restart();
      }
      else{
        Serial.println("Conectado na Rede!!!");
        break;
      }
    }
  }  
}

// callback que indica que o ESP entrou no modo AP
void configModeCallback(WiFiManager *myWiFiManager) {
  Serial.println("Entrou no modo de configuração");
  Serial.println(WiFi.softAPIP());                      // imprime o IP do AP
  Serial.println(myWiFiManager->getConfigPortalSSID()); // imprime o SSID criado da rede
}

// Callback que indica que salvamos uma nova rede para se conectar (modo estação)
void saveConfigCallback() {
  Serial.println("Configuração salva");
}

void WifiManager() {
  wfm.setAPCallback(configModeCallback);
  wfm.setSaveConfigCallback(saveConfigCallback);
  // Fixa um IP na rede.
  wfm.setSTAStaticIPConfig(
    IPAddress(192,168,0,6),
    IPAddress(192,168,0,1),
    IPAddress(255,255,255,0)
  ); // optional DNS 4th argument
  reconnectWifi();
}

#endif