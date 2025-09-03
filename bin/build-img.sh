#! /bin/bash

function usage() {
    cat <<EOF
    $(basename $0)                      # Build all images based off src
    $(basename $0) <img1> ...           # Build all specified images

    $(basename $0) -l                   # Relink all images
    $(basename $0) -l <img1> ...        # Relink all specified images

    Used to build the riscv32 images. Arguments passed are entry points to the
    image and must have a corresponding .c file.
EOF
    exit 1;
}

DIR="./cache_miss"
ASM="${DIR}/asm"
SRC="${DIR}/src"
IMG="./images"
LIB="./lib"             # So we don't have to recompile each time

mkdir -p ${IMG}
mkdir -p ${LIB}

# TODO: come up with a better way to build instead of just numbers
# TODO: Building with specific cache size in linker should go here

# Build all [0-18]
if [[ $# == 0 ]]; then
    for exe in ${SRC}/*; do
        target=`basename ${exe} .c`
        sed -i "s/jal zero, .*/jal zero, ${target}/" "$ASM/crt0.s"

        make -C ${DIR}

        # Initial creation of images
        mv "${DIR}/riscv32-img" "${IMG}/${target}-img"
        mv "${DIR}/libfj.a" "${LIB}/lib${target}.a"
    done

else
    while [[ ! -z $1 ]]; do
        target=$1

        if [[ -f ${SRC}/${target}.c ]]; then
            echo "FILE EXISTS"
            sed -i "s/jal zero, .*/jal zero, ${target}/" "$ASM/crt0.s"
        else
            echo "Error: ${SRC}/${target}.c does not exists"
        fi
        shift
    done
fi

# Build specific
# elif [[ $# == 1 ]]; then
#     if ! [[ $1 =~ $number_match ]]; then
#         usage
#     fi

#     start=$1
#     end=$1

# # Build range [$1 - $2]
# elif [[ $# == 2 ]]; then
#     if ! [[ $1 =~ $number_match && $2 =~ $number_match ]]; then
#         usage
#     fi

#     start=$1
#     else=$2

# else
#     usage
# fi

# for obj in $(seq -f "%02g" "$start" "$end"); do
#     sed -i "s/object[[:digit:]]*/object$obj/" "$SRC/asm/crt0.s"
#     make -C "$SRC"
#     mv "$SRC/riscv32-img" "${IMG}/object$obj-img"
# done
