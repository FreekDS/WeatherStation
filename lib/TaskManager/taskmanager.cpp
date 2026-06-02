#include <taskmanager.h>

TaskManager::TaskManager(uint16_t tickRate, Task func) : m_tickRate{tickRate}, m_func{func}
{
    m_lastTick = millis();
}

auto TaskManager::tick() -> void
{
    auto ms = millis();
    if (ms - m_lastTick < m_tickRate)
        return;

    m_lastTick = ms;
    m_func();
}

auto TaskManager::registerTask(Task func, uint16_t tickRate) -> bool
{
    return true;
}