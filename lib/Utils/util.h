#include <Arduino.h>


namespace mystd
{
    template <typename T>
    constexpr T &&move(T &arg) noexcept
    {
        return static_cast<T &&>(arg);
    }

    template <typename T>
    constexpr T &&move(T &&arg) noexcept
    {
        return static_cast<T &&>(arg);
    }
}

namespace CrossBoard
{
    inline auto readMilliVolts(uint8_t analogPin) -> float
    {
#if defined(ARDUINO_ARCH_ESP32)
        return static_cast<float>(analogReadMilliVolts(analogPin));
#elif defined(__AVR__)
        float raw = static_cast<float>(analogRead(analogPin));
        return (raw / 1023.f) * 5000.f; // Assuming 5V
#else
        float raw = static_cast<float>(analogRead(analogPin));
        return (raw / 1023.f) * 3300.f; // Assuming 3.3V
#endif
    }
}