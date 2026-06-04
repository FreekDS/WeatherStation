#ifndef BME_SENSOR_H
#define BME_SENSOR_H

#include "I2CSensor.h"

#include <Adafruit_BME280.h>

template <unsigned int ADDRESS>
class BMESensor : public I2CSensor<BMESensor<ADDRESS>, ADDRESS>
{
public:
    static constexpr auto getSize() -> size_t { return 3; }

    bool begin() const;

    void fillData(DataPoint *dataPoints) const;

private:
    mutable Adafruit_BME280 m_bme280;
};

#include "src/BMESensor_impl.inl"

#endif // BME_SENSOR_H