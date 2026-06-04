#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

struct DataPoint {
    const char* m_name{""};
    float m_value{0.0};
};

template <typename TDerived>
class SensorBase
{
public: 
    constexpr auto size() const -> size_t { return TDerived::getSize(); }
    void fillData(DataPoint* dataPoints) const { static_cast<const TDerived &>(*this).fillData(dataPoints); }

protected:
    static constexpr size_t getSize() { return 1; }
    SensorBase() = default;
};

#endif // SENSOR_H