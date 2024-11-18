#include <LoRa.h>
#include <SPI.h>

// LORA ACCEPTED/SENT MESSAGES
const char* lora_turnoff = "0";
const char* lora_turnon = "1";
const char* lora_getstatus = "2";
const char* lora_rele_on = "on";
const char* lora_rele_off = "off";

//LORA PIN
#define NSS 4
#define RST 5
#define DI0 2

//RELE PIN
#define RELE_PIN 21

//LORA DEFs
// Change sync word (0xF1) to match the receiver LoRa
// This code ensure that you don't get LoRa messages
// from other LoRa transceivers
// ranges from 0-0xFF
#define LORA_SYNCWORD 0xF1
#define LORA_SF 12 // 7 is the fastest. 12 is is farthest
#define LORA_CR 5
#define LORA_BW 41.7E3 //31.25E3 // 41.7E3 //125E3
#define LORA_PREAMBLE_LENGTH  8

//RELE FIRST STATUS
int rele_status = LOW;

void init_lora();
void send_lora(const char* message);
void receive_lora();
void parse_lora(String lora_data);
