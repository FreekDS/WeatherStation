#ifndef I2C_SENSOR_H
#define I2C_SENSOR_H

#include "Sensor.h"

template<typename TDerived, uint8_t I2CAddress, size_t dataCount = 1>
class I2CSensor : public SensorBase<TDerived, dataCount>
{
public:
    constexpr auto size() const -> size_t { 
        return SensorBase<TDerived, dataCount>::size(); 
    }
 protected:
    uint8_t m_address = I2CAddress;
};

#endif // I2C_SENSOR_H