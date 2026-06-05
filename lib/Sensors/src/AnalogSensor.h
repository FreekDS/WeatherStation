#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H

#include <Arduino.h>

#include "Sensor.h"


/* Additional layer of abstraction for analog sensors.
Analog sensors are connected to a pin, provided through the ANALOG_PIN template argument.
*/
template<typename TDerived, uint8_t ANALOG_PIN>
class AnalogSensor : public SensorBase<TDerived>
{
protected:
    constexpr auto readPin() const -> unsigned int { return analogRead(ANALOG_PIN); }
    constexpr auto readPinPercentage() const -> float { return readPin() / 1024.0 * 100; }
};

#endif // ANALOG_SENSOR_H