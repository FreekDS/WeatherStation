#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

#include <crtp.h>

// Named data point. Provided by the various sensors.
struct DataPoint
{
    const char *m_name{""};
    float m_value{0.0};
};

/* CRTP base for sensors.
Curiously Recurring Template Pattern, used for static polymorphism.
Each sensor must implement
    - fillData
    - [OPTIONAL] getSize, if more than one data point at a single time is generated.
Intended use:
    size() tells callers how many different data points a single sensor will provide each fillData call.
    Callers can use it to prepare an array of datapoints to be filled in.

*/
template <typename TDerived>
class SensorBase
{

public:
    constexpr auto size() const -> size_t { return TDerived::getSize(); }

    void fillData(DataPoint *dataPoints) const
    {
        static_cast<const TDerived &>(*this).fillData(dataPoints);
    }

protected:
    constexpr SensorBase()
    {
        CRTP_REQUIRED(TDerived, fillData, void);
    }

    static constexpr size_t getSize() { return 1; }
};

#endif // SENSOR_H