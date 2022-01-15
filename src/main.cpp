#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <chrono>
#include <functional>

#include "sorts.h"

template <typename T>
decltype(auto) generateRandomVec(unsigned size = 100, int min = 0, int max = 100) {
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    std::uniform_int_distribution<T> dist {min, max};
    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };
    std::vector<T> vec(size);
    generate(std::begin(vec), std::end(vec), gen);
    return vec;
}

class Timer {
public:
    using time_t        = std::chrono::system_clock::time_point;
    using clock         = std::chrono::high_resolution_clock;
    using milliseconds  = std::chrono::milliseconds;
    using seconds       = std::chrono::seconds;

    enum class TimerMode {
        Milliseconds,
        Seconds
    };

    explicit Timer(TimerMode mode = TimerMode::Milliseconds) noexcept
        : _mode(mode), _startTime(clock::now())
    {}

    void start() noexcept {
        _startTime = clock::now();
    }

    [[nodiscard]] long elapsed() const noexcept {
        switch (_mode)
        {
            case TimerMode::Milliseconds : {
                return std::chrono::duration_cast<milliseconds>(clock::now() - _startTime ).count();
            }
            case TimerMode::Seconds : {
                return std::chrono::duration_cast<seconds>(clock::now() - _startTime ).count();
            }
            default:
                return -1;
        }
    }
    void reset() noexcept {
        _startTime = clock::now();
    }

private:
    TimerMode   _mode;
    time_t      _startTime;
};

template<typename T>
long getAverageSortingTime(std::function<void(std::vector<T>)> sortingFunc,
                           Timer::TimerMode timerMode = Timer::TimerMode::Seconds,
                           unsigned vecSize = 10'000,
                           unsigned repetitionTime = 100)
{
    long averageTime = 0;
    Timer execTimer(timerMode);
    for (int i = 0; i < repetitionTime; i++) {
        auto vec = generateRandomVec<int>(vecSize, -1000, 1000);
        execTimer.reset();
        sortingFunc(vec);
        /// (a1 + a2 + a3) / n = a1/n + a2/n + a3/n;
        /// otherwise in (a1 + a2 + a3) will be an overflow (i guess)
        averageTime += execTimer.elapsed() / repetitionTime;
    }
    return averageTime;
}

int main() {

    const int VECTOR_TEST_SIZE  = 100'000;
    const int REPEAT_COUNT      = 10;
    const Timer::TimerMode MODE = Timer::TimerMode::Milliseconds;
    std::cout   << "RUN TEST FOR DIFFERENT SORTS; VECTOR SIZE IS "
                << VECTOR_TEST_SIZE << "; REPEATING TEST SIZE IS " <<  REPEAT_COUNT << "\n";


    std::cout << "Quick sort average time is " << getAverageSortingTime<int>(sorts::quick_sort<int>,
                                                                             MODE, VECTOR_TEST_SIZE, REPEAT_COUNT) << std::endl;
    std::cout << "Merge sort average time is " << getAverageSortingTime<int>(sorts::merge_sort<int>,
                                                                             MODE, VECTOR_TEST_SIZE, REPEAT_COUNT) << std::endl;;
    std::cout << "Bubble sort sort average time is " << getAverageSortingTime<int>(sorts::bubble_sort<int>,
                                                                                    MODE, VECTOR_TEST_SIZE, REPEAT_COUNT) << std::endl;;
    std::cout << "Insertion sort average time is " << getAverageSortingTime<int>(sorts::insertion_sort<int>,
                                                                             MODE, VECTOR_TEST_SIZE, REPEAT_COUNT) << std::endl;

    auto vec = generateRandomVec<int>(VECTOR_TEST_SIZE, -1000, 1000);
    Timer t;
    std::sort(std::begin(vec), std::end(vec));
    /// my quick sort is faster than std::sort
    std::cout << "std::sort time is " << t.elapsed();

    return 0;

}