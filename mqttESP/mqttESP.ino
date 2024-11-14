#include <mqttESP.h>

// Setup function to initialize the system components
void setup() {
  Serial.begin(115200);
  delay(2000);  // Short delay to stabilize serial connection
  Serial.println("Setup: Started");
  
  // Connect to WiFi
  reconnect_wifi();

  // Connect to MQTT Broker
  reconnect_mqtt();

  // Initialize LORA
  init_lora();
  
  Serial.println("Setup: Ended");
}


// Main loop function that continuously checks for LoRa messages and connection statuses
void loop() {
  String read = read_lora();       // Read incoming LoRa messages
  if (!read.isEmpty()) {           // If a message is received, process it
    parse_lora(read);              // Parse the received LoRa message
  }   
  
  // Check Wi-Fi connection and reconnect if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    reconnect_wifi();
  }

  // Check MQTT connection and reconnect if disconnected
  if (!client.connected()) {
    reconnect_mqtt();
  }

  // Keep the MQTT connection alive
  client.loop();
}


// Function to connect to WiFi with automatic reconnection attempts
void reconnect_wifi() {
  Serial.println("Wifi Init: Started");

  // Exit function if already connected to WiFi
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  Serial.println("Wifi Init: Connecting ");
  WiFi.begin(ssid, password); // Start WiFi connection using SSID and password

  // Attempt to connect for a limited time (e.g., 10 seconds)
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500); // Wait 500 ms before each connection attempt
    Serial.print(".");
  }
  Serial.println("");
  
  // Check if the connection was successful
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wifi Init: Ended");
    Serial.print("Wifi IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Wifi Init: Failed");
  }

  Serial.println("Wifi Init: Ended");
}

// Function to reconnect to MQTT server with automatic reconnection attempts
void reconnect_mqtt() {
  Serial.println("MQTT Init: Started");

  // Set up MQTT server and callback function
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  Serial.println("MQTT Init: Connecting ");
  while (!client.connected()) {
  Serial.println("MQTT Init: Attempting connection ");
    
    // Attempt to connect with an MQTT client ID
    if (client.connect(mqtt_name, mqtt_username, mqtt_password)) {
      Serial.println("MQTT Init: Connected ");
      
      // Subscribe to topics after connecting
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("MQTT Init: failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds...");
      
      // Wait before retrying
      delay(5000);
    }
  }

  Serial.println("MQTT Init: Ended");
}

// Callback function to handle incoming MQTT messages
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("MQTT CALLBACK: topic-> ");
  Serial.print(topic);
  Serial.print(" message-> ");
  
  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)message[i]; // Convert byte array to String
  }
  Serial.println(msg);
  parse_mqtt(msg.c_str()); // Parse the received message
}

// Function to parse MQTT messages and send appropriate LoRa commands
void parse_mqtt(const char* message){
    if(strcmp(message, mqtt_on) == 0){
        send_lora(lora_turnon); // Send LoRa command to turn on device
    } else if(strcmp(message, mqtt_off) == 0){
        send_lora(lora_turnoff); // Send LoRa command to turn off device
    } else if(strcmp(message, mqtt_check) == 0){
        send_lora(lora_getstatus); // Send LoRa command to turn off device
    }
}

// Function to parse received LoRa data
void parse_lora(String lora_data){
  // TODO: Implement parsing logic for LoRa data based on application requirements
}
