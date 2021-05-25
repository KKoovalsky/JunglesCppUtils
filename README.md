# Jungles CPP utilities

This repo contains C++ utilities that help me develop code faster, by wrapping common entities into those reusable
classes.

C++17 is required.

Explore `test` directory to find out how to use the utilities.

## jungles::assign_callback

Allows to assign a lambda function to a plain C pointer, e.g.:

```
static unsigned (*plain_c_pointer)(char, float);

plain_c_pointer = jungles::assign_callback([](char, float) -> unsigned { return 5; });

auto r{(*plain_c_pointer)('c', 32.2)};

std::cout << r << std::endl; // Prints '5'
```

## jungles::overload

It is taken from the Bartłomiej Filipek's blog: 
[Variant and Overload](https://www.bfilipek.com/2018/06/variant.html#overload)

## Algorithms 

Defined in [jungles/algorithm.hpp](jungles/algorithm.hpp).

### jungles::copy

Is the same as `std::copy`, but the iterators may have different types, e.g. the end iterator can be a sentinel.

## jungles::calculate_correlation_function

Calculates correlation function for `num_offsets` of the `signal`, with reference to `pattern`. Uses Pearson 
correlation coefficient formula for each offset.

## jungles::singleton

CRTP utility to be used by class if one wants to indicate that the class is a Singleton - only one instance at a time
can be running:

```
class USBDriver : public jungles::Singleton<USBDriver>
{
    // ...
};

{
    USBDriver{};
    USBDriver{}; // Will throw 
}

{

    {
        USBDriver{};
    }

    {
        USBDriver{}; // OK
    }
}

```
