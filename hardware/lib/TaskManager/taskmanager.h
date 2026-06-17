#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <Arduino.h>

#include <taskbuffer.h>

/* Handles when specific tasks need to run.
A TaskBuffer needs to be passed in of appropriate size to hold all tasks.
Tasks are automatically triggered at the frequency of tickRate provided in registerTask.
*/
class TaskManager
{
public:
    explicit TaskManager(TaskBufferAccessor bufferAccessor);

    // Avoid temporaries (rvalues) to be passed in.
    template<size_t N>
    explicit TaskManager(TaskBuffer<N>&&) = delete;

    void update();

    auto registerTask(Task func, uint16_t tickRate) -> bool;

private:
    TaskBufferAccessor m_taskBufferAccessor;
};

#endif // TASKMANAGER_H