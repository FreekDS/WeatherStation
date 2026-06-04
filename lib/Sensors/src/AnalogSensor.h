#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H

#include <Arduino.h>

#include "Sensor.h"


template<typename TDerived, uint8_t ANALOG_PIN, size_t dataCount = 1>
class AnalogSensor : public SensorBase<TDerived, dataCount>
{
public:
    constexpr auto size() const -> size_t { 
        return SensorBase<TDerived, dataCount>::size();
    }
 protected:
    constexpr auto readPin() -> unsigned int { return analogRead(ANALOG_PIN); }
    constexpr auto readPinPercentage() -> float { return readPin() / 1024.0 * 100; }
};

#endif // ANALOG_SENSOR_H