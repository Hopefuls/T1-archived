#include <string>
#include <Wire.h>
#include <vector>

using namespace std;

class T1DistanceController
{
public:
    static T1DistanceController &getInstance()
    {
        static T1DistanceController distance_controller_instance;
        return distance_controller_instance;
    }

    void setEchoPin(int echo_pin)
    {
        this->echo_pin = echo_pin;
    }

    void setTrigPin(int trig_pin)
    {
        this->trig_pin = trig_pin;
    }

    void setMaxDistance(int max_distance)
    {
        this->max_distance = max_distance;
    }

    void setMinDistance(int min_distance)
    {
        this->min_distance = min_distance;
    }

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
    T1DistanceController() {}
};
