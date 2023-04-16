#include "MotorController.h"
#include <Arduino.h>

MotorController::MotorController(int motor_pin)
{
    this->motor_pin = motor_pin;
}

void MotorController::setup()
{
    pinMode(this->motor_pin, OUTPUT);
}
