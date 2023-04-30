/**
 * Light controller for T1-Project
 * @author Jan Wofleben
 * @version 0.1.0
 */

class T1LightController
{

public:
    static T1LightController &getInstance()
    {
        static T1LightController light_controller_instance;
        return light_controller_instance;
    }
    void changeLightState();
    void indicatorLeft();
    void indicatorRight();
    void flashingLight();
    int input_pin;
    int output_pin;
    int shift_pin;
    bool light_state = false;
    bool indicator_toggle = false;
    void setInputPin(int input_pin)
    {
        this->input_pin = input_pin;
    };
    void setOutputPin(int output_pin)
    {
        this->output_pin = output_pin;
    };
    void setShiftPin(int shift_pin)
    {
        this->shift_pin = shift_pin;
    };
};