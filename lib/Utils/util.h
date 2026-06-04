#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

#include "Sensor.h"
#include "logging.h"

namespace mystd
{
    template <typename T>
    constexpr T &&move(T &arg) noexcept
    {
        return static_cast<T &&>(arg);
    }

    template <typename T>
    constexpr T &&move(T &&arg) noexcept
    {
        return static_cast<T &&>(arg);
    }
}

namespace util
{
    template <typename TImpl>
    void printSensorData(SensorBase<TImpl> &sensor)
    {
        DataPoint dataPoints[sensor.size()];
        // Serial.println(sensor.size());
        sensor.fillData(dataPoints);
        for (auto i = 0U; i < sensor.size(); i++)
        {
            LOG(dataPoints[i].m_name);
            LOG(" : ");
            LOG_LN(dataPoints[i].m_value);
        }
        LOG_LN("---------");
    }
}

namespace CrossBoard
{
    inline auto readMilliVolts(uint8_t analogPin) -> float
    {
#if defined(ARDUINO_ARCH_ESP32)
        return static_cast<float>(analogReadMilliVolts(analogPin));
#elif defined(__AVR__)
        float raw = static_cast<float>(analogRead(analogPin));
        return (raw / 1023.f) * 5000.f; // Assuming 5V
#else
        float raw = static_cast<float>(analogRead(analogPin));
        return (raw / 1023.f) * 3300.f; // Assuming 3.3V
#endif
    }
}

#endif // UTILS_H