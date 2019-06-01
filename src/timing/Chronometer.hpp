/**
 *  class Chronometer
 *
 *  simple time counter.
 *
 *  This class offers the behaviour of a classic hand chronometer for sport.
 *
 *  - start:    launches the time count. It resumes where it last stopped,
 *              the counter is not reset.
 *
 *  - stop:     stops the time counter.
 *
 *  - reset:    sets the counter back to 0.
 *
 *  - restart:  resets the counter and starts counting.
 *
 */
#pragma once
#include <chrono>
#include <vector>

template <class Clock = std::chrono::high_resolution_clock>
class Chronometer
{
public:
    using clock_type    = Clock;

private:
    using duration_t    = typename clock_type::duration;
    using time_point_t  = typename clock_type::time_point;

    //* Time-storage data-structure.
    struct Time_Range;

    //* Wrapper for read method's return value
    struct Duration_Wrapper;

    //* Data fields
    std::vector<Time_Range> m_ranges            {};
    Time_Range              m_current_range     {};

    static constexpr auto   invalid_time        {std::chrono::nanoseconds(-1)};

public:
    void start();
    void stop();
    void reset();
    void restart();

    bool is_counting() const;
    Duration_Wrapper read() const;

};


//* Nested structures
template <class Clock>
struct Chronometer<Clock>::Time_Range
{
    time_point_t start_point;
    time_point_t stop_point;

    Time_Range() noexcept;
    Time_Range(time_point_t)  noexcept;
    Time_Range(Time_Range&&) noexcept                   = default;
    Time_Range& operator=(Time_Range&&) noexcept        = default;
    Time_Range(const Time_Range&) noexcept              = delete;
    Time_Range& operator=(const Time_Range&) noexcept   = delete;
};



template <class Clock>
struct Chronometer<Clock>::Duration_Wrapper
{
    //* Field
    typename Clock::duration duration {std::chrono::nanoseconds(0)};

    //* Conversion methods (to STL type)
    operator     typename Clock::duration() const;
    duration_t   as_stl_duration() const;

    //* Conversion methods (to numeric type)
    float        as_seconds() const;
    float        as_milliseconds() const;
    std::int64_t as_microseconds() const;
    std::int64_t as_nanoseconds() const;
    std::int64_t as_picoseconds() const;

};



//* Implementation
#include "Chronometer.impl.hpp"
