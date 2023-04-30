#include <string>
#include <Wire.h>
#include <vector>

using namespace std;

class T1RemoteCommunicator
{
public:
    static T1RemoteCommunicator &getInstance()
    {
        static T1RemoteCommunicator remote_communicator_instance;
        return remote_communicator_instance;
    }

    void setBtName(String btname)
    {
        this->btname = btname;
    }

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
