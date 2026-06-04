#include "UVSensor.h"

template <uint8_t PIN>
void UVSensor<PIN>::fillData(DataPoint *dataPoints) const
{
    const auto raw = this->readPin();
    dataPoints[0] = DataPoint{
        .m_name = "uv_raw",
        .m_value = static_cast<float>(raw)
    };
    dataPoints[1] = DataPoint{
        .m_name = "uv_todo",
        .m_value = raw * 1000.0f
    };
}