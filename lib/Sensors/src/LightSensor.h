
#include "I2CSensor.h"
#include <BH1750.h>

template <unsigned int I2C_ADDRESS>
class LightSensor : public I2CSensor<LightSensor<I2C_ADDRESS>, I2C_ADDRESS>
{
public:
    bool begin() const
    {
        return m_bh1750.begin(BH1750::Mode::ONE_TIME_LOW_RES_MODE, I2C_ADDRESS);
    }

    void fillData(DataPoint *dataPoints) const
    {
        m_bh1750.configure(BH1750::ONE_TIME_HIGH_RES_MODE_2);
        dataPoints[0] = DataPoint{
            .m_name = "light_intensity",
            .m_value = max(0.0f, m_bh1750.readLightLevel())};
    }

private:
    mutable BH1750 m_bh1750;
};

