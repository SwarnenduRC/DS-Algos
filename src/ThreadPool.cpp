#include "ThreadPool.hpp"

ThreadPool::ThreadPool(const ui32 threadCnt)
    : m_threadCnt(threadCnt)
{
    createThreads();
}

ThreadPool::~ThreadPool()
{
    waitForTasksToComplete();
    m_workerRunning = false;
    destroyThreads();
}

void ThreadPool::reset(const ui32 threadCnt)
{
    // First take the current task popping indicator
    auto lastTaskPopState = m_continuePopping.load();
    // Now set it to false to prevent any fresh task to be popped
    // from the queue so that only the running tasks get completed
    m_continuePopping = false;
    // Now wait for the already running tasks to get completed
    waitForTasksToComplete();
    // Now set worker function to stop from running
    // as we don't want to go in a loop of popping and
    // thus waiting eternal
    m_workerRunning = false;
    // Destroy the existing threads in the pool which
    // are by now not running any task
    destroyThreads();
    // Set the new thread counts and create the new pool with it
    m_threadCnt = threadCnt;
    m_pThreads.reset(new std::thread[m_threadCnt]);
    createThreads();
    // Set worker to run again
    m_workerRunning = true;
    // Get the last pop state for worker
    m_continuePopping = lastTaskPopState;
}

ui32 ThreadPool::getTaskQueuedCount() const noexcept 
{ 
    const std::scoped_lock lock(m_taskQueueMtx);
    return static_cast<ui32>(m_tasks.size()); 
}

void ThreadPool::sleepOrYield() noexcept
{
    if (m_sleepTime)
        std::this_thread::sleep_for(std::chrono::microseconds(m_sleepTime));
    else
        std::this_thread::yield();
}

bool ThreadPool::popTask(std::function<void()>& task)
{
    std::scoped_lock queueLock(m_taskQueueMtx);
    if (m_tasks.empty())
        return false;

    task = std::move(m_tasks.front());
    m_tasks.pop();
    return true;
}

void ThreadPool::worker()
{
    while (m_workerRunning)
    {
        std::function<void()> task;
        if (popTask(task))
        {
            task();
            m_totalTaskCnt--;   // As a new task has started executing means an old task is finished, thus decrease the total task count by 1
        }
        else
        {
            sleepOrYield();
        }
    }
}

void ThreadPool::createThreads()
{
    if (m_threadCnt)
    {
        for (auto idx = 0; idx < static_cast<int>(m_threadCnt); ++idx)
            m_pThreads[idx] = std::thread(&ThreadPool::worker, this);
    }
}

void ThreadPool::destroyThreads() noexcept
{
    for (ui32 idx = 0; idx < m_threadCnt; ++idx)
    {
        if (m_pThreads[idx].joinable())
            m_pThreads[idx].join();
    }
}

void ThreadPool::waitForTasksToComplete() noexcept
{
    while (true)
    {
        if (m_continuePopping)
        {
            if (getTaskRunningCount() == 0)
                break;
        }
        else
        {
            if (m_totalTaskCnt == 0)
                break;
        }
        sleepOrYield();
    }
}

