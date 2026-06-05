
#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "I2CSensor.h"
#include <BH1750.h>

template <unsigned int I2C_ADDRESS>
class LightSensor : public I2CSensor<LightSensor<I2C_ADDRESS>, I2C_ADDRESS>
{
public:
    bool begin() const;

    void fillData(DataPoint *dataPoints) const;
private:
    mutable BH1750 m_bh1750;
};

#include "src/LightSensor_impl.inl"

#endif // LIGHT_SENSOR_H

