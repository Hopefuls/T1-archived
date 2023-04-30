/**
 * Light controller for T1_Project using 74hc595 shift register
 * The headlights currently use one of the 8 pins each, the indicator lights are groupt in pairs
 * It is possible to use the 74hc595 in combination with a transistor switch cirsuit to toggle multiple headlight
 * LEDs with one pin.
 * Module can turn on/off headlights and indicators
 * @author Jan Wofleben
 * @version 0.1.0
 */

#include "T1LightController.h"
#include <Arduino.h>

// byte values for the different light states, for examble headlights on equals B11110000
byte states[] = {B00000000, B11110000, B00001000, B00000100, B11111000, B11110100, B11111100, B00001100};
using namespace std;
/**
 * @param input_pin: 74hc595 input pin
 * @param output_pin: 74hc595 outbut_pin
 * @param shift_pin: 74hc595 shift pin
 * @param light_state: to toggle the light state between on/off
 * @param indicator_toggle: to toggle the state of the indicators between on/off
 */

/**
 * Method to change the current light state
 * light_state==false : turns on lights
 * light_state==true : turns off lights
 */
void T1LightController::changeLightState()
{
    T1LightController &lc_instance = T1LightController::getInstance();
    if (T1LightController::getInstance().light_state)
    {
        digitalWrite(lc_instance.output_pin, 0);
        shiftOut(lc_instance.input_pin, lc_instance.shift_pin, MSBFIRST, states[0]);
        digitalWrite(lc_instance.output_pin, 1);
    }
    else
    {
        digitalWrite(lc_instance.output_pin, 0);
        shiftOut(lc_instance.input_pin, lc_instance.shift_pin, MSBFIRST, states[1]);
        digitalWrite(lc_instance.output_pin, 1);
    }
    lc_instance.light_state != lc_instance.light_state;
}

/**
 * Method to toggle the state of the left indicator depending on the state of indicator_toggle
 */
void T1LightController::indicatorLeft()
{
    T1LightController &lc_instance = T1LightController::getInstance();
    byte state_on = lc_instance.light_state ? states[4] : states[2];  // check if headlights are on and chose the correct byte value for left indicator state on
    byte state_off = lc_instance.light_state ? states[1] : states[0]; // check if headlights are on and chose the correct byte value for left indicator state off
    if (lc_instance.indicator_toggle)
    {
        digitalWrite(lc_instance.output_pin, 0);
        shiftOut(lc_instance.input_pin, lc_instance.shift_pin, MSBFIRST, state_off);
        digitalWrite(lc_instance.output_pin, 1);
    }
    else
    {
        digitalWrite(lc_instance.output_pin, 0);
        shiftOut(lc_instance.input_pin, lc_instance.shift_pin, MSBFIRST, state_on);
        digitalWrite(lc_instance.output_pin, 1);
    }
    lc_instance.indicator_toggle != lc_instance.indicator_toggle;
}

/**
 * Method to toggle the state of the right indicator depending on the state of indicator_toggle
 */
void T1LightController::indicatorRight()
{
    T1LightController &lc_instance = T1LightController::getInstance();
    byte state_on = lc_instance.light_state ? states[5] : states[3];  // check if headlights are on and chose the correct byte value for right indicator state on
    byte state_off = lc_instance.light_state ? states[1] : states[0]; // check if headlights are on and chose the correct byte value for right indicator state off
    if (lc_instance.indicator_toggle)
    {
        digitalWrite(lc_instance.output_pin, 0);
        shiftOut(lc_instance.input_pin, lc_instance.shift_pin, MSBFIRST, state_off);
        digitalWrite(lc_instance.output_pin, 1);
    }
    else
    {
        digitalWrite(lc_instance.output_pin, 0);
        shiftOut(lc_instance.input_pin, lc_instance.shift_pin, MSBFIRST, state_on);
        digitalWrite(lc_instance.output_pin, 1);
    }
    lc_instance.indicator_toggle != lc_instance.indicator_toggle;
}

/**
 * Method to turn on the flashing lights, maybe in case of a car accident ;)
 */
void T1LightController::flashingLight()
{
    T1LightController &lc_instance = T1LightController::getInstance();
    byte state_on = lc_instance.light_state ? states[6] : states[7];  // check if headlights are on and chose the correct byte value for warning indicator state on
    byte state_off = lc_instance.light_state ? states[1] : states[0]; // check if headlights are on and chose the correct byte value for warning indicator state off
    if (lc_instance.indicator_toggle)
    {
        digitalWrite(lc_instance.output_pin, 0);
        shiftOut(lc_instance.input_pin, lc_instance.shift_pin, MSBFIRST, state_off);
        digitalWrite(lc_instance.output_pin, 1);
    }
    else
    {
        digitalWrite(lc_instance.output_pin, 0);
        shiftOut(lc_instance.input_pin, lc_instance.shift_pin, MSBFIRST, state_on);
        digitalWrite(lc_instance.output_pin, 1);
    }
    lc_instance.indicator_toggle != lc_instance.indicator_toggle;
}