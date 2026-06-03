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