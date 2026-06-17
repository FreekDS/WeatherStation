#include <taskbuffer.h>

auto TaskBufferAccessor::insert(Task func, uint16_t tickRate) -> bool
{
    if (m_lastStoredIndex >= m_size)
        return false;
    m_storage[m_lastStoredIndex++] = TaskInfo{.m_task = func, .m_tickRate = tickRate};
    return true;
};

TaskBufferAccessor::TaskBufferAccessor(TaskInfo *storage, size_t size) : m_storage{storage}, m_size{size} {};