#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

#include "AnalogSensor.h"

template<uint8_t PIN>
class SoilMoistureSensor : public AnalogSensor<SoilMoistureSensor<PIN>, PIN>
{
public:
    void fillData(DataPoint *dataPoints) const;
};

#include "src/SoilMoistureSensor_impl.inl"

#endif // SOIL_MOISTURE_SENSOR_H