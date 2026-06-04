#ifndef UV_SENSOR_H
#define UV_SENSOR_H

#include "AnalogSensor.h"

template<uint8_t PIN>
class UVSensor : public AnalogSensor<UVSensor<PIN>, PIN>
{
public:
    static constexpr size_t getSize() { return 2; }

    void fillData(DataPoint *dataPoints) const;
};

#include "src/UVSensor_impl.h"

#endif // UV_SENSOR_H