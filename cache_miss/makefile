PFX=riscv32-unknown-elf
CC=$(PFX)-gcc
LD=$(PFX)-ld
AS=$(PFX)-as

LIB=-L. -lfj
INCLUDE=inc

LDFLAGS=--gc-sections -Triscv32-virt.ld
CFLAGS=-I$(INCLUDE) -O0 -g3 -gdwarf-2 -ffreestanding -nostartfiles \
	-nostdlib -nodefaultlibs -fno-tree-loop-distribute-patterns \
	-fno-builtin

OBJDIR=obj
OBJECTS=$(patsubst src/%.c,${OBJDIR}/%.o, $(wildcard src/*.c))
ASMOBJS=$(patsubst asm/%.s,${OBJDIR}/%.o, $(wildcard asm/*.s))

all: libfj.a riscv32-img

rv32-abi: CFLAGS+=-march=rv32g -mabi=ilp32d
rv32-abi: all

$(OBJECTS): ${OBJDIR}/%.o : src/%.c | ${OBJDIR}
	$(CC) $(CFLAGS) -c $< -o $@

$(ASMOBJS): ${OBJDIR}/%.o : asm/%.s | ${OBJDIR}
	$(AS) $< -o $@

${OBJDIR}:
	mkdir ${OBJDIR}

libfj.a: $(OBJECTS) $(ASMOBJS)
	ar -rcs $@ $(OBJECTS) $(ASMOBJS)

.PHONY: riscv32-img
riscv32-img: $(OBJECTS)
	$(LD) $(LDFLAGS) $(LIB) -o $@

clean:
	rm -rf *-img
	rm -rf ${OBJDIR}
	rm -rf cache.log
	rm -rf data.csv
	rm -rf cache-logs
	rm -rf images
