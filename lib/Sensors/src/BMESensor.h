#ifndef BME_SENSOR_H
#define BME_SENSOR_H

#include "I2CSensor.h"

#include "constants.h"

class BMESensor : public I2CSensor<BMESensor, ADDR_SENSOR_BME, 3>
{
public:
    void fillData(DataPoint *dataPoints) const
    {
        dataPoints[0] = {
            .m_name = "humidity",
            .m_value = 90.0
        };
        dataPoints[1] =  {
            .m_name = "temp",
            .m_value = 20
        };
        dataPoints[2] =  {
            .m_name = "pressure",
            .m_value = 1024.0
        };
    }
};

#endif // BME_SENSOR_H