#!/bin/bash
make -C build 
num_runs=20

set -e

for i in $(seq 1 $num_runs); do
    ./build/main $RANDOM &
    wait $!
done