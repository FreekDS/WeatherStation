#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

struct DataPoint {
    const char* m_name{""};
    float m_value{0.0};
};

template <typename TDerived, size_t dataCount = 1>
class SensorBase
{
public:

    constexpr auto size() const -> size_t { return dataCount; }

    void fillData(DataPoint* dataPoints) const { return static_cast<const TDerived &>(this).fillData(dataPoints); }

protected:
    SensorBase() = default;
};

#endif // SENSOR_H