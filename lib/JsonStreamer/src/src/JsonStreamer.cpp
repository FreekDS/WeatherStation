#include "JsonStreamer.h"

#include <logging.h>

namespace JsonStreamer
{
    void streamToSerial(DataPoint *dataPoints, size_t dataPointCount, bool newlines = true)
    {
        auto printDP = [](const DataPoint &dp)
        {
            const auto &[name, value] = dp;
            LOG("\"");
            LOG(name);
            LOG("\":");
            LOG(value);
        };

        LOG('{');
        for (size_t i = 0; i < dataPointCount - 1; i++)
        {
            printDP(dataPoints[i]);
            LOG(",");
            if (newlines)
                LOG_LN("");
        }
        printDP(dataPoints[dataPointCount - 1]);
        LOG_LN('}');
    }

    bool streamToBuffer(DataPoint *dataPoints, size_t numPoints, char *buffer, size_t bufferSize)
    {
        if (buffer == nullptr || dataPoints == nullptr || bufferSize == 0)
            return false;

        size_t bufferOffset{0};
        int lastWritten{0};

        auto isBufferOverflowing = [&bufferSize, &bufferOffset, &lastWritten]()
        {
            return lastWritten < 0 || static_cast<size_t>(lastWritten) >= bufferSize - bufferOffset;
        };

        auto writeToBuffer = [&lastWritten, &buffer, &bufferOffset, &bufferSize, &isBufferOverflowing](const char *strFmt, auto... args)
        {
            const auto bufferPos = buffer + bufferOffset;
            const auto remainingSize = bufferSize - bufferOffset;

            lastWritten = snprintf(bufferPos, remainingSize, strFmt, args...);
            if (isBufferOverflowing())
                return false;
            bufferOffset += lastWritten;
            return true;
        };

        if (!writeToBuffer("{"))
            return false;

        // TODO: write sensor values
        for (size_t i = 0; i < numPoints; i++)
        {
            const auto &[name, value] = dataPoints[i];
            if (!writeToBuffer("%s: %.4f", name, value))
                return false;

            if (i < numPoints - 1)
                if (!writeToBuffer(","))
                    return false;
        }

        if (!writeToBuffer("}"))
            return false;

        return true;
    }
}