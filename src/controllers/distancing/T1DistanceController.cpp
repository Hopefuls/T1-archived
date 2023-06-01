#include "T1DistanceController.h"
#include <Arduino.h>

using namespace std;

String DC_LOG_PREFIX = "[DISTANCECONTROLLER] ";

/*
 * Function that gets called when measured distance is larger than the minimum distance and smaller than the maximum distance
 * Use this as an entrypoint to make actions towards the schallsensor if a certain distance is met (e.g. drive backwards)
 */
/*if  (T1DistanceController &distance_controller_instance = T1DistanceController::getInstance()){ */
void T1DistanceController::on_measured_distance(int distance_in_cm)
{


}

/*
 * Loop function responsible for keeping track of the distance, runs repeatedly every trigger_rate / portTICK_PERIOD_MS
 * @author Aurel Ballin
 */
void T1DistanceController::measure_distance_loop()
{
    digitalWrite(this->trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trig_pin, LOW);
    long duration = pulseIn(this->echo_pin, HIGH);
    long distance_in_cm = duration * 0.034 / 2;
    if (distance_in_cm >= this->min_distance && distance_in_cm <= this->max_distance)
    {
        this->on_measured_distance(distance_in_cm);
    }
}

/*
 * Loop task responsible for executing the measure_distance_loop function repeatedly
 * @param pvParameters: void pointer to the parameters passed to the task, can be ignored
 * @author Aurel Ballin
 */
void measure_distance_loop_task(void *pvParameters)
{
    for (;;)
    {
        T1DistanceController::getInstance().measure_distance_loop();
        vTaskDelay(T1DistanceController::getInstance().trigger_rate / portTICK_PERIOD_MS);
    }
}

/*
 * Setup function for the distance controller, sets up the pins and starts the measure_distance_loop_task from xTaskCreatePinnedToCore
 * @author Aurel Ballin
 */
void T1DistanceController::distance_controller_setup()
{
    pinMode(this->echo_pin, INPUT);
    pinMode(this->trig_pin, OUTPUT);
    TaskHandle_t xHandle = NULL;
    Serial.println(DC_LOG_PREFIX + "Starting distance controller");
    // create a task, pass the reference to the task handle
    xTaskCreatePinnedToCore(
        measure_distance_loop_task,   /* Function to implement the task */
        "measure_distance_loop_task", /* Name of the task */
        10000,                        /* Stack size in words */
        NULL,                         /* Task input parameter */
        0,                            /* Priority of the task */
        &xHandle,                     /* Task handle. */
        1);                           /* Core where the task should run */
}
