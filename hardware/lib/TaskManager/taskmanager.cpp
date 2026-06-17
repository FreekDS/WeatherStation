#include <taskmanager.h>

#include <util.h>

TaskManager::TaskManager(TaskBufferAccessor bufferAccessor) : m_taskBufferAccessor{mystd::move(bufferAccessor)} {}

auto TaskManager::update() -> void
{
    auto ms = millis();

    for (auto &[task, taskTickRate, lastTick] : m_taskBufferAccessor)
    {
        if (!task)
            continue;

        if (ms - lastTick >= taskTickRate)
        {
            task();
            lastTick = ms;
        }
    }
}

auto TaskManager::registerTask(Task func, uint16_t tickRate) -> bool
{
    return m_taskBufferAccessor.insert(func, tickRate);
}