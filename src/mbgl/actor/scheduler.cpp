#include <mbgl/actor/scheduler.hpp>
#include <mbgl/util/thread_local.hpp>
#include <mbgl/util/thread_pool.hpp>
#include <iostream>

namespace mbgl {

util::ThreadLocal<Scheduler> g_currentScheduler;

static auto& current() {
    static util::ThreadLocal<Scheduler> scheduler;
    return scheduler;
};

void Scheduler::SetCurrent(Scheduler* scheduler) {
    current().set(scheduler);
}

Scheduler* Scheduler::GetCurrent() {
    return current().get();
}

// static
std::shared_ptr<Scheduler> Scheduler::GetBackground() {
    // static std::weak_ptr<Scheduler> weak;
    // static std::mutex mtx;
    // 
    // std::lock_guard<std::mutex> lock(mtx);
    // std::shared_ptr<Scheduler> scheduler = weak.lock();
    // 
    // if (!scheduler) {
    //     std::clog << "creating scheduler\n";
    //     weak = scheduler = std::make_shared<ThreadPool>(4);
    // } else {
    //     std::clog << "re-using scheduler\n";      
    // }
    // 
    // return scheduler;
    return std::make_shared<ThreadPool>(2);
}

} //namespace mbgl
