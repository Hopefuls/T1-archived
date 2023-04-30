class T1MotorController
{

public:
    static T1MotorController &getInstance()
    {
        static T1MotorController motor_controller_instance;
        return motor_controller_instance;
    }
    T1MotorController(int motor_pin1, int motor_pin2);
    void motor_controller_setup();
    int motor_pin1;
    int motor_pin2;
    void motor_controller_drive(int direction);
    void motor_controller_stop();

    void setMotorPin1(int motor_pin1)
    {
        this->motor_pin1 = motor_pin1;
    }

    void setMotorPin2(int motor_pin2)
    {
        this->motor_pin2 = motor_pin2;
    }

private:
    T1MotorController() {}
};
