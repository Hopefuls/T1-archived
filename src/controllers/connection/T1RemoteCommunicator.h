#include <string>
#include <Wire.h>
#include <vector>

using namespace std;

class T1RemoteCommunicator
{
public:
    /*
     * Singleton pattern, instance of the T1RemoteCommunicator that can be accessed from anywhere
     */
    static T1RemoteCommunicator &getInstance()
    {
        static T1RemoteCommunicator remote_communicator_instance;
        return remote_communicator_instance;
    }

    /*
     * Setter for the bluetooth name that shows up for the Remote Device
     */
    void setBtName(String btname)
    {
        this->btname = btname;
    }

    /*
     * Setter for the bluetooth baudrate, this should be the same as the baudrate of the bluetooth module
     */
    void setBaudrate(int baudrate)
    {
        this->baudrate = baudrate;
    }
    String btname;
    int baudrate;
    void remote_communicator_connect();
    bool rc_is_connected = false;
    bool rc_bluetooth_is_setup = false;
    // create an array of callbacks
    // void registerCallback(void callback, std::string type);

private:
    T1RemoteCommunicator() {}
};
