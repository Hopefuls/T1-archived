#include <Arduino.h>
#include <Servo.h>
#include "controllers/connection/RemoteCommunicator.h"
#include "BluetoothSerial.h"

#define BT_TRANSFER_LED 32
#define BT_WAIT_LED 33
#define HEADLIGHT_LEFT_PIN 19
#define HEADLIGHT_RIGHT_PIN 18
#define BACKLIGHT_LEFT_PIN 17
#define BACKLIGHT_RIGHT_PIN 16

Servo servo;
int pos = 0;

void setup()
{
    Serial.begin(9600);
    RemoteCommunicator *remoteCommunicator = new RemoteCommunicator("T1 BUS CONTROLLER", 9600);
    remoteCommunicator->connect();
    pinMode(BT_WAIT_LED, OUTPUT);
    pinMode(BT_TRANSFER_LED, OUTPUT);
    pinMode(HEADLIGHT_LEFT_PIN, OUTPUT);
    pinMode(HEADLIGHT_RIGHT_PIN, OUTPUT);
    pinMode(BACKLIGHT_LEFT_PIN, OUTPUT);
    pinMode(BACKLIGHT_RIGHT_PIN, OUTPUT);
}

void loop()
{
}