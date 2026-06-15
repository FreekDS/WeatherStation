
#ifndef JSON_STREAMER_H
#define JSON_STREAMER_H

#include <Arduino.h>
#include <Sensor.h>

namespace JsonStreamer
{
    void streamToSerial(const DataPoint* dataPoints, const size_t dataPointCount, bool newlines);
    bool streamToBuffer(const DataPoint *dataPoints, const size_t numPoints, char *buffer, const size_t bufferSize);
}

#endif // JSON_STREAMER_H
