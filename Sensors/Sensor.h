#ifndef VS19_SENSOR_H
#define VS19_SENSOR_H

#include<stdexcept>
#include<iostream>
#include<string>
#include<string.h>
#include<stdio.h>
#include<sstream>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdio.h>
#include<array>
#include<vector>
#include<algorithm>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<chrono>
#include<ctime>
#include<iomanip>

using namespace std;

struct Measurement{
    float val;
    string unit;
};

class Sensor {
public:
    const static size_t TIME_OUT = 20;
    const static size_t MAX_LENGTH = 1024;

    struct timeval timeout {
            Sensor::TIME_OUT, 0
    };

    Sensor() {
        srand(time(nullptr));
    };

    Sensor(const string& type, const float& label, const string& unit);
    virtual void gen_value(const float& upper_bound);
    virtual Measurement getMeasurement()const {
        return m_measurement;
    }
	virtual void setServerPort(const size_t& port) { m_server_port = port; } 
    virtual void sendData(char** argv);
    virtual void formatAllSensorData();
    virtual sockaddr_in createUDPSocket(const unsigned int& port);
    virtual bool receivedDataFromServer(const sockaddr_in& server_addr);
    virtual string toString() const;
    virtual string getType(){
        return m_type;
    }
    virtual ~Sensor();
private:
    string m_type = "Sensor";
    string m_ip;
    Measurement m_measurement;
    int m_socket;
    int m_result;
    char m_buf[MAX_LENGTH];
    size_t m_client_port;
	size_t m_server_port;
};

#endif //VS19_SENSOR_H
