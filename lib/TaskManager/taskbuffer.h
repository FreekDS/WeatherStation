#ifndef TASKBUFFER_H
#define TASKBUFFER_H

#include <Arduino.h>

using Task = void (*)();

// Store task metadata to know when it should run.
struct TaskInfo
{
    Task m_task;
    uint16_t m_tickRate;
    unsigned long m_lastRun{0};
};

// Provides a safe access pattern into a TaskBuffer.
// Used in the TaskManager.
class TaskBufferAccessor
{
public:
    constexpr auto cbegin() const -> const TaskInfo * { return &m_storage[0]; }
    constexpr auto cend() const -> const TaskInfo * { return &m_storage[m_size]; }
    constexpr auto begin() -> TaskInfo * { return &m_storage[0]; }
    constexpr auto end() -> TaskInfo * { return &m_storage[m_size]; }
    constexpr auto size() -> size_t { return m_size; }
    constexpr auto at(size_t idx) -> TaskInfo & { return m_storage[idx]; }

private:
    friend class TaskManager;

    template <size_t>
    friend class TaskBuffer;

    // True of insertion was successful, false if insertion failed (e.g. TaskBuffer is full)
    auto insert(Task func, uint16_t tickRate) -> bool;
    explicit TaskBufferAccessor(TaskInfo *storage, size_t size);

    TaskInfo *m_storage;
    const size_t m_size;
    size_t m_lastStoredIndex{0};
};

// Simple wrapper around a TaskInfo array of size N
template <size_t N>
class TaskBuffer
{
public:
    operator TaskBufferAccessor() { return TaskBufferAccessor{static_cast<TaskInfo *>(m_data), static_cast<size_t>(N)}; }

private:
    TaskInfo m_data[N];
};

template <size_t N>
constexpr auto makeTaskBuffer() -> TaskBuffer<N>
{
    return TaskBuffer<N>{};
}

#endif // TASKBUFFER_H