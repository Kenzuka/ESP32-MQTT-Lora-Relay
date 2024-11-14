#include <releESP.h>


// Setup function to initialize the system components
void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Setup: Started");

  // Initialize LoRa communication module
  init_lora();
  

  // Set up relay pin mode and initial status
  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, rele_status);
  
  Serial.println("Setup: Ended");
}

// Main loop to continuously check for incoming LoRa messages
void loop() {
  String read = read_lora();        // Read any incoming LoRa messages
  if (!read.isEmpty()) {            // If a message is received, process it
    parse_lora(read);               // Parse and handle the received LoRa message
  } 
}

// Function to parse and execute commands received over LoRa
void parse_lora(String lora_data){
  if(strcmp(lora_data.c_str(), lora_turnoff) == 0){   // Check if received data matches the command to turn off the relay, if yes set off the relay
      Serial.println("Lora parser: turn off");
      rele_status = LOW;
      digitalWrite(RELE_PIN, rele_status);
    } else if(strcmp(lora_data.c_str(), lora_turnon) == 0){ // Check if received data matches the command to turn off the relay, if yes set on the relay
      Serial.println("Lora parser: turn on");
      rele_status = HIGH;
      digitalWrite(RELE_PIN, rele_status);
    } else if(strcmp(lora_data.c_str(), lora_getstatus) == 0){   // Check if received data matches the command to get relay status, if yes send back the current status
      Serial.println("Lora parser: get status");
      if(rele_status == LOW){
        send_lora(lora_rele_off);
      }else if(rele_status == HIGH){
        send_lora(lora_rele_on);
      }
    }else {
      Serial.println("Lora parser: invalid data");  
    }
}
