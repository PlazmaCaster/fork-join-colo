#! /bin/bash

# TODO: Have it read from riscv32-virt.ld to get the actual cache size instead
# of whatever this is
CACHE_SZ=0400
CACHE_SZ=$((16#$CACHE_SZ))

# Default to test if it works
if [[ $# == 0 ]]; then
    ../../../bin/qemu.sh riscv32-img 0x00000000
    exit
fi

# Place to save cache-logs
mkdir -p cache-logs/$1
SAVES="cache-logs/$1"

# Increments of 4
for OFFSET in $(seq 0 4 $CACHE_SZ); do

    HEX_OFFSET=$(printf "%04x" $OFFSET)

    QEMU_PARAM="0x0000$HEX_OFFSET"

    # Pass offset to qemu
    ../../../bin/qemu.sh $2 "$QEMU_PARAM"
    # echo $HEX_OFFSET
    # Expensive to do this...
    # cp cache.log "$SAVES/offset-$HEX_OFFSET.log"
done
