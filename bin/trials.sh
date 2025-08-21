#! /bin/bash

### Defaults
m=1024
r=100
s=0
t=16384

SRC="../cache_miss"
LD_FILE="$SRC/riscv32-virt.ld"
RANGE=true
SAVE=false
HEADER="Offset,Data Miss"

CACHE_SZ=`grep "CBYTES =" $LD_FILE | sed 's/CBYTES = 0x//' | sed 's/;.*//'`
CACHE_SZ=$((16#${CACHE_SZ}))

function usage() {
    cat <<EOF
    $(basename $0) <image> [options]

    Runs the provided RISC-V image through QEMU and finds the worst number of
    data cache misses given the passed in parameters. Defaults to 100 runs to
    calculate average. If [-s] option is not provided it will run through the
    entire search space [0 - image_cache).

    Options:
    -h                  Display this message
    -m <cache>          Sets the cache size provided by the linker script, in
                        bytes, and re-links. (WIP)
                        [default: 1024]
    -o <file>           Saves output in CSV format to <file>
    -r <runs>           Number of times to run specified offset. Minimum of one
                        [default: $r]
    -s <stack_offset>   Set stack's offset; must be divisible by four.
                        [default: $s]
    -t <cache>          Set TCG plugin dcachesize to <cache>, in bytes. Must be
                        divisble by 32 (dcache block size)
                        [default: $t]
EOF
    exit 1
}

# TODO: Don't rebuild all of it, just the ones you need
function edit_linker_cache() {
    cache="$(printf "%04x" $1)"

    sed -i "s/CBYTES = 0x.*;/CBYTES = 0x${cache};/" "$LD_FILE"
    make -C "$SRC"
    mv "$SRC/riscv32-img" $2
}


while getopts "h:m:o:r:s:t:" opt; do
    case "${opt}" in
        # TODO: Maybe move changing cache in ld file to a different script
        # m)
        #     m=${OPTARG}
        #     [ $m -lt 0 ] \
        #     && echo "Monolith cache must be non-negative; $m found"\
        #     && exit 1
        #     ;;
        o)
            o=${OPTARG}
            [ -z $o ] \
            && echo "No output file provided"\
            && exit 1

            SAVE=true
            ;;
        r)
            r=${OPTARG}
            [ $r -lt 1 ] \
            && echo "Number of runs must be at least 1; $r found"\
            && exit 1
            ;;
        s)
            s=${OPTARG}
            [ $s -lt 0 ]\
            && echo "Stack offset cannot be negative: $s found"\
            && exit 1

            [ $((s % 4)) -ne 0 ]\
            && echo "Stack offset must be divisible by 4: $s found"\
            && exit 1

            RANGE=false
            ;;
        t)
            t=${OPTARG}
            [ $t -lt 0 ]\
            && echo "TCG dcachesize must be non-negative; $t found"\
            && exit 1

            [ $((t % 32)) -ne 0 ]\
            && echo "TCG dcachesize must be divisible by 32: $t found"\
            && exit 1
            ;;
        *)
            usage
            ;;
    esac
done
shift "$((OPTIND-1))"

if [[ $# != 1 ]]; then
    echo "Missing kernel image"
    exit 1
elif [[ ! -f $1 ]]; then
    echo "Could not find kernel image: $1"
    exit 1
fi

echo "Running kernel image: $1" >&2
echo "Image Cache Size    : $m bytes" >&2
# echo "Image Cache Size    : $CACHE_SZ bytes" >&2
echo "Runs per offset     : $r" >&2
echo "TCG dcachesize      : $t bytes" >&2
if [ $RANGE = true ]; then
    echo "Running entire search space" >&2
else
    HEX=$(printf "%08x" $s)
    echo "Stack Offset        : $s (0x$HEX)" >&2
fi
if [ $SAVE = true ]; then
echo "Saving to           : $o" >&2
fi
echo "-------------------------------------------------------------------------"

# See TODO
# Edit the linker script to use the cache size
# edit_linker_cache "$m" "$1"

IMAGE="$1"
# CACHE_SZ=$((16#${m}))


if [[ -z $1 ]]; then
    usage
fi

CSV=$(
    # Go through whole search space
    if [ $RANGE = true ]; then
        # Increments of 4

        echo "$HEADER"
        for OFFSET in $(seq 0 4 $CACHE_SZ); do
            HEX_OFFSET=$(printf "%08x" $OFFSET)
            QEMU_PARAM="0x$HEX_OFFSET"

            MAX=0

            printf "Curent offset: ${QEMU_PARAM}\n" >&2
            for i in $(seq 1 $r); do

                # Pass offset to qemu
                ./qemu.sh "$IMAGE" "$QEMU_PARAM" "$t" > /dev/null

                DMISS=`head cache.log | awk 'NR == 2 {print $3}'`

                if [[ $MAX -lt $DMISS ]]; then
                    MAX=$DMISS
                fi
            done
            echo "${QEMU_PARAM},${MAX}"
        done

    # Go through one specific offset
    else
        OFFSET="$(printf "%08x" $s)"
        MAX=0

        echo "$HEADER"


        for i in $(seq 1 $r); do
            printf "Run: $i\n" >&2

            ./qemu.sh "$IMAGE" "0x$OFFSET" "$t" > /dev/null
            DMISS=`head cache.log | awk 'NR == 2 {print $3}'`
            if [[ $MAX -lt $DMISS ]]; then
                MAX=$DMISS
            fi
        done
        echo "0x${OFFSET},${MAX}"

    fi
)

echo "-------------------------------------------------------------------------"
echo "$CSV" | column -t -s ','

if [ $SAVE = true ]; then
    echo "$CSV" > "$o"
fi
