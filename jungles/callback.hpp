/**
 * @file	callback.hpp
 * @brief	Assigns a callback to C function pointer.
 * @author	Kacper Kowalski - kacper.kowalski@hum-systems.com
 */
#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include "function_traits.hpp"

#include <functional>

namespace jungles
{

template<typename Callable>
struct cfunction_wrapper
{
    using Traits = jungles::function_traits<Callable>;

    cfunction_wrapper(Callable callback)
    {
        dispatched_callback = callback;
    }

    using Signature = typename Traits::signature;
    static inline std::function<Signature> dispatched_callback;

    using ReturnType = typename Traits::result_type;
    template<typename... Args>
    static inline ReturnType dispatcher(Args... args)
    {
        return dispatched_callback(args...);
    }
};

template<typename T>
auto assign_callback(T&& t)
{
    using Traits = jungles::function_traits<T>;
    using Signature = typename Traits::signature;

    cfunction_wrapper c{std::forward<T>(t)};
    Signature* matching_function_pointer{c.dispatcher};
    return matching_function_pointer;
}

} // namespace jungles

#endif /* CALLBACK_HPP */
