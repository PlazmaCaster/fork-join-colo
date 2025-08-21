#! /bin/bash

function usage() {
    cat <<EOF
    $(basename $0)                      # Build all executable [1-18]
    $(basename $0)  <executable>        # Build specific executable
    $(basename $0)  <start> <finish>    # Build a range

EOF
    exit 1;
}

number_match='^[0-9]+$'
SRC="../cache_miss"

mkdir -p "../images"

# TODO: come up with a better way to build instead of just numbers
# TODO: Building with specific cache size in linker should go here

# Build all [0-18]
if [[ $# == 0 ]]; then
    start=1
    end=18

# Build specific
elif [[ $# == 1 ]]; then
    if ! [[ $1 =~ $number_match ]]; then
        usage
    fi

    start=$1
    end=$1

# Build range [$1 - $2]
elif [[ $# == 2 ]]; then
    if ! [[ $1 =~ $number_match && $2 =~ $number_match ]]; then
        usage
    fi

    start=$1
    else=$2

else
    usage
fi

for obj in $(seq -f "%02g" "$start" "$end"); do
    sed -i "s/object[[:digit:]]*/object$obj/" "$SRC/asm/crt0.s"
    make -C "$SRC"
    mv "$SRC/riscv32-img" "../images/object$obj-img"
done
