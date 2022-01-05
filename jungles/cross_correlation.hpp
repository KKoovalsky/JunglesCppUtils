/**
 * @file        cross_correlation.hpp
 * @brief       Implements Cross-correlation function calculation.
 * @author      Kacper Kowalski - kacper.s.kowalski@gmail.com
 */
#ifndef CROSS_CORRELATION_HPP
#define CROSS_CORRELATION_HPP

#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace jungles
{

namespace detail
{

template<typename ItSignalBegin, typename ItSignalEnd, typename ItPatternBegin, typename ItPatternEnd>
inline auto correlation_product(ItSignalBegin signal_begin,
                                ItSignalEnd signal_end,
                                ItPatternBegin pattern_begin,
                                ItPatternEnd pattern_end)
{
    using SignalUnderlyingType = typename ItSignalBegin::value_type;

    if (std::distance(signal_begin, signal_end) > std::distance(pattern_begin, pattern_end))
        throw std::runtime_error("Signal cannot be longer than pattern");

    SignalUnderlyingType result{std::inner_product(signal_begin,
                                                   signal_end,
                                                   pattern_begin,
                                                   static_cast<SignalUnderlyingType>(0),
                                                   std::plus<SignalUnderlyingType>{},
                                                   std::multiplies<SignalUnderlyingType>{})};
    return result;
}

} // namespace detail

template<typename ItSignalBegin, typename ItSignalEnd, typename ItPatternBegin, typename ItPatternEnd>
std::vector<float> calculate_correlation_function(ItSignalBegin signal_begin,
                                                  ItSignalEnd signal_end,
                                                  ItPatternBegin pattern_begin,
                                                  ItPatternEnd pattern_end,
                                                  unsigned num_offsets)
{
    auto signal_autocorrelation_factor{detail::correlation_product(signal_begin, signal_end, signal_begin, signal_end)};
    auto pattern_autocorrelation_factor{
        detail::correlation_product(pattern_begin, pattern_end, pattern_begin, pattern_end)};

    auto calculate_cross_correlation_product{[=]<typename BegIt, typename EndIt>(BegIt beg_it, EndIt end_it) {
        auto cross_correlation_product{detail::correlation_product(beg_it, end_it, pattern_begin, pattern_end)};
        return cross_correlation_product / std::sqrt(signal_autocorrelation_factor * pattern_autocorrelation_factor);
    }};

    std::vector<float> resulting_correlation_function;
    resulting_correlation_function.reserve(num_offsets);
    auto result_it{std::back_inserter(resulting_correlation_function)};

    auto past_last_offset_it{std::next(signal_begin, num_offsets)};
    for (auto signal_it{signal_begin}; signal_it != past_last_offset_it; ++signal_it)
        *result_it++ = calculate_cross_correlation_product(signal_it, signal_end);

    return resulting_correlation_function;
}

} // namespace jungles

#endif /* CROSS_CORRELATION_HPP */
