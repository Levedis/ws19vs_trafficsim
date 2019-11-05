//
// Created by cgrah on 01/11/2019.
//

#include "DirectionSensor.h"

DirectionSensor::DirectionSensor(const float &val, const string &unit)
: Sensor("Direction", val, unit)
{
}

DirectionSensor::~DirectionSensor() = default;
