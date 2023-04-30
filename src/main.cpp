#include <Arduino.h>
#include "controllers/connection/T1RemoteCommunicator.h"
#include "BluetoothSerial.h"
#include "controllers/distancing/T1DistanceController.h"
#include "controllers/driving/T1MotorController.h"
#include "controllers/light/T1LightController.h"
#include "controllers/steering/T1SteeringController.h"

#define BT_TRANSFER_LED 32
#define BT_WAIT_LED 33
#define HEADLIGHT_LEFT_PIN 19
#define HEADLIGHT_RIGHT_PIN 18
#define BACKLIGHT_LEFT_PIN 17
#define BACKLIGHT_RIGHT_PIN 16

#define MOTOR1_PIN1 26
#define MOTOR1_PIN2 25

#define SCHALLSENSOR_TRIGGER_PIN 19
#define SCHALLSENSOR_ECHO_PIN 18

int pos = 0;

void setup()
{

    pinMode(BT_TRANSFER_LED, OUTPUT);
    pinMode(BT_WAIT_LED, OUTPUT);

    Serial.begin(9600);

    T1RemoteCommunicator &remote_communicator_instance = T1RemoteCommunicator::getInstance();
    remote_communicator_instance.setBtName("T1 BUS CONTROLLER");
    remote_communicator_instance.setBaudrate(9600);
    remote_communicator_instance.remote_communicator_connect();

    T1DistanceController &distance_controller_instance = T1DistanceController::getInstance();
    distance_controller_instance.setEchoPin(SCHALLSENSOR_ECHO_PIN);
    distance_controller_instance.setTrigPin(SCHALLSENSOR_TRIGGER_PIN);
    distance_controller_instance.setMaxDistance(100);
    distance_controller_instance.setMinDistance(0);
    distance_controller_instance.setTriggerRate(100);

    distance_controller_instance.distance_controller_setup();

    T1MotorController &motor_controller_instance = T1MotorController::getInstance();
    motor_controller_instance.setMotorPin1(MOTOR1_PIN1);
    motor_controller_instance.setMotorPin2(MOTOR1_PIN2);
    motor_controller_instance.motor_controller_setup();

    T1LightController &light_controller_instance = T1LightController::getInstance();

    T1SteeringController &steering_controller_instance = T1SteeringController::getInstance();
    steering_controller_instance.setSteeringPin(16);

    steering_controller_instance.steering_controller_setup();
    steering_controller_instance.steering_controller_turn_degree(90);
    // pinMode(BT_WAIT_LED, OUTPUT);
    // pinMode(BT_TRANSFER_LED, OUTPUT);
    // pinMode(HEADLIGHT_LEFT_PIN, OUTPUT);
    // pinMode(HEADLIGHT_RIGHT_PIN, OUTPUT);
    // pinMode(BACKLIGHT_LEFT_PIN, OUTPUT);
    // pinMode(BACKLIGHT_RIGHT_PIN, OUTPUT);
}

void loop()
{
    delay(1);
}