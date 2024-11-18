// Function to read data received over LoRa
String read_lora(){
  // Determine if a LoRa data packet has been received
  int lora_packet_size = LoRa.parsePacket();
  String lora_data;
  // If a packet has been received, process it, lora_packet_size > 0
  if (lora_packet_size) {
    // received a packet
    Serial.print("Lora Receiver: message->");
  
    // Read the entire data packet from LoRa
    while (LoRa.available()) {
      lora_data = LoRa.readString(); // Store received data in lora_data
    }
    Serial.println(lora_data);

    int rssi = LoRa.packetRssi();           // Signal strength (RSSI) of received packet
    float snr = LoRa.packetSnr();            // Signal-to-noise ratio (SNR) of received packet
    long freqErr = LoRa.packetFrequencyError();  // Frequency error of received packet
    
    // Display RSSI, SNR, and frequency error for debugging
    Serial.print("Lora Receiver: rssi:");
    Serial.print(rssi);
    Serial.print(" snr:");
    Serial.print(snr);
    Serial.print(" freqErr:");
    Serial.println(freqErr);
    // Return the received data
    return lora_data;
  }
  
  // Return an empty string if no data was received
  return String();
}

// Function to initialize LoRa module settings and configuration
void init_lora(){
  Serial.println("LoRa Init: Started");

  // Connect to LoRA
  LoRa.setPins(NSS, RST, DI0);

  //IMPORTANT CHECK FREQUENCIES ALLOWED: Replace 433E6 with the frequency allowed in your region
  while (!LoRa.begin(433E6)) { 
    Serial.println("LoRa Init: Starting LoRa failed!");
    delay(1000);
  }
  // Configure additional LoRa settings for optimal transmission
  LoRa.setSyncWord(LORA_SYNCWORD);         // Set unique sync word for network identification
  LoRa.setSpreadingFactor(LORA_SF);        // Set spreading factor for communication range/speed
  LoRa.setCodingRate4(LORA_CR);            // Set coding rate for error correction
  LoRa.setSignalBandwidth(LORA_BW);        // Set bandwidth of LoRa signal
  LoRa.setPreambleLength(LORA_PREAMBLE_LENGTH);  // Set preamble length for packet synchronization
  LoRa.enableCrc();       

  Serial.println("LoRa Init: Ended");
}



// Function to send data over LoRa network
void send_lora(const char* message){
  Serial.println("Lora Send: prepare to send a message");

  Serial.print("Lora Send: message->");
  Serial.print(message);
  Serial.println("");
  
  // Begin the LoRa packet, add the message, and transmit it
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket(true);
  
  Serial.println("Lora Send: message send");
}
