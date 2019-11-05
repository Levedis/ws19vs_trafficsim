#ifndef VS19_DIRECTIONSENSOR_H
#define VS19_DIRECTIONSENSOR_H


#include "Sensor.h"

class DirectionSensor: public Sensor{
public:
    DirectionSensor(){};
    explicit DirectionSensor(const float& val, const string& unit="x,y");
    virtual ~DirectionSensor();
};

#endif //VS19_DIRECTIONSENSOR_H
