#include "T1MotorController.h"
#include <Arduino.h>

void T1MotorController::motor_controller_setup()
{
    pinMode(motor_pin1, OUTPUT);
    pinMode(motor_pin2, OUTPUT);
}

void T1MotorController::motor_controller_stop()
{
    digitalWrite(motor_pin1, LOW);
    digitalWrite(motor_pin2, LOW);
}

void T1MotorController::motor_controller_drive(int direction)
{
    switch (direction)
    {
    case 1:
        digitalWrite(motor_pin1, HIGH);
        digitalWrite(motor_pin2, LOW);
        break;
    case 2:
        digitalWrite(motor_pin1, LOW);
        digitalWrite(motor_pin2, HIGH);
        break;
    }
}
