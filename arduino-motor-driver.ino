#include <VirtualWire.h> // include the VirtualWire library

#define MOTOR1_PIN 9     // define the pin for the left motor
#define MOTOR2_PIN 10    // define the pin for the right motor
#define RX_PIN 11        // define the pin for the receiver
#define TX_PIN 12        // define the pin for the transmitter
#define TX_SPEED 2000    // define the transmitter speed in bits per second

int motor1Speed = 0;     // initialize the left motor speed to 0
int motor2Speed = 0;     // initialize the right motor speed to 0

void setup() {
  pinMode(MOTOR1_PIN, OUTPUT);     // set the left motor pin to output mode
  pinMode(MOTOR2_PIN, OUTPUT);     // set the right motor pin to output mode
  vw_set_rx_pin(RX_PIN);           // set the receiver pin
  vw_setup(TX_SPEED);              // set the transmitter speed
  vw_rx_start();                   // start the receiver
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];      // create a buffer to hold the received message
  uint8_t buflen = VW_MAX_MESSAGE_LEN;  // set the maximum buffer length
  if (vw_get_message(buf, &buflen)) {   // if a message is received
    int leftSpeed = map(buf[0], 0, 255, 0, 255);    // map the first byte of the message to a speed value between 0 and 255 for the left motor
    int rightSpeed = map(buf[1], 0, 255, 0, 255);   // map the second byte of the message to a speed value between 0 and 255 for the right motor
    
    analogWrite(MOTOR1_PIN, leftSpeed);   // set the left motor speed
    analogWrite(MOTOR2_PIN, rightSpeed);  // set the right motor speed
  }
}
