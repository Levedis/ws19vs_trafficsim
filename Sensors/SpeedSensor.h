#ifndef VS19_SPEEDSENSOR_H
#define VS19_SPEEDSENSOR_H


#include "Sensor.h"

class SpeedSensor: public Sensor{
public:
    SpeedSensor(){};
    explicit SpeedSensor(const float& val, const string& unit="x,y");
    virtual ~SpeedSensor();
};

#endif //VS19_SPEEDSENSOR_H
