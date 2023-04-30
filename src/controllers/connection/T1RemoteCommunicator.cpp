#include <string>
#include <vector>
#include <tuple>
#include "T1RemoteCommunicator.h"
#include "../driving/T1MotorController.h"
#include "../steering/T1SteeringController.h"
#include <Arduino.h>
#include <BluetoothSerial.h>

#define BT_TRANSFER_LED 32
#define BT_WAIT_LED 33

BluetoothSerial serialConnection;

using namespace std;

String RC_LOG_PREFIX = "[REMOTECOMMUNICATOR] ";

/*
 * handles the serial input
 * @param input: the input from the serial connection
 * @see handle_serial_parsing
 */
void handle_serial_input(String input)
{
    String CONTROLLER_LOG_PREFIX = "[CONTROLLER] ";

    if (input == "CONTROL_LED_ON")
    {
        Serial.println(CONTROLLER_LOG_PREFIX + "Turning LED on");
        return;
    }

    if (input == "CONTROL_LED_OFF")
    {
        Serial.println(CONTROLLER_LOG_PREFIX + "Turning LED off");
        return;
    }

    if (input == "MOTOR1_FORWARD")
    {
        T1MotorController::getInstance().motor_controller_drive(2);
        Serial.println(CONTROLLER_LOG_PREFIX + "Driving forward");
        return;
    }
    if (input == "MOTOR1_BACKWARD")
    {

        T1MotorController::getInstance().motor_controller_drive(2);
        Serial.println(CONTROLLER_LOG_PREFIX + "Driving backward");
        return;
    }

    if (input == "MOTOR1_STOP")
    {
        T1MotorController::getInstance().motor_controller_stop();
        Serial.println(CONTROLLER_LOG_PREFIX + "Stopping");
        return;
    }
    if (input == "STEER_LEFT")
    {
        Serial.println(CONTROLLER_LOG_PREFIX + "Steering left");
        T1SteeringController::getInstance().steering_controller_turn(1);
        return;
    }
    if (input == "STEER_RIGHT")
    {
        Serial.println(CONTROLLER_LOG_PREFIX + "Steering right");
        T1SteeringController::getInstance().steering_controller_turn(2);
        return;
    }
}

/*
 * handles the serial parsing received from the bluetooth connection
 * @see listen
 * @author Aurel Ballin
 */
void handle_serial_parsing()
{
    if (serialConnection.available())
    {
        Serial.println(RC_LOG_PREFIX + "Serial data available!");
        digitalWrite(BT_TRANSFER_LED, HIGH);
        // loop through each character, ensure it starts with < and ends with >
        // if it does, add it to the buffer
        // create a buffer variable
        String buffer = "";
        bool receiving = false;
        while (serialConnection.available())
        {
            char c = serialConnection.read();
            digitalWrite(BT_TRANSFER_LED, digitalRead(BT_TRANSFER_LED) == HIGH ? LOW : HIGH);
            if (c == '>')
            {
                receiving = false;
                Serial.println(RC_LOG_PREFIX + "Received: " + buffer);
                handle_serial_input(buffer);
                digitalWrite(BT_TRANSFER_LED, LOW);
            }
            if (receiving)
            {
                buffer += c;
            }
            if (c == '<')
            {
                receiving = true;
                buffer = "";
            }
        }
    }
}

/*
 * listens for incoming bluetooth connections, this is run in a separate task
 * @param pvParameters: the parameters for the task, not used
 */
void listen(void *pvParameters)
{
    for (;;)
    {
        if (!T1RemoteCommunicator::getInstance().rc_bluetooth_is_setup)
        {
            serialConnection.begin(T1RemoteCommunicator::getInstance().btname);

            T1RemoteCommunicator::getInstance().rc_bluetooth_is_setup = true;
            Serial.println(RC_LOG_PREFIX + "Bluetooth Serial is setup!");
            continue;
        }

        // if the connection is not established (rc_instance->rc_is_connected == false) then wait for incoming connection
        if (!T1RemoteCommunicator::getInstance().rc_is_connected)
        {
            Serial.println(RC_LOG_PREFIX + "Waiting for Bluetooth connection...");
            // check the BT_WAIT_LED state
            digitalWrite(BT_WAIT_LED, digitalRead(BT_WAIT_LED) == HIGH ? LOW : HIGH);

            // digitalWrite(BT_WAIT_LED, HIGH);
            // digitalWrite(BT_TRANSFER_LED, LOW);
            if (serialConnection.hasClient())
            {
                Serial.println(RC_LOG_PREFIX + "Client connected!");
                digitalWrite(BT_WAIT_LED, HIGH);

                T1RemoteCommunicator::getInstance().rc_is_connected = true;
            }
            else
            {
                // digitalWrite(BT_WAIT_LED, HIGH);
                // digitalWrite(BT_TRANSFER_LED, LOW);
            }
            vTaskDelay(1000);
            continue;
        }
        else
        {
            if (serialConnection.connected())
            {
                handle_serial_parsing();
            }
            else
            {
                Serial.println(RC_LOG_PREFIX + "Connection lost!");
                T1RemoteCommunicator::getInstance().rc_is_connected = false;
                continue;
            }
        }

        vTaskDelay(10);
    }
}

// https://www.tutorialspoint.com/esp32_for_iot/esp32_for_iot_setting_up_rtos_for_dual_core_and_multi_threaded_operation.htm
/*
 * connects to the bluetooth device and starts the listen task
 */
void T1RemoteCommunicator::remote_communicator_connect()
{
    TaskHandle_t xHandle = NULL;
    xTaskCreatePinnedToCore(listen, "listen", 10000, (void *)1, 1, &xHandle, 0);
}
