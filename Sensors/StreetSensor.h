#ifndef VS19_STREETSENSOR_H
#define VS19_STREETSENSOR_H


#include "Sensor.h"

class StreetSensor: public Sensor{
public:
    StreetSensor(){};
    explicit StreetSensor(const float& val, const string& unit="x,y");
    virtual ~StreetSensor();
};

#endif //VS19_STREETSENSOR_H
