# Monitoramento de Umidade do Solo com ESP32S e MQTT

Este projeto utiliza um **ESP32S** para monitorar a umidade do solo e enviar os dados coletados para um Broker MQTT. A solução permite o monitoramento remoto em tempo real, utilizando plataformas de visualização como o **Grafana**.

---

## Funcionalidades

- **Leitura de Umidade do Solo**: Utiliza um sensor higrômetro para capturar dados.
- **Envio de Dados via MQTT**:
  - Dados brutos do sensor.
  - Percentual de umidade do solo.
  - Alertas em casos de níveis críticos.
  - Informações de rede e sistema.
- **Monitoramento Remoto**: Dados disponíveis em dashboards criados no **Grafana**.

---

## Requisitos

### Hardware Necessário

- **NodeMCU ESP32S**
- **Sensor de Umidade do Solo (Higrômetro)**

### Software Necessário

- **Arduino IDE**
  - Baixe e instale a [Arduino IDE](https://www.arduino.cc/en/software).
- **Broker MQTT**
  - Configure um serviço como [HiveMQ](https://www.hivemq.com).
- **Grafana**
  - Baixe e instale o [Grafana](https://grafana.com/).

### Bibliotecas Utilizadas

As seguintes bibliotecas devem estar instaladas na Arduino IDE:

- `WiFi.h`
- `WiFiClientSecure.h`
- `PubSubClient.h`

---

## Configuração do Projeto

### Conexões do Hardware

1. Conecte o pino **S** do sensor de umidade ao pino **33** do ESP32.
2. Conecte o pino **VCC** do sensor ao **3.3V** do ESP32.
3. Conecte o pino **GND** do sensor ao **GND** do ESP32.

### Configuração do Código

No código fornecido, edite as seguintes variáveis com os dados da sua rede Wi-Fi e do Broker MQTT:

```cpp
const char* ssid = "SEU_WIFI";          // Nome da sua rede Wi-Fi
const char* password = "SUA_SENHA";    // Senha da sua rede Wi-Fi
const char* mqttServer = "SEU_BROKER"; // Endereço do Broker MQTT
const int mqttPort = 8883;             // Porta do Broker MQTT
const char* mqttUser = "SEU_USUARIO";  // Usuário do Broker MQTT
const char* mqttPassword = "SUA_SENHA"; // Senha do Broker MQTT
``` 
---

## Configuração do Grafana

- Conecta o data source MQTT no grafana, colocando os dados cadastrais do HiveMQ Cloud
- Crie o dashboard como desejar
