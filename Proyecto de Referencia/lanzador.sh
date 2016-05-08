#!/bin/bash

# Lanza varios procesos

for _ in $(seq 100); do
    ./c/prog_a &
    sleep 0.016
done

