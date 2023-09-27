#ifndef c_queue_hpp
#define c_queue_hpp

#include <queue>
#include <mutex>

class concurrent_queue_exception : public std::runtime_error
{
public:
    concurrent_queue_exception() : std::runtime_error("Queue is empty") {}
    concurrent_queue_exception(const char *s) : std::runtime_error(s) {}
};

template <class T>
class concurrent_queue
{
    std::mutex m;
    std::queue<T> q;
    std::condition_variable cv;
    
public:
    concurrent_queue() = default;
    void push(T value)
    {
        std::lock_guard<std::mutex> lck_grd(m);
        q.push(value);
        cv.notify_one();
    }
    
    void pop(T& value)
    {
        std::unique_lock<std::mutex> lck_grd(m);
        cv.wait(lck_grd, [this] {return !q.empty();});
        if(q.empty())
        {
            throw concurrent_queue_exception("Queue is empty");
        }
        
        value = q.front();
        q.pop();
    }
};


#endif /* c_queue_hpp */
