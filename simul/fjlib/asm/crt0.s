
	#  The following assembly goes into the .init section
	.section .init, "ax"
	#  The following exposes the symbol to the linker
	.global _start

_start:
	.cfi_startproc
	.cfi_undefined ra

	li t0, 1 << 13		# FPU enable bit
	csrw mstatus, t0	# Enable the FPU

	add t0, zero, 0x8	# set enable MSI bit
	csrrw zero, mie, t0	# enable interrupts

	csrr t0, mhartid	# t0 = current hartid
	# Multiply by the hartid by __GLOBAL_BYTES (1024) store in t1
	add t1, zero, 1024
	mul t1, t0, t1		# t1 = hartid * 1024

	.option push
	.option norelax
	# gp (global pointer) refers to the start of global data
	# structures and variables
	la gp, __global_pointer_start
	# Increment to the next global pointer block
	add gp, gp, t1
	.option pop
	# store the hart id at the location of gp
	sw t0, (gp)

	# Calculate the new stack top for the given hartid
	# This should be more elegant, for now, let's have a 4MB stack
	# per core
	# Load the 4 megabyte word into t0
	add t1, zero, 8
	add t2, zero, 20
	sll t2, t1, t2
	# t0 -- still holds the hartid
	mul t2, t2, t0

    li t6, 0x80100000   # Addr chosen arbitrarily to store stack offset
    lw t5, 0(t6)        # Grabbing offset

	# la sp, __stack_top
	la sp, __stack_top
    sub sp, sp, t5      # Adjusting __stack_top by offset
	sub sp, sp, t2
	# add sp, t2, zero
	add s0, sp, zero
	jal zero, object09
	.cfi_endproc
