#include "LightSensor.h"

template <unsigned int ADDRESS>
bool LightSensor<ADDRESS>::begin() const
{
    return m_bh1750.begin(BH1750::Mode::ONE_TIME_LOW_RES_MODE, ADDRESS);
}

template <unsigned int ADDRESS>
void LightSensor<ADDRESS>::fillData(DataPoint *dataPoints) const
{
    m_bh1750.configure(BH1750::ONE_TIME_HIGH_RES_MODE_2);
    dataPoints[0] = DataPoint{
        .m_name = "light_intensity",
        .m_value = max(0.0f, m_bh1750.readLightLevel())};
}