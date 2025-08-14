#! /bin/bash

mkdir -p images

# Build all [0-18]
if [[ $# == 0 ]]; then
start=1
end=18

# Build specific
elif [[ $# == 1 ]]; then
start=$1
end=$1

# Build range [$1 - $2]
else
start=$1
else=$2

fi

for obj in $(seq -f "%02g" "$start" "$end"); do
    sed -i "s/object[[:digit:]]*/object$obj/" asm/crt0.s
    make
    mv riscv32-img "images/object$obj-img"
done
