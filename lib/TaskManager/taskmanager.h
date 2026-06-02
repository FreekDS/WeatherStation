#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <Arduino.h>


class TaskManager
{
public:
    using Task = void (*)();

    explicit TaskManager(uint16_t tickRate, Task func);

    void tick();

    auto registerTask(Task func, uint16_t tickRate) -> bool;

private:

    struct TaskInfo{
        Task m_task;
        uint16_t m_tickRate;
    };


    const uint16_t m_tickRate{100};
    Task m_func;

    unsigned long m_lastTick{0};
};

#endif // TASKMANAGER_H