#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <LoRa.h>


// WiFi and MQTT Server Configuration
const char* ssid     = "SSID";
const char* password = "PASSWORD";
const char* mqtt_server = "MQTTSERVER_IP";
const int mqtt_port = 1883;
const char* mqtt_username = "MQTTSERVER_USERNAME";
const char* mqtt_password = "MQTTSERVER_PASSWORD";
const char* mqtt_name = "Thermostat_Sender1";
const char* mqtt_topic = "thermostat/cmd";


const char* mqtt_off = "off";
const char* mqtt_on = "on";
const char* mqtt_check = "check";

const char* lora_turnoff = "0";
const char* lora_turnon = "1";
const char* lora_getstatus = "2";

//LoRa PIN
#define NSS 5
#define RST 14
#define DI0 2

// Change sync word (0xF1) to match the receiver LoRa
// This code ensure that you don't get LoRa messages
// from other LoRa transceivers
// ranges from 0-0xFF
#define LORA_SYNCWORD 0xF1
#define LORA_SF 12 // 7 is the fastest. 12 is is farthest
#define LORA_CR 5
#define LORA_BW 41.7E3 //31.25E3 // 41.7E3 //125E3
#define LORA_PREAMBLE_LENGTH  8

//RELE PIN
#define RELE_PIN 21




// MQTT Client and WiFi Client
WiFiClient espClient;
PubSubClient client(espClient);

// Function Prototypes
void init_lora();
void send_lora(const char* message);
void receive_lora();
void parse_lora(String lora_data);
void reconnect_wifi();
void reconnect_mqtt();
void callback(char* topic, byte* message, unsigned int length);
void parse_mqtt(const char* message);
