
/*
 * This class is used to control the motor
 * This class controls the input and output from/to the SBC-MotorDriver2
 * The motor controller is a singleton class and can be accessed from anywhere
 */
class T1MotorController
{

public:
    /*
     * Singleton pattern, instance of the T1MotorController that can be accessed from anywhere
     * @return T1MotorController instance
     */
    static T1MotorController &getInstance()
    {
        static T1MotorController motor_controller_instance;
        return motor_controller_instance;
    }

    /*
     * Setup the motor controller pins
     */
    void motor_controller_setup();

    /*
     * The pin number for the motor1 pin
     */
    int motor_pin1;

    /*
     * The pin number for the motor2 pin
     */
    int motor_pin2;

    /*
     * Causes the motor to drive in a given direction
     * @param direction: 1 = forward, 2 = backward
     * Might be changed to enums in the future
     */
    void motor_controller_drive(int direction);
    void motor_controller_stop();

    /*
     * Setter for the motor_pin1 variable
     * @param motor_pin1 the pin number
     * @return void
     */
    void setMotorPin1(int motor_pin1)
    {
        this->motor_pin1 = motor_pin1;
    }

    /*
     * Setter for the motor_pin2 variable
     * @param motor_pin2 the pin number
     * @return void
     */
    void setMotorPin2(int motor_pin2)
    {
        this->motor_pin2 = motor_pin2;
    }

private:
    /*
     * Private constructor for the singleton pattern
     */
    T1MotorController() {}
};
