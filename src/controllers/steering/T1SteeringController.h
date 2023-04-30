#include <Arduino.h>
#include <ESP32Servo.h>

class T1SteeringController
{
public:
    static T1SteeringController &getInstance()
    {
        static T1SteeringController steering_controller_instance;
        return steering_controller_instance;
    }
    void setSteeringPin(int steering_pin)
    {
        this->steering_pin = steering_pin;
    }
    void steering_controller_setup();
    void steering_controller_turn(int direction);
    void steering_controller_turn_degree(int degree);

private:
    int steering_pin;
    Servo servo;
    T1SteeringController() {}
};