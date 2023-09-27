#include <iostream>
#include <future>
#include "c_queue.hpp"
#include "thread_pool.hpp"

using namespace std::literals;

std::mutex m;

void task()
{
    std::lock_guard<std::mutex> lg(m);
    std::cout << "Thread id: " << std::this_thread::get_id() << " started task" << std::endl;
    
    std::this_thread::sleep_for(100ms);
    std::cout << "Thread id: " << std::this_thread::get_id() << " ended task" << std::endl;
}


int main(int argc, const char * argv[]) {
    
    thread_pool pool;
    
    for(int i=0; i<10; ++i)
        pool.submit(task);
    
    std::this_thread::sleep_for(5s);
   
    
    return 0;
}
