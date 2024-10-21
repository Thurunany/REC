#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h> 
#include <PubSubClient.h>

// Wi-Fi
const char* ssid = "*";        
const char* password = "*";    

// Broker MQTT - HIVEMQ
const char* mqttServer = "*"; 
const int mqttPort = *;
const char* mqttUser = "*";  
const char* mqttPassword = "*";  

const char* mqttTopic = "thuany/soil_moisture";  
const char* alertTopic = "thuany/alert";        
const char* infoTopic = "thuany/info";         


WiFiClientSecure espClient; 
PubSubClient client(espClient);

#define soil_moist_pin 33  
static unsigned long lastInfoPublish = 0;

// conecta wifi
void setupWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("conectando ao Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); 
    Serial.print(".");
  }
  Serial.println("\nconectado!");
  Serial.print("Endereço IP do ESP32: ");
  Serial.println(WiFi.localIP());
}

// conecta MQTT
void connectToMQTT() {
  espClient.setInsecure();
  
  while (!client.connected()) {
    Serial.println("conectando o MQTT Broker...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("conectado ao MQTT Broker!");
    } else {
      Serial.print("Falha, erro = ");
      Serial.println(client.state());
      delay(2000); // 2 seg
    }
  }
}


// input de informação
void setup() {
  Serial.begin(115200);
  pinMode(soil_moist_pin, INPUT);
  setupWiFi();
  client.setServer(mqttServer, mqttPort);
  connectToMQTT();
}


void loop() {
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();

  int moistureLevel = analogRead(soil_moist_pin);
  
  char msg[50];
  snprintf(msg, 50, "Umidade do solo: %d", moistureLevel);
  Serial.println(msg);
  client.publish(mqttTopic, msg);
  float moisturePercentage = (4095 - moistureLevel) / 40.95;  // Converter o valor lido para porcentagem de umidade
  char alertMsg[100]; 

  if (moisturePercentage < 20) {
    snprintf(alertMsg, 100, "ALERTA: Nível de umidade do solo muito baixo (crítico)! Umidade: %.2f%%", moisturePercentage);
    Serial.println(alertMsg); 
    client.publish(alertTopic, alertMsg);  
  } else if (moisturePercentage < 40) {
    snprintf(alertMsg, 100, "Atenção: Nível de umidade otimo. Umidade: %.2f%%", moisturePercentage);
    Serial.println(alertMsg);  
    client.publish(alertTopic, alertMsg);  
  } else if (moisturePercentage < 60) {
    snprintf(alertMsg, 100, "Umidade em nível bom. Umidade: %.2f%%", moisturePercentage);
    Serial.println(alertMsg);  
    client.publish(alertTopic, alertMsg);  
  } else if (moisturePercentage < 80) {
    snprintf(alertMsg, 100, "Umidade em nível médio. Umidade: %.2f%%", moisturePercentage);
    Serial.println(alertMsg); 
    client.publish(alertTopic, alertMsg); 
  } else {
    snprintf(alertMsg, 100, "Solo com umidade alta. Umidade: %.2f%%", moisturePercentage);
    Serial.println(alertMsg);
    client.publish(alertTopic, alertMsg); 
  }

  unsigned long currentMillis = millis();
  if (currentMillis - lastInfoPublish > 10000) {
    lastInfoPublish = currentMillis;

    char systemInfo[150];
    snprintf(systemInfo, 150, "IP ESP32: %s, IP Broker: %s, Porta Broker: %d, Porta Cliente: %d", 
             WiFi.localIP().toString().c_str(), mqttServer, mqttPort, espClient.localPort());
    
    // Publicando as informações no tópico MQTT
    Serial.println(systemInfo);
    client.publish(infoTopic, systemInfo);
  }
  
  delay(5000);  // 5 seg
}
