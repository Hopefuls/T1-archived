#include "RemoteCommunicator.h"

#include <Arduino.h>
#include <string>
#include <vector>
#include <tuple>
#include "BluetoothSerial.h"

#define BT_TRANSFER_LED 32
#define BT_WAIT_LED 33
#define HEADLIGHT_LEFT_PIN 19
#define HEADLIGHT_RIGHT_PIN 18
#define BACKLIGHT_LEFT_PIN 17
#define BACKLIGHT_RIGHT_PIN 16
#define MOTOR1_PIN1 26
#define MOTOR1_PIN2 25

BluetoothSerial serialConnection;
bool isConnectionEstablished = false;

RemoteCommunicator *instance;
using namespace std;
RemoteCommunicator::RemoteCommunicator(String btname, int baudrate)
{
    this->btname = btname;
    this->baudrate = baudrate;
    instance = this;
}

void reconnect(void *pvParameters)
{
    configASSERT(((uint32_t)pvParameters) == 1);

    for (;;)
    {
        if (!isConnectionEstablished)
        {
            instance->connect();
        }
    }
}

void listen(void *pvParameters)
{
    configASSERT(((uint32_t)pvParameters) == 1);

    for (;;)
    {
        if (isConnectionEstablished)
        {
            // check if connection is still alive
            if (!serialConnection.connected())
            {
                isConnectionEstablished = false;
                Serial.println("Connection lost");
                analogWrite(BT_TRANSFER_LED, 0);
            }

            bool receiving = false;
            String data = "";
            String start_indicator = "<";
            String end_indicator = ">";
            while (serialConnection.available() > 0)
            {
                if (!receiving)
                {
                    char c = serialConnection.read();
                    if (c == start_indicator[0])
                    {
                        receiving = true;
                        analogWrite(BT_TRANSFER_LED, 255);
                    }
                }

                if (receiving)
                {
                    char c = serialConnection.read();
                    if (c == end_indicator[0])
                    {
                        receiving = false;
                        Serial.println("Received: " + data);
                        analogWrite(BT_TRANSFER_LED, 0);
                        if (data == "CONTROL_LED_ON") {
                            digitalWrite(HEADLIGHT_LEFT_PIN, HIGH);
                            digitalWrite(HEADLIGHT_RIGHT_PIN, HIGH);
                            digitalWrite(BACKLIGHT_LEFT_PIN, HIGH);
                            digitalWrite(BACKLIGHT_RIGHT_PIN, HIGH);
                        } else if (data == "CONTROL_LED_OFF") {
                            digitalWrite(HEADLIGHT_LEFT_PIN, LOW);
                            digitalWrite(HEADLIGHT_RIGHT_PIN, LOW);
                            digitalWrite(BACKLIGHT_LEFT_PIN, LOW);
                            digitalWrite(BACKLIGHT_RIGHT_PIN, LOW);
                        } else if (data == "MOTOR1_FORWARD") {
                            digitalWrite(MOTOR1_PIN1, HIGH);
                            digitalWrite(MOTOR1_PIN2, LOW);
                        } else if (data == "MOTOR1_BACKWARD") {
                            digitalWrite(MOTOR1_PIN1, LOW);
                            digitalWrite(MOTOR1_PIN2, HIGH);
                        } else if (data == "MOTOR1_STOP") {
                            digitalWrite(MOTOR1_PIN1, LOW);
                            digitalWrite(MOTOR1_PIN2, LOW);
                        } // check if data starts with "INPUT_"
                    }
                    else
                    {
                        data += c;
                    }
                }
            }
        }
        else
        {
            serialConnection.begin(instance->btname);
            Serial.println("BT CONNECTON started");
            while (!serialConnection.connected())
            {
                Serial.println("Waiting for connection");
                analogWrite(BT_WAIT_LED, 255);
                delay(300);
                analogWrite(BT_WAIT_LED, 0);
                delay(300);
            } // Wait for connection
            Serial.println("Connected");
            analogWrite(BT_WAIT_LED, 50);

            isConnectionEstablished = true;
        }
    }
}

void RemoteCommunicator::connect()
{
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;
    xReturned = xTaskCreate(
        listen,           /* Function that implements the task. */
        "Listener",       /* Text name for the task. */
        10000,            /* Stack size in words, not bytes. */
        (void *)1,        /* Parameter passed into the task. */
        tskIDLE_PRIORITY, /* Priority at which the task is created. */
        NULL);            /* Used to pass out the created task's handle. */
}
