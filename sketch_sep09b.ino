
#define BLYNK_TEMPLATE_ID "TMPL2tkxnFHw_"
#define BLYNK_TEMPLATE_NAME "REDES"
#define BLYNK_AUTH_TOKEN "DXz3zEDXnEQAPLzZZGovdObMqoiTUsrH"
// Inclua as bibliotecas necessárias
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN; // Seu Token de Autenticação do Blynk
char ssid[] = "Wifi 2";       // Nome da sua rede Wi-Fi
char pass[] = "conta4900";      // Senha da sua rede Wi-Fi

#define soil_moist_pin 33  // Pin do sensor de umidade
BlynkTimer timer;

void setup() {
  // Inicializa a serial e o Blynk
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
  // Configura o temporizador para enviar os dados ao Blynk
  timer.setInterval(2000L, sendSensorData);  // Envia a cada 2 segundos
}

void sendSensorData() {
  int moistureLevel = analogRead(soil_moist_pin); // Lê o sensor de umidade
  Serial.println(moistureLevel); // Exibe no monitor serial
  Blynk.virtualWrite(V33, moistureLevel);  // Envia o valor para o Virtual Pin V1 no Blynk
}

void loop() {
  Serial.println(analogRead(soil_moist_pin));
  delay(500);
  Blynk.run();  // Mantém a conexão com o Blynk ativa
  timer.run();  // Roda o temporizador para enviar dados regularmente
}
