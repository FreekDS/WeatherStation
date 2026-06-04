#include "SoilMoistureSensor.h"

template <uint8_t PIN>
void SoilMoistureSensor<PIN>::fillData(DataPoint *dataPoints)
{
    dataPoints[0] = DataPoint{
        .m_name = "soil_moisture",
        .m_value = this->readPinPercentage()
    };
}