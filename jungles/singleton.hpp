/**
 * @file	singleton.hpp
 * @brief	Implements a CRTP component that objects can use to mark themselves singletons.
 * @author	Kacper Kowalski - kacper.s.kowalski@gmail.com
 */
#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <stdexcept>

namespace jungles
{

template<typename T>
class Singleton
{
  public:
    Singleton()
    {
        if (is_instance_created)
            throw std::runtime_error{"One instance already created"};

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
