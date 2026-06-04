#ifndef I2C_SENSOR_H
#define I2C_SENSOR_H

#include "Sensor.h"

template<typename TDerived, uint8_t I2CAddress>
class I2CSensor : public SensorBase<TDerived>
{
 protected:
    uint8_t m_address = I2CAddress;
};

#endif // I2C_SENSOR_H