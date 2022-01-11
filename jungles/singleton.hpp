/**
 * @file	singleton.hpp
 * @brief	Implements a CRTP component that objects can use to mark themselves singletons.
 * @author	Kacper Kowalski - kacper.s.kowalski@gmail.com
 */
#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <exception>
#include <stdexcept>

namespace jungles
{

template<typename T, typename Exception = std::exception>
class Singleton
{
  public:
    Singleton()
    {
        if (is_instance_created)
            throw Exception{};

        is_instance_created = true;
    }

    ~Singleton()
    {
        is_instance_created = false;
    }

  private:
    static inline bool is_instance_created{false};
};

}; // namespace jungles

#endif /* SINGLETON_HPP */
