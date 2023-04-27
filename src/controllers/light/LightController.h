/**
 * Light controller for T1-Project
 * @author Jan Wofleben
 * @version 0.1.0
 */


class LightController
{   
    
    public:
        LightController(int input_pin, int output_pin, int shit_pin);
        void changeLightState();
        void indicatorLeft();
        void indicatorRight();
        void flashingLight();
        int input_pin; 
        int output_pin;
        int shift_pin;
        bool light_state;
        bool indicator_toggle;
};