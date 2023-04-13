#include <Arduino.h>

int HEADLIGHT_LEFT_PIN = 18;
int HEADLIGHT_RIGHT_PIN = 19;
int BRAKE_LIGHT_LEFT_PIN = 17;
int BRAKE_LIGHT_RIGHT_PIN = 16;

void setup() {
  pinMode(HEADLIGHT_LEFT_PIN, OUTPUT);
  pinMode(HEADLIGHT_RIGHT_PIN, OUTPUT);
  pinMode(BRAKE_LIGHT_LEFT_PIN, OUTPUT);
  pinMode(BRAKE_LIGHT_RIGHT_PIN, OUTPUT);
}

void loop() {
  digitalWrite(HEADLIGHT_LEFT_PIN, HIGH);
  digitalWrite(HEADLIGHT_RIGHT_PIN, HIGH);
  digitalWrite(BRAKE_LIGHT_LEFT_PIN, HIGH);
  digitalWrite(BRAKE_LIGHT_RIGHT_PIN, HIGH);
  delay(1000);
  digitalWrite(HEADLIGHT_LEFT_PIN, LOW);
  delay(500);
  digitalWrite(HEADLIGHT_RIGHT_PIN, LOW);
  delay(500);
}