//
// Created by cgrah on 01/11/2019.
//

#include "StreetSensor.h"

StreetSensor::StreetSensor(const float &val, const string &unit)
: Sensor("Street", val, unit)
{
}

StreetSensor::~StreetSensor() = default;
