#include "Chronometer.hpp"

/**
 *  Chronometer class template methods implementation
 */
template <class Clock>
void Chronometer<Clock>::start()
{
    m_current_range = Time_Range(Clock::now());
}



template <class Clock>
void Chronometer<Clock>::stop()
{
    m_current_range.stop_point = Clock::now();
    m_ranges.emplace_back(std::move(m_current_range));
}



template <class Clock>
void Chronometer<Clock>::reset()
{
    m_ranges.clear();
}



template <class Clock>
void Chronometer<Clock>::restart()
{
    reset();
    start();
}



template <class Clock>
bool Chronometer<Clock>::is_counting() const
{
    return m_current_range.stop_point == invalid_time;
}



template <class Clock>
auto Chronometer<Clock>::read() const -> Chronometer<Clock>::Duration_Wrapper
{
    Duration_Wrapper wrapper;

    for (auto const& [ start, stop ] : std::as_const(m_ranges)) {
        wrapper.duration += stop - start;
    }
    return wrapper;
}



/**
 *  Nested class "Time_Range"
 */
template <class Clock>
Chronometer<Clock>::Time_Range::Time_Range() noexcept
    : start_point   {}
    , stop_point    {invalid_time}
{
}



template <class Clock>
Chronometer<Clock>::Time_Range::Time_Range(
    Chronometer<Clock>::time_point_t starting_point
) noexcept
    : start_point   {starting_point}
    , stop_point    {invalid_time}
{
}



/**
 *  Nested classe "Duration_Wrapper"
 */
template <class Clock>
Chronometer<Clock>::Duration_Wrapper::operator typename Clock::duration() const
{
    return duration;
}



template <class Clock>
typename Clock::duration Chronometer<Clock>::Duration_Wrapper::as_stl_duration() const
{
    return duration;
}



template <class Clock>
float Chronometer<Clock>::Duration_Wrapper::as_seconds() const
{
    return std::chrono::duration_cast<
        std::chrono::duration<float, std::ratio<1,1>>
    >(duration).count();
}



template <class Clock>
float Chronometer<Clock>::Duration_Wrapper::as_milliseconds() const
{
    return std::chrono::duration_cast<
        std::chrono::duration<float, std::milli>
    >(duration).count();
}



template <class Clock>
std::int64_t Chronometer<Clock>::Duration_Wrapper::as_microseconds() const
{
    return std::chrono::duration_cast<
        std::chrono::duration<std::int64_t, std::micro>
    >(duration).count();
}



template <class Clock>
std::int64_t Chronometer<Clock>::Duration_Wrapper::as_nanoseconds() const
{
    return std::chrono::duration_cast<
        std::chrono::duration<std::int64_t, std::nano>
    >(duration).count();
}



template <class Clock>
std::int64_t Chronometer<Clock>::Duration_Wrapper::as_picoseconds() const
{
    return std::chrono::duration_cast<
        std::chrono::duration<std::int64_t, std::pico>
    >(duration).count();
}
