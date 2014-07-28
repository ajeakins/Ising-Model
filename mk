#! /bin/env bash

mkdir -p build && cd build && cmake .. && make -j 6 && cp bind/libising_model.so bind/ising_model.so