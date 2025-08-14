#! /bin/bash

LD_FILE=riscv32-virt.ld

usage() {
    echo "usage: $(basename $0) log_directory kernel"
}

if [[ $# != 2 ]]; then
    usage;
    exit 1;
fi

LOG_DIR="cache-logs/$1"
KERNEL="$2"

CACHE_SZ=`grep "CBYTES =" "$LD_FILE" | awk '{print $3}' | sed 's/0x//' | sed 's/;//'`
CACHE_SZ="$((16#$CACHE_SZ))"

# Place to save cache-logs
mkdir -p "$LOG_DIR"

# Increments of 4
for OFFSET in $(seq 0 4 $CACHE_SZ); do

    HEX_OFFSET=$(printf "%04x" $OFFSET)
    QEMU_PARAM="0x0000$HEX_OFFSET"

    # Pass offset to qemu
    ../../../bin/qemu.sh "$KERNEL" "$QEMU_PARAM"

    # Expensive to do this...
    cp cache.log "$LOG_DIR/offset-$HEX_OFFSET.log"
done
