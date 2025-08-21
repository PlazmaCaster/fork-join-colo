_QEMU=$(command -v qemu-system-riscv32)
_PLUGIN=$(dirname $(dirname ${_QEMU}))/contrib/plugins/libcache.so
QEMU=${QEMU:-${_QEMU}}
PLUGIN=${PLUGIN:-${_PLUGIN}}

opts=-nographic 	# disable the graphical output
opts+=" -machine virt"	# the RISC-V simulated machine
opts+=" -bios none"	# Prevent the OpenSBI bios from being loaded
opts+=" -m 128M"	# 128 megabytes of memory
opts+=" -smp 1"		# The number of cores (harts)
# The -gdb option does not work, I do not know why
# opts+=" -gdb tcp:4321"	# Specify the GDB remote port
# opts+=" -s"
# opts+=" -S"         # Connect GDB to qemu

# libcache enable and parameters
opts+=" --plugin ${PLUGIN}"
opts+=",dcachesize=$3,dassoc=2,dblksize=32"
opts+=',icachesize=16384,iassoc=2,iblksize=32'
opts+=' -d plugin'
opts+=' -D cache.log'
opts+=" -device loader,addr=0x80100000,data=$2,data-len=4"
opts+=" -kernel $1"	# the kernel to add


echo "Invoking: ${QEMU} ${opts}"
${QEMU} ${opts}
