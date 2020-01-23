/*ThreadPool*/

#include <queue>
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <stdexcept>



class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize);

     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func&& func, Args&&... args)->std::future<decltype( func(args...) )>;
    ~ThreadPool();
private:
    std::vector<std::thread> threads_;// набор потоков
    std::queue< std::function<void()> > tasks_;// очередь задач
    std::mutex mutex_;
    std::condition_variable condition_;
    bool stopFlag;
};

// инициализация poolSize потоков
ThreadPool::ThreadPool(size_t poolSize) : stopFlag(false)
{
    for ( size_t i = 0; i < poolSize; ++i )
        threads_.emplace_back(
        [this] {
        while (true) {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(this->mutex_);

                this->condition_.wait(lock);

                if ( this->stopFlag && this->tasks_.empty() )
                    return;

                task = std::move(this->tasks_.front());
                this->tasks_.pop();
            }

            task();
        }
    }
    );
}

// добавление задач
template <class Func, class... Args>
auto ThreadPool::exec(Func&& func, Args&&... args)->std::future<decltype( func(args...) )>
{
    using return_type = decltype( func(args...) );

    auto task = std::make_shared< std::packaged_task<return_type()> >(
        std::bind(std::forward<Func>(func), std::forward<Args>(args)...)
        );

    auto res = task->get_future();
    
    mutex_.lock();
    tasks_.emplace([task]() { ( *task )( ); });
    mutex_.unlock();

    condition_.notify_one();
    return res;
}



ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(mutex_);
        stopFlag = true;
    }

    condition_.notify_all();

    for ( std::thread& thread_ : threads_ ) 
        thread_.join();
}
