#! /bin/bash

function usage() {
    cat <<EOF
    $(basename $0)                      # Build all monoliths [1-18]
    $(basename $0)  <monolith>          # Build specific monolith
    $(basename $0)  <start> <finish>    # Build a range

EOF
    exit 1;
}

number_match='^[0-9]+$'

mkdir -p images

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
    sed -i "s/object[[:digit:]]*/object$obj/" asm/crt0.s
    make
    mv riscv32-img "images/object$obj-img"
done
