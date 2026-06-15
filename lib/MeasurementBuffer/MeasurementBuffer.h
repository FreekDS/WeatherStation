#ifndef MEASUREMENT_BUFFER_H
#define MEASUREMENT_BUFFER_H

#include "Arduino.h"
#include <Sensor.h>

template <size_t SIZE>
class MeasurementBuffer
{
public:
    bool isFull() const { return m_pointer >= SIZE; }

    bool insert(const DataPoint &dp)
    {
        if (isFull())
            return false;
        m_dataPoints[m_pointer++] = dp;
        return true;
    }

    const DataPoint *begin() const
    {
        return &m_dataPoints[0];
    }

    const DataPoint *end() const
    {
        return &m_dataPoints[m_pointer];
    }

    void clear()
    {
        m_pointer = 0;
    }

    constexpr size_t size()
    {
        return m_pointer + 1;
    }

    constexpr size_t capacity()
    {
        return SIZE;
    }

    template <typename... TSensors>
    bool readSensors(const TSensors &...sensors)
    {
        static_assert((__is_base_of(SensorBase<TSensors>, TSensors) && ...));
        bool success = true;

        auto read = [&success, this](const auto &sensor)
        {
            if (!success)
                return;
            DataPoint dps[sensor.size()];
            sensor.fillData(dps);
            for (size_t i = 0; i < sensor.size(); i++)
                success = insert(dps[i]);
        };

        (read(sensors), ...);

        return success;
    }

private:
    size_t m_pointer{0};
    DataPoint m_dataPoints[SIZE];
};

#endif // MEASUREMENT_BUFFER_H