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
