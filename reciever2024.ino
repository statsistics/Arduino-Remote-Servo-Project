#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8);

const byte address[5] = "00001";  // Address length should be 5 bytes

int servoPin = 9;

Servo paul;

void setup() {
  Serial.begin(9600);
  paul.attach(servoPin);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening(); // Start listening once in the setup
}

void loop() {
  if (radio.available()) {
    int angleV = 0;
    radio.read(&angleV, sizeof(angleV));

    // Constrain servo movement within 0-180 degrees
    angleV = constrain(angleV, 0, 180);

    paul.write(angleV);
    Serial.print("Received servo position: ");
    Serial.println(angleV);
  }
}
