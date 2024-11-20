#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

// Configurações Wi-Fi
#define WIFI_SSID "AmericaNET"
#define WIFI_PASSWORD "00960096"

// Configurações do Adafruit IO
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "arturvictorio"
#define AIO_KEY "aio_wCng52wUqKxT67Q2BKCVAQjN3BX4"

// Pinos
#define MQ7_PIN A0    // Pino analógico conectado ao MQ-7
#define BUZZER_PIN D5 // Pino digital conectado ao buzzer passivo

// MQTT
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Tópico para enviar dados do sensor ao Adafruit IO
Adafruit_MQTT_Publish gasLevel = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/gas");

// Variáveis
int threshold = 900; // Valor limite do MQ-7 para ativar o alerta

void setup() {
  Serial.begin(115200);
  pinMode(MQ7_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  connectWiFi();
}

void loop() {
  // Leitura do valor analógico do MQ-7
  int gasValue = analogRead(MQ7_PIN);
  Serial.println("Nível de CO detectado: " + String(gasValue));

  // Controle do buzzer baseado no limite
  if (gasValue > threshold) {
    tone(BUZZER_PIN, 1000); // Ativa o buzzer com som de 1kHz
    Serial.println("⚠️ ALERTA: Nível perigoso detectado!");
  } else {
    noTone(BUZZER_PIN);     // Desativa o buzzer
  }

  // Conexão MQTT
  if (!mqtt.connected()) {
    connectMQTT();
  }

  // Publica o valor do sensor no Adafruit IO
  if (!gasLevel.publish(gasValue)) {
    Serial.println("Falha ao enviar dados ao Adafruit IO!");
  } else {
    Serial.println("Dados enviados ao Adafruit IO!");
  }

  delay(2000); // Intervalo entre as leituras
}

void connectWiFi() {
  Serial.print("Conectando ao WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi!");
}

void connectMQTT() {
  Serial.print("Conectando ao Adafruit IO...");
  while (mqtt.connect() != 0) {
    Serial.println("Falha ao conectar no MQTT. Tentando novamente em 5s...");
    delay(5000);
  }
  Serial.println("Conectado ao MQTT!");
}