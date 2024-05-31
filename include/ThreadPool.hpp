/**
 * @file ThreadPool.hpp
 * @author your name (you@domain.com)
 * @brief A C++17 thread pool class.
 * The user submits tasks to be executed into a queue.
 * Whenever a thread becomes available, it pops a task from the queue and executes it.
 * Each task is automatically assigned a future, which can be used to wait for the task 
 * to finish executing and/or obtain its eventual return value.
 * @version 0.1
 * @date 2024-05-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _THREAD_POOL_HPP_
#define _THREAD_POOL_HPP_

#include <atomic>      // std::atomic
#include <chrono>      // std::chrono
#include <cstdint>     // std::int_fast64_t, std::uint_fast32_t
#include <functional>  // std::function
#include <algorithm>   // std::algorithm
#include <future>      // std::future, std::promise
#include <memory>      // std::shared_ptr, std::unique_ptr
#include <mutex>       // std::mutex, std::scoped_lock
#include <queue>       // std::queue
#include <thread>      // std::this_thread, std::thread
#include <type_traits> // std::common_type_t, std::decay_t, std::enable_if_t, std::is_void_v, std::invoke_result_t
#include <utility>     // std::move

using ui32 = std::uint_fast32_t;

class ThreadPool
{
    public:
        /**
         * @brief All the normal constructors are not allowed
         * for now.
         */
        ThreadPool() = delete;
        ThreadPool(const ThreadPool& rhs) = delete;
        ThreadPool(ThreadPool&& rhs) = delete;
        ThreadPool& operator=(const ThreadPool& rhs) = delete;
        ThreadPool& operator=(ThreadPool&& rhs) = delete;
        ~ThreadPool();
        /**
         * @brief Construct a new Thread Pool object
         * Constructs a new threadpool object with the user
         * provided no of threads.
         * 
         * @param threadCnt The max no of threads the pool can have.
         * Default is std::thread::hardware_concurrency()
         */
        ThreadPool(const ui32 threadCnt = std::thread::hardware_concurrency());
        /**
         * @brief Resets the threadpool with new no of threads
         * It resets the existing thread pool with the new no of threads.
         * But before that it completes all the tasks which are running,
         * preserves the state of the task queue and then resets the thread
         * pool with the new no of threads
         * 
         * @param threadCnt The max no of threads the pool can have.
         * Default is std::thread::hardware_concurrency()
         */
        void reset(const ui32 threadCnt = std::thread::hardware_concurrency());

        inline ui32 getTotalTaskCount() const noexcept { return m_totalTaskCnt; }
        ui32 getTaskQueuedCount() const noexcept;
        inline ui32 getTaskRunningCount() const noexcept { return m_totalTaskCnt - getTaskQueuedCount(); }
        inline ui32 getThreadsCount() const noexcept { return m_threadCnt; }
    
    private:
        /**
         * @brief Sleeps for sleep duration in microseconds.
         * If can't sleep then just yield instead.
         */
        void sleepOrYield() noexcept;
        /**
         * @brief Pops and gets the next task from the task queue
         * 
         * @param [out] task The task to be exceuted
         * @return true If the queue isn't empty and min one task is available to execute, otherwise 
         * @return false 
         */
        bool popTask(std::function<void()>& task);
        /**
         * @brief A worker function to be assigned to each thread in the pool.
         * Continuously pops tasks out of the queue and executes them, as long 
         * as the atomic variable m_workerRunning is set to true.
         */
        void worker();
        /**
         * @brief Creates the pool of threads
         * It creates the pool of threads limited by the number
         * as dictate by the variable m_threadCnt. While creating
         * the threads it attaches a worker function along with it
         * to perform the task from the queue. @see worker
         */
        void createThreads();
        /**
         * @brief Destroys the threads in the pool by joining them.
         * It destroys the threads from the thread pool array
         * @see m_pThreads one by one by joining them one after another
         */
        void destroyThreads() noexcept;
        /**
         * @brief Wait for tasks to be completed
         * Normally, this function waits for all tasks, both those that are currently running in the threads
         * and those that are still waiting in the queue.
         * However, if the variable @see m_continuePopping is set to false, this function only waits for the 
         * currently running tasks (otherwise it would wait forever).
         */
        void waitForTasksToComplete() noexcept;
        /**
         * @brief Push a function with no arguments or return value into the task queue.
         * i.e.; void foo() type of tasks
         * 
         * @tparam T The type of the function.
         * @param newTask The function to push.
         */
        template<typename T>
        void pushTask(const T& newTask)
        {
            std::unique_lock lock(m_taskQueueMtx);
            auto task = std::function<void()>(newTask);
            m_tasks.emplace(task);
            m_totalTaskCnt++;
            lock.release();
        }
        /**
         * @brief Push a function with arguments, but no return value, into the task queue.
         * The function is wrapped inside a lambda in order to hide the arguments,
         * as the tasks in the queue must be of type std::function<void()>,
         * so they cannot have any arguments or return value.
         * If no arguments are provided, the other overload will be used, in order to avoid the (slight) overhead of using a lambda
         * 
         * @tparam T The type of the function.
         * @tparam A The types of the arguments.
         * @param newTask The function to push.
         * @param args The arguments to pass to the function.
         */
        template<typename T, typename ...A>
        void pushTask(const T& newTask, const A& ...args)
        {
            auto task = [newTask, args...]()
            {
                newTask(args...);
            };
            pushTask(task);
        }
        /**
         * @brief Submit a function with zero or more arguments and no return value into the task queue
         * Submit a function with zero or more arguments and no return value into the task queue
         * and get an std::future<bool> that will be set to true upon completion of the task.
         * 
         * @tparam F The type of the function.
         * @tparam A The types of the zero or more arguments to pass to the function.
         * @param func The function to submit.
         * @param args The zero or more arguments to pass to the function.
         * @return std::future<bool> A future to be used later to check if the function has finished its execution.
         */
        template<typename F, typename ...A, typename = std::enable_if_t<std::is_void_v<std::invoke_result_t<std::decay_t<F>, std::decay_t<A>...>>>>
        std::future<bool> submitTask(const F& func, const A&... args)
        {
            /**
             * @brief The template declaration uses SFINAE to enable the template only if the return type of invoking F with arguments A... is void. 
             * This can be useful when you want to create a template that only participates in overload resolution if the callable F returns void.
             */
            // Take a promise in a shared pointer so that while passing into the lambda we can set the value
            // upon completion of the task function
            auto taskPromise = std::make_shared<std::promise<bool>>();
            auto taskFuture = taskPromise->get_future();
            auto task = [func, args..., taskPromise]()
            {
                try
                {
                    func(args...);
                    taskPromise->set_value(true);
                }
                catch(const std::exception& e)
                {
                    taskPromise->set_exception(std::current_exception());
                }
                
            };
            pushTask(task);
            return taskFuture;
        }
        template<typename F, typename ...A, typename R = std::invoke_result_t<std::decay_t<F>, std::decay_t<A>...>, typename = std::enable_if_t<!std::is_void_v<R>>>
        std::future<R> submitTask(const F& func, const A&... args)
        {
            /**
             * @brief The template declaration uses SFINAE to enable the template only if the return type of invoking F with arguments A... is non void. 
             * This can be useful when you want to create a template that only participates in overload resolution if the callable F returns non void value
             */
            // Take a promise in a shared pointer so that while passing into the lambda we can set the value
            // upon completion of the task function
            auto taskPromise = std::make_shared<std::promise<R>>();
            auto taskFuture = taskPromise->get_future();
            auto task = [func, args..., taskPromise]()
            {
                try
                {
                    taskPromise->set_value(func(args...));
                }
                catch(const std::exception& e)
                {
                    taskPromise->set_exception(std::current_exception());
                }
                
            };
            pushTask(task);
            return taskFuture;
        }

        //Variables 
        /**
         * @brief A smart pointer to manage the memory allocated for the threads.
         */
        std::unique_ptr<std::thread[]> m_pThreads;
        /**
         * @brief The number of threads in the pool.
         */
        ui32 m_threadCnt = 0;
        /**
         * @brief An atomic variable to keep track of the total number of unfinished task
         * either still in the queue, or running in a thread.
         */
        std::atomic<ui32> m_totalTaskCnt = 0;
        /**
         * @brief A queue of tasks to be executed by the threads.
         */
        std::queue<std::function<void()>> m_tasks = {};
        /**
         * @brief A mutex to synchronize access to the tasks queued by different threads.
         */
        mutable std::mutex m_taskQueueMtx = {};
        /**
         * @brief An atomic variable indicating to the workers to pause.
         * When set to false, the workers temporarily stop popping new tasks out of the queue,
         * although any tasks already executed will keep running until they are done.
         * Set to true again to resume popping tasks.
         */
        std::atomic<bool> m_continuePopping = true;
        /**
         * @brief An atomic variable indicating to the workers to keep running.
         * When set to false, the workers permanently stop working.
         */
        std::atomic<bool> m_workerRunning = true;
        /**
         * @brief The duration, in microseconds, that the worker function should sleep for
         * when it cannot find any tasks in the queue.
         * If set to 0, then instead of sleeping, the worker function will execute std::this_thread::yield()
         * if there are no tasks in the queue. The default value is 1000.
         */
        ui32 m_sleepTime = 1000;
};

#endif