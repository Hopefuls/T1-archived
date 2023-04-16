#include <string>
#include <Wire.h>
#include <vector>

using namespace std;
class RemoteCommunicator
{
public:
    RemoteCommunicator(String btname, int baudrate);
    String btname;
    int baudrate;
    void connect();
    // create an array of callbacks
    // void registerCallback(void callback, std::string type);
};
