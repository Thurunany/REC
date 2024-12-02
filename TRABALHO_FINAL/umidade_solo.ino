#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Wi-Fi
const char* ssid = "****";        
const char* password = "******";    

// Broker MQTT - HIVEMQ
const char* mqttServer = "*******.s1.eu.hivemq.cloud";
const int mqttPort = 8883;
const char* mqttUser = "*****";  
const char* mqttPassword = "*****";  

const char* mqttTopicRaw = "solo/raw";  
const char* mqttTopicPercentage = "solo/percentage";  
const char* alertTopic = "solo/alert";        
const char* infoTopic = "solo/info";        


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


// INPUT DE INFORMAÇÃO
void setup() {
  Serial.begin(115200);
  pinMode(soil_moist_pin, INPUT);
  setupWiFi();
  client.setServer(mqttServer, mqttPort);
  connectToMQTT();
}


 void loop() {
    // CONECTAR NO MQTT
    if (!client.connected()) {
      connectToMQTT();
    }
    client.loop();
  
    int moistureLevel = analogRead(soil_moist_pin);
    float moisturePercentage = (4095 - moistureLevel) / 40.95; 

    // DADO BRUTO DO ESP
    char rawMsg[10];
    snprintf(rawMsg, 10, "%d", moistureLevel);
    client.publish(mqttTopicRaw, rawMsg);
  
    // DADO PERCENTUAL DO ESP
    char percentageMsg[10];
    snprintf(percentageMsg, 10, "%.2f", moisturePercentage);
    client.publish(mqttTopicPercentage, percentageMsg);

    // DADOS DE PORTA IP CLIENTE/SERVIDOR
     char systemInfo[250];
        snprintf(systemInfo, 250, "{\"Bloco\": \"%s\", \"ESP32_IP\": \"%s\", \"Broker_IP\": \"%s\", \"Broker_Port\": %d, \"Client_Port\": %d}",
                "INFORMAÇÕES DE REDE", WiFi.localIP().toString().c_str(), mqttServer, mqttPort, espClient.localPort());
      client.publish(infoTopic, systemInfo);

    // DADOS DE UMIDADE DO SOLO
    char alertMsg[200];
    if (moisturePercentage < 20) {
        snprintf(alertMsg, 200, "{\"level\": \"%s\", \"description\": \"%s\", \"moisturePercentage\": %.2f}", 
                 "low", "Nivel de umidade baixo", moisturePercentage);
        client.publish(alertTopic, alertMsg);
    } else if (moisturePercentage > 80) {
        snprintf(alertMsg, 200, "{\"level\": \"%s\", \"description\": \"%s\", \"moisturePercentage\": %.2f}", 
                 "high", "Nivel de umidade alto", moisturePercentage);
        client.publish(alertTopic, alertMsg);
    }

  delay(5000); 
}