#ifndef __RV_H__
#define __RV_H__

/**
 * @file rv.h
 *
 * RISC-V macros and functions to aid in interacting with the
 * SOC
 */

/**
 * @define MSWI_BASE
 * The memory mapped location of the MSI 
 */ 
#define MSWI_BASE 0x2000000

/**
 * @define MSIP
 *
 * Provides the memory location for the nth core.
 *
 * MSIP(0) -- MSI location for core 0
 * MSIP(1) -- MSI location for core 1
 * ...
 * MSIP(4095) -- Max core
 */
#define MSIP(n) (*(int *)(MSWI_BASE + (n * 4)))

/**
 * @define READ_GP
 * Reads the GP register into a variable
 *
 * var is intended to be an integer pointer
 *
 int *value;
 READ_GP(value);    -- value now has the contents of GP
 *
 * XXX
 * Currently only works if var is a register
 * XXX
 */
#define READ_GP(var) asm volatile( "add %0, gp, zero" : "=r" (var))


/**
 * @define EXIT
 *
 * Causes the processor to halt and exit the QEMU emulator. If *any*
 * core executes this instruction the simulator will stop.
 *
 * XXX
 * Exit codes (success or failure) have not been implemented, only
 * reports success.
 * XXX
 *
 * XXX
 * Unsure why this works it, the address is magic, and the 0x3333
 * number is also magic
 * XXX
 */
#define EXIT do {						\
	unsigned int *__DMA_EXIT = (unsigned int *) 0x100000;	\
        *__DMA_EXIT = 0x3333;					\
} while(0)


/**
 * @define INT_PEND_CLEAR
 *
 * Clears any pending interrupts for hart given by core_id
 *
 * XXX
 * This should not require a core_id, more importantly it should not
 * be there as a parameter to invite a coding mistake.
 */
#define INT_PEND_CLEAR(core_id) do {		\
	asm("add t0, zero, 0x0\n\t"		\
	    "csrrw zero, mip, t0"		\
	    :					\
	    :					\
	    : "t0");				\
	MSIP(core_id) = 0;			\
} while(0)

/**
 * @define WFI
 *
 * Wait For Interrupt -- halts this core until an interrupt is raised.
 */
#define WFI asm("wfi")

/**
 * @define PADOP
 *
 * Adds a 32 bit padding instruction
 */
#define PADOP asm("add a0,zero,zero")

#endif /* __RV_H__ */

