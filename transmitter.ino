#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int servoPos = 0;

RF24 radio(7, 8);

const byte address[5] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
}

void loop() {
  delay(1000); // Add a delay to avoid flooding the radio
  Serial.println("Enter servo position (0-180): ");
  while (Serial.available() == 0) {
    // Wait for user input
  }
  servoPos = Serial.parseInt();
  Serial.print("Sending servo position: ");
  Serial.println(servoPos);
  radio.write(&servoPos, sizeof(servoPos));
}
