/**
 * @file	algorithm.hpp
 * @brief       Some algorithm implementations from std:: that are a little bit refined.
 * @author	Kacper Kowalski - kacper.s.kowalski@gmail.com
 */
#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace jungles
{

template<class InputIt1, class InputIt2, class OutputIt>
OutputIt copy(InputIt1 first, InputIt2 last, OutputIt d_first)
{
    while (first != last)
    {
        *d_first++ = *first++;
    }
    return d_first;
}

}; // namespace jungles

#endif /* ALGORITHM_HPP */

