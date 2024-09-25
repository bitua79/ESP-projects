#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         14           // Configurable, see typical pin layout above
#define SS_PIN          5          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;
byte bufferSize = 18;

bool tryAgain = false;

/**
 * Initialize.
 */
void setup() {
    Serial.begin(9600); // Initialize serial communications with the PC
    while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card

    // Prepare the key (used both as key A and as key B)
    // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

    Serial.println("RFID Prepared. Enter Your Command: ");
}

/**
 * Main loop.
 */

void loop() {

    // Check Condition validity
    if ( ! mfrc522.PICC_IsNewCardPresent())
      return;
    

    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    // Wait for command
    if (Serial.available() > 0){
      // Read command from serial
      String command = Serial.readStringUntil('\n');
      command.trim();
      Serial.println(command);

      if (command.startsWith("read")) {
        handleReadCommand(command);

      } else if (command.startsWith("write")) {
        handleWriteCommand(command);

      } else {
        Serial.println("Invalid Command!");
        tryAgain = true;
        return;
      }

      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1();

      if(tryAgain){
        Serial.println("\nWrite your new command: ");
        tryAgain = false;
      }
    }
}


// Check if block number input is in the valid range
bool checkBlockAddressValidity(int blockAddr){
  return (blockAddr > 0 && blockAddr < 64 && blockAddr % 4 != 3);
}

void handleReadCommand(String command){
    String block = command.substring(5);
    int blockAddr = (int) block.toInt();

    if (!checkBlockAddressValidity(blockAddr)){
      Serial.println("Invalid Block Address!");
      tryAgain = true;
      return;
    }
    byte readData[18];
    readBlock(blockAddr, readData);
    tryAgain = true;
}


void readBlock(int blockAddr, byte readData[]){
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockAddr, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK){
    Serial.println("Authentication was Failed for Read!");
    tryAgain = true;
    return;
  }
  else{
    Serial.println("Authentication for Read was successful.");
  }

  Serial.println("Reading Block...");
  status = mfrc522.MIFARE_Read(blockAddr, readData, &bufferSize);
  if (status != MFRC522::STATUS_OK){
    Serial.println("Reading failed!");
    tryAgain = true;
    return;
  } 
  Serial.println("Reading was successful.");  
  for (int j=0 ; j<16 ; j++){
    Serial.write(readData[j]);
  }
  Serial.println();
}


void handleWriteCommand(String command){
    String block = command.substring(6);
    int blockAddr = (int) block.toInt();

    // Extract value which we eant to write in block
    String value = command.substring(String(blockAddr).length());
    value.trim();

    if (value.length() > bufferSize) {
      value = value.substring(0, bufferSize);
    }

    if (!checkBlockAddressValidity(blockAddr)){
      Serial.println("Invalid Block Address!");
      tryAgain = true;
      return;
    }

    byte buffr[16] = {0};
    char inputChars[16];
    value.toCharArray(inputChars, 16);

    for (int i =0 ; i < 16 && i < value.length(); i++) {
      buffr[i] = (byte)inputChars[i];
    }

    writeBlock(blockAddr, buffr);
}

void writeBlock(int blockAddr, byte blockData[]){\
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockAddr, &key, &(mfrc522.uid));

    if (status != MFRC522::STATUS_OK){
      Serial.println("Authentication was Failed for Write!");
      tryAgain = true;
      return;
    }
    else{
      Serial.println("Authentication for Write was successful.");
    }
    
    Serial.println("Writing Block...");
    status = mfrc522.MIFARE_Write(blockAddr, blockData, 16);
    if (status != MFRC522::STATUS_OK){
      Serial.println("Writing failed!");
      tryAgain = true;
      return;
    }  
    Serial.println("Writing was successful.");  

}
