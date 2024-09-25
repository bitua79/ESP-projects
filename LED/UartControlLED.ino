
//turn on/off led with uart(serial)

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);  // Set the baud rate to match the external device
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();  // Read the incoming data
    
    if (command == '1') {
      digitalWrite(LED_BUILTIN, HIGH);  // Turn on the LED
      Serial.println("LED is ON");
    } else if (command == '0') {
      digitalWrite(LED_BUILTIN, LOW);   // Turn off the LED
      Serial.println("LED is OFF");
    }
  }
}
