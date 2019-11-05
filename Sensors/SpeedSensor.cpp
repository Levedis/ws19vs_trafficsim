//
// Created by cgrah on 01/11/2019.
//

#include "SpeedSensor.h"

SpeedSensor::SpeedSensor(const float &val, const string &unit)
: Sensor("Speed", val, unit)
{
}

SpeedSensor::~SpeedSensor() = default;
