#include"Sensor.h"
#include"PositionSensor.h"
#include"SpeedSensor.h"
#include"DirectionSensor.h"
#include"StreetSensor.h"
#include<cstdlib>
#include<iostream>

int main(int argc, char** argv) {
    Sensor* sensor;
    try {
        size_t choice;
        int port;

        // get sensor type from start.sh input
        choice = atoi(argv[1]);
        port = atoi(argv[2]);

        switch(choice){
            case 1:
                sensor = new PositionSensor(33);
                break;
            case 2:
                sensor = new SpeedSensor(50);
                break;
            case 3:
                sensor = new DirectionSensor(100);
                break;
            case 4:
                sensor = new StreetSensor(100);
                break;
            default:
                cout<< "DEFAULT"<<endl;
                sensor = new PositionSensor(33);
                break;
        }

        // set server port
        sensor->setServerPort(port);
        
        // start sending data to server via UDP
        sensor->sendData(argv);

    }catch(const std::invalid_argument& io) {
        std::cerr<< io.what();
    }

    delete sensor;

    return 0;
}