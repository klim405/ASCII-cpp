#include "Timer.hpp"

#include <cassert>

namespace plotter {

    void Timer::Start() {
        assert(!start_time_.has_value());
        start_time_ = Clock::now();
    }

    void Timer::Stop() {
        assert(!stop_time_.has_value());
        stop_time_ = Clock::now();
    }

    void Timer::Restart() {
        start_time_ = Clock::now();
        stop_time_ = std::nullopt;
    }


    long long Timer::GetDuration() const {
        using namespace std::chrono;

        if (!start_time_.has_value()) {
            return 0;
        }

        if (!stop_time_.has_value()) {
            const auto duration = Clock::now() - start_time_.value();
            return duration_cast<microseconds>(duration).count();
        }

        const auto duration = stop_time_.value() - start_time_.value();
        return duration_cast<microseconds>(duration).count();
    }

}
