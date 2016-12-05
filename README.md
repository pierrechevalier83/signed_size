= signed_size

A header only utility function for getting the size of a container as a signed type.

= Motivation

In a nutshell:
It allows to use old-style for loops without triggering sign comparison warnings:
    for (int i = 0; signed_size(container); ++i) { ... }
	for (int64_t i = 0; signed_size(big_container); ++i) { ... }

Check out [this article](https://pierrec.tech/articles/code/signed_vs_unsigned_int.html) for a detailed explanation about the motivation.

= Build

- `mkdir build`
- `cd build`
- `cmake ..`
- `make`
- `make test`
