#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>

// Pin Definitions
const int gsrPin = A0;    
const int chipSelect = 4; 
const int rxPin = 2;      
const int txPin = 3;      

// Variables
int gsrValue = 0;
File dataFile;

SoftwareSerial bluetooth(rxPin, txPin);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600); 
  Serial.println("Bluetooth started");

  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed!");
    return;
  }
  Serial.println("SD Card initialized.");

  dataFile = SD.open("gsrdata.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Timestamp (ms),GSR Value");
    dataFile.flush();
  } else {
    Serial.println("Error opening file!");
  }
}

void loop() {
  gsrValue = analogRead(gsrPin);
  Serial.print("GSR Value: ");
  Serial.println(gsrValue);

  // Bluetooth debug
  Serial.println("Sending GSR value over Bluetooth...");
  bluetooth.print("GSR Value: ");
  bluetooth.println(gsrValue);

  if (dataFile) {
    dataFile.print(millis());
    dataFile.print(",");
    dataFile.println(gsrValue);
    dataFile.flush();
  } else {
    Serial.println("Error writing to file!");
  }

  delay(1000);
}

void closeFile() {
  if (dataFile) {
    dataFile.close();
    Serial.println("Data saved and file closed.");
  }
}
