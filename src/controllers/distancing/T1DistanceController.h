#include <string>
#include <Wire.h>
#include <vector>

using namespace std;

/*
 * This class is responsible for handling everything around the HC-SR04 Schallsensor attached to the T1 Bus
 * It is a singleton, so it can be accessed from anywhere
 */
class T1DistanceController
{
public:
    /*
     * Singleton pattern, instance of the T1DistanceController that can be accessed from anywhere
     * @return T1DistanceController instance
     */
    static T1DistanceController &getInstance()
    {
        static T1DistanceController distance_controller_instance;
        return distance_controller_instance;
    }

    /*
     * Setter for the Echo pin on the HC-SR04
     * @param echo_pin the pin number
     * @return void
     */
    void setEchoPin(int echo_pin)
    {
        this->echo_pin = echo_pin;
    }

    /*
     * Setter for the Trig pin on the HC-SR04
     * @param trig_pin the pin number
     * @return void
     */
    void setTrigPin(int trig_pin)
    {
        this->trig_pin = trig_pin;
    }

    /*
     * Setter for the max distance the HC-SR04 can measure
     * This is used to determine if the measured distance is valid, if the distance is larger than max_distance, the corresponding callback will not be called
     * @see on_measured_distance()
     * @param max_distance the max distance in cm
     * @return void
     */
    void setMaxDistance(int max_distance)
    {
        this->max_distance = max_distance;
    }
    /*
     * Setter for the min distance the HC-SR04 can measure
     * This is used to determine if the measured distance is valid, if the distance is smaller than min_distance, the corresponding callback will not be called
     * @see on_measured_distance()
     * @param min_distance the min distance in cm
     * @return void
     */
    void setMinDistance(int min_distance)
    {
        this->min_distance = min_distance;
    }

    /*
     * Setter for the trigger rate of the HC-SR04
     * This is used to determine how often the distance should be measured in ms
     * E.g. if trigger_rate is 1000, the distance will be measured every second
     *
     * @note Keep in mind that this is affected by how long the HC-SR04 takes to measure a distance and only
     * triggers said delay after the measurement is done
     * @param trigger_rate the trigger rate in ms
     * @return void
     */
    void setTriggerRate(int trigger_rate)
    {
        this->trigger_rate = trigger_rate;
    }
    int echo_pin;
    int trig_pin;
    int max_distance;
    int min_distance;
    int trigger_rate;
    void distance_controller_setup();
    void measure_distance_loop();
    void on_measured_distance(int distance_in_cm);

private:
    /*
     * Constructor for the T1DistanceController
     */
    T1DistanceController() {}
};
