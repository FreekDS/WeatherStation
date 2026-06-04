#ifndef BME_SENSOR_H
#define BME_SENSOR_H

#include "I2CSensor.h"

#include <Adafruit_BME280.h>

template <unsigned int ADDRESS>
class BMESensor : public I2CSensor<BMESensor<ADDRESS>, ADDRESS>
{
public:
    static constexpr auto getSize() -> size_t { return 3; }

    bool begin() const
    {
        return m_bme280.begin(ADDRESS);
        // TODO: the BME is continuosly measuring, when switching to ESP32, this must become forced mode
        // --> take forced measurement
        // --> setup sampling rate also, no need to oversample ourselves
    }

    void fillData(DataPoint *dataPoints) const
    {
        dataPoints[0] = DataPoint{
            .m_name = "humidity",
            .m_value = m_bme280.readHumidity()};
        dataPoints[1] = DataPoint{
            .m_name = "temp",
            .m_value = m_bme280.readTemperature()};
        dataPoints[2] = DataPoint{
            .m_name = "pressure",
            .m_value = m_bme280.readPressure() / 100.0f};
    }

private:
    mutable Adafruit_BME280 m_bme280;
};

#endif // BME_SENSOR_H