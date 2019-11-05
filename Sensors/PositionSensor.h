#ifndef VS19_POSITIONSENSOR_H
#define VS19_POSITIONSENSOR_H


#include "Sensor.h"

class PositionSensor: public Sensor{
public:
    PositionSensor(){};
    explicit PositionSensor(const float& val, const string& unit="x,y");
    virtual ~PositionSensor();
};

#endif //VS19_POSITIONSENSOR_H
