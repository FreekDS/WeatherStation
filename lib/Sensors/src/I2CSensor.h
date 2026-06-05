#ifndef I2C_SENSOR_H
#define I2C_SENSOR_H

#include "Sensor.h"
#include <util.h>

/* Additional layer of abstraction for I2C sensors.
I2C sensors are digital sensors connected to the I2C pins (SCL and SDA).
Each I2C sensor has a (unique) address on the SDA bus, provided by the template argument I2CAddress
I2C sensors must implement
    - begin() const: sets up the I2C sensor at the start of the program.
*/
template <typename TDerived, uint8_t I2CAddress>
class I2CSensor : public SensorBase<TDerived>
{
public:
    bool begin() const
    {
        static_assert(&SensorBase<TDerived>::begin != nullptr);
        return static_cast<const TDerived &>(*this).begin();
    }

protected:
    constexpr I2CSensor() : SensorBase<TDerived>()
    {
        CRTP_REQUIRED(TDerived, begin, bool);
    }
};

#endif // I2C_SENSOR_H