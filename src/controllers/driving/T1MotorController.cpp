#include "T1MotorController.h"
#include <Arduino.h>

/*
 * Setup the motor controller pins using the motor_pin1 and motor_pin2 variables
 */

using namespace std;

String MC_LOG_PREFIX = "[MOTORCONTROLLER] ";

void T1MotorController::motor_controller_setup()
{
    pinMode(this->motor_pin1, OUTPUT);
    pinMode(this->motor_pin2, OUTPUT);
}

/*
 * Causes the motor to stop
 */
void T1MotorController::motor_controller_stop()
{
    digitalWrite(this->motor_pin1, LOW);
    digitalWrite(this->motor_pin2, LOW);
}

/*
 * Causes the motor to drive in a given direction
 * @param direction: 1 = forward, 2 = backward
 * Might be changed to enums in the future
 */
void T1MotorController::motor_controller_drive(int direction)
{
    switch (direction)
    {
    case 1:
        digitalWrite(this->motor_pin1, HIGH);
        digitalWrite(this->motor_pin2, LOW);
        break;
    case 2:
        digitalWrite(this->motor_pin1, LOW);
        digitalWrite(this->motor_pin2, HIGH);
        break;
    }
}
