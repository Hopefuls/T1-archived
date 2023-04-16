class MotorController
{
public:
    MotorController(int motor_pin);
    void setup();
    int motor_pin;
    int get_motor_pin();
    void set_motor_pin(int motor_pin);
};