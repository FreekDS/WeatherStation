#include "BMESensor.h"

template <unsigned int ADDRESS>
bool BMESensor<ADDRESS>::begin() const
{
    if (!m_bme280.begin(ADDRESS))
        return false;

    m_bme280.setSampling(
        Adafruit_BME280::MODE_FORCED,
        Adafruit_BME280::SAMPLING_X2,
        Adafruit_BME280::SAMPLING_X2,
        Adafruit_BME280::SAMPLING_X2, 
        Adafruit_BME280::FILTER_X2
    );

    return m_bme280.init();
}

template <unsigned int ADDRESS>
void BMESensor<ADDRESS>::fillData(DataPoint *dataPoints) const
{
    m_bme280.takeForcedMeasurement();

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