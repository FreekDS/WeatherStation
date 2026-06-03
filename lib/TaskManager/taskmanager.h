#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <Arduino.h>

#include <taskbuffer.h>

class TaskManager
{
public:
    explicit TaskManager(TaskBufferAccessor bufferAccessor);

    // Avoid temporaries to be passed in.
    template<size_t N>
    explicit TaskManager(TaskBuffer<N>&&) = delete;

    void update();

    auto registerTask(Task func, uint16_t tickRate) -> bool;

private:
    TaskBufferAccessor m_taskBufferAccessor;
};

#endif // TASKMANAGER_H