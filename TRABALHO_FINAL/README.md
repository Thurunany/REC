# Monitoramento de Umidade do Solo com ESP32S e MQTT

Este projeto utiliza um **ESP32S** para monitorar a umidade do solo e enviar os dados coletados para um Broker MQTT. A solução permite monitoramento remoto dos dados em tempo real, podendo ser integrada com plataformas de visualização como o **Grafana**.

## 🚀 Funcionalidades
- **Leitura de umidade do solo**: Utiliza um sensor de umidade (higrômetro).
- **Envio de dados MQTT**:
  - Valores brutos do sensor.
  - Percentual de umidade do solo.
  - Alertas de umidade muito baixa ou muito alta.
  - Informações da rede (IP, portas, etc.).
- **Monitoramento remoto**: Dados podem ser visualizados em dashboards.

---

## 🛠️ Requisitos e Preparação

### 📋 Hardware Necessário
1. **NodeMCU ESP32S**
2. **Sensor de Umidade do Solo (Higrômetro)**

### 📥 Software e Bibliotecas
- **Arduino IDE**
  - Baixe e instale a IDE do [Arduino](https://www.arduino.cc/en/software).
- **Bibliotecas**:
  - `WiFi.h`
  - `WiFiClientSecure.h`
  - `PubSubClient.h`
- Broker MQTT configurado (ex.: [HiveMQ](https://www.hivemq.com)).

---

## ⚙️ Configuração do Projeto

### Conexões Físicas
1. Conecte o pino **S** do sensor de umidade ao pino **33** do ESP32.
2. Conecte o pino **VCC** do sensor ao **3.3V** do ESP32.
3. Conecte o pino **GND** do sensor ao **GND** do ESP32.

### Parâmetros a Configurar no Código
Abra o arquivo do código no Arduino IDE e edite as seguintes variáveis:
```cpp
const char* ssid = "SEU_WIFI";          // Nome da sua rede Wi-Fi
const char* password = "SUA_SENHA";    // Senha da sua rede Wi-Fi
const char* mqttServer = "SEU_BROKER"; // Endereço do Broker MQTT
const int mqttPort = 8883;             // Porta do Broker MQTT
const char* mqttUser = "SEU_USUARIO";  // Usuário do Broker MQTT
const char* mqttPassword = "SUA_SENHA"; // Senha do Broker MQTT
