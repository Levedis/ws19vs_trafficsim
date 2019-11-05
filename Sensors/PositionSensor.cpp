//
// Created by cgrah on 01/11/2019.
//

#include "PositionSensor.h"

PositionSensor::PositionSensor(const float &val, const string &unit)
: Sensor("Position", val, unit)
{
}

PositionSensor::~PositionSensor() = default;
