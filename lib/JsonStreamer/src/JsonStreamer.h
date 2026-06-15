
#ifndef JSON_STREAMER_H
#define JSON_STREAMER_H

#include <Arduino.h>
#include <Sensor.h>

namespace JsonStreamer
{
    void streamToSerial(DataPoint* dataPoints, size_t dataPointCount, bool newlines);
    bool streamToBuffer(DataPoint *dataPoints, size_t numPoints, char *buffer, size_t bufferSize);
}

#endif // JSON_STREAMER_H
