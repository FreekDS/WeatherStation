#ifndef I2C_SENSOR_H
#define I2C_SENSOR_H

#include "Sensor.h"
#include <util.h>

template <typename TDerived, uint8_t I2CAddress>
class I2CSensor : public SensorBase<TDerived>
{
public:
    bool begin() const
    {
        static_assert(&SensorBase<TDerived>::begin != nullptr);
        return static_cast<const TDerived &>(*this).begin();
    }
    bool stop() const { return static_cast<const TDerived &>(*this).stop(); }

protected:
    uint8_t m_address = I2CAddress;
};

#endif // I2C_SENSOR_H