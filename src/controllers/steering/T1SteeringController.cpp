#include "T1SteeringController.h"
#include <Arduino.h>
#include <ESP32Servo.h>

/*
 * Setup the steering controller pins using the steering_pin variable
 */
void T1SteeringController::steering_controller_setup()
{
    pinMode(this->steering_pin, OUTPUT);
    this->servo.attach(this->steering_pin);
}

/*
 * Causes the steering to turn in a given direction
 * @param direction: 1 = right, 2 = left, 3 = center
 * Might be changed to enums in the future
 */
void T1SteeringController::steering_controller_turn(int direction)
{
    switch (direction)
    {
    case 1:
        this->servo.write(0);
        break;
    case 2:
        this->servo.write(60);
        break;
    case 3:
        this->servo.write(30);
        break;
    }
}

/*
 * Causes the steering to turn a given degree
 * @param degree: the degree to turn
 */

void T1SteeringController::steering_controller_turn_degree(int degree)
{
    this->servo.write(degree);
}

/*
 * Setter for the steering_pin variable
 * @param steering_pin the pin number
 * @return void
 */