#ifndef TIMER_H_YZ4EBNSJ
#define TIMER_H_YZ4EBNSJ

#include <cxxopts.hpp>
namespace jrd {
namespace time {

template <typename TimeType, typename ClockType> 
class Timer {

   public:
    explicit Timer(bool run = false) {
        if (run) Reset();
    }
    void Reset() { _start = ClockType::now(); }
    TimeType elapsed() const {
        return std::chrono::duration_cast<TimeType>(
            ClockType::now() - _start);
    }
    template <typename T, typename Traits>
    friend std::basic_ostream<T, Traits>& operator<<(
        std::basic_ostream<T, Traits>& out, const Timer& timer) {
        out << timer.elapsed().count();
        return out;
    }

   private:
    typename ClockType::time_point _start;
};
template <typename T = std::chrono::milliseconds, typename C = std::chrono::high_resolution_clock>
Timer<T, C> make_time(bool bStart = true) {
    return Timer<T, C>{bStart};
}
}
}

#endif /* end of include guard: TIMER_H_YZ4EBNSJ */
