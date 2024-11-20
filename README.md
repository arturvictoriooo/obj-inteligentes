# Monitoramento de Monóxido de Carbono com NodeMCU e MQTT

## Descrição do Projeto

Este projeto utiliza um NodeMCU ESP8266 como controlador principal para monitorar os níveis de monóxido de carbono (CO) no ambiente. O sensor MQ-7 é responsável por medir os níveis do gás, enquanto um buzzer passivo alerta os usuários quando o nível detectado ultrapassa um limite predefinido. Os dados são enviados para a internet através do protocolo MQTT, utilizando o Adafruit IO como plataforma de visualização.

Ideal para aplicações domésticas e industriais, o sistema permite monitoramento remoto e fornece alertas locais e em tempo real sobre a qualidade do ar.


## Software Desenvolvido e Documentação de Código

O software foi desenvolvido utilizando a IDE do Arduino e pode ser encontrado no arquivo monitoramento_co.ino. O código está dividido em três partes principais:
	1. Conexão Wi-Fi: Configuração do acesso à internet.
	2. Leitura do Sensor e Controle do Buzzer: Interpretação dos dados analógicos do sensor e alerta sonoro.
	3. Envio de Dados via MQTT: Comunicação com o Adafruit IO para visualização remota.

Estrutura do Código

	• setup(): Configura os pinos, inicializa o monitor serial, conecta ao Wi-Fi e ao broker MQTT.
	• loop(): Lê o sensor, controla o buzzer e envia os dados ao Adafruit IO.
	• Funções auxiliares:
	• connectWiFi(): Conecta à rede Wi-Fi.
	• connectMQTT(): Garante a conexão estável com o broker MQTT.

	Observação: O código contém comentários detalhados para facilitar a reprodução.

## Hardware Utilizado

Plataformas de Desenvolvimento

	•	NodeMCU ESP8266 (ESP-12): Controlador principal e módulo de comunicação Wi-Fi.

Sensores

	•	MQ-7: Sensor para detecção de monóxido de carbono.
	•	Tensão operacional: 5V
	•	Saída: Analógica

Atuadores

	•	Buzzer Passivo (3 pinos):
	•	Tensão operacional: 3.3V
	•	Som de 1 kHz para alertas.

Outros Componentes

	•	Protoboard, jumpers e fonte de alimentação USB.

Impressão 3D (Opcional):
Para encapsulamento, uma caixa com medidas de 100x80x40mm pode ser impressa, com aberturas para ventilação do sensor MQ-7. Arquivos .stl estão disponíveis no repositório.

## Interfaces, Protocolos e Módulos de Comunicação

	1. Interface de Comunicação com o Sensor
	  	• Comunicação analógica através do pino A0 do NodeMCU.
   
	2. Protocolo MQTT
	  	• Broker: Adafruit IO
	  	• Porta: 1883
	  	• Tópico: usuario/feeds/nome-feed
	  	• Dados enviados: Valor analógico detectado pelo MQ-7.
   
	3. Protocolo TCP/IP
  		• Comunicação entre o NodeMCU e o broker MQTT utiliza o protocolo TCP/IP para envio de mensagens.
   
	4. Conexão Wi-Fi
	  	• SSID e senha configuráveis diretamente no código.
