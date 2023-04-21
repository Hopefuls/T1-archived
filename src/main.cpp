#include <Arduino.h>
#include "controllers/connection/RemoteCommunicator.h"
#include "BluetoothSerial.h"

#define BT_TRANSFER_LED 32
#define BT_WAIT_LED 33
#define HEADLIGHT_LEFT_PIN 19
#define HEADLIGHT_RIGHT_PIN 18
#define BACKLIGHT_LEFT_PIN 17
#define BACKLIGHT_RIGHT_PIN 16

#define MOTOR1_PIN1 26
#define MOTOR1_PIN2 25

int pos = 0;

void setup()
{

    pinMode(13, OUTPUT);
    pinMode(MOTOR1_PIN1, OUTPUT);
    pinMode(MOTOR1_PIN2, OUTPUT);
    // Serial.begin(9600);
    RemoteCommunicator *remoteCommunicator = new RemoteCommunicator("T1 BUS CONTROLLER", 9600);
    remoteCommunicator->connect();
    // pinMode(BT_WAIT_LED, OUTPUT);
    // pinMode(BT_TRANSFER_LED, OUTPUT);
    // pinMode(HEADLIGHT_LEFT_PIN, OUTPUT);
    // pinMode(HEADLIGHT_RIGHT_PIN, OUTPUT);
    // pinMode(BACKLIGHT_LEFT_PIN, OUTPUT);
    // pinMode(BACKLIGHT_RIGHT_PIN, OUTPUT);
    // Move DC motor forward with increasing speed

}

void loop()
{
}