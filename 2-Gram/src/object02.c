#include "objects.h"
#include "rv.h"

/**
 * @file object02.c
 *
 * Port of bsort100 from the MRTC benchmarks
 */


/* MDH WCET BENCHMARK SUITE. File version $Id: bsort100.c,v 1.1.1.1 2007-12-11 15:22:55 puaut Exp $ */

/* BUBBLESORT BENCHMARK PROGRAM:
 * This program tests the basic loop constructs, integer comparisons,
 * and simple array handling of compilers by sorting an array of 10 randomly
 * generated integers.
 */

#define FALSE 0
#define TRUE 1
#define NUMELEMS 100
#define MAXDIM   (NUMELEMS+1)

int             Seed;
int             factor;
void            BubbleSort(/*int Array[]*/);
void            Initialize(/*int Array[]*/);

void object(2) object02(void) {
	int Array[MAXDIM];
	Initialize(Array);
    BubbleSort(Array);
    EXIT;
}

void object(2) Initialize(int Array[])
{
	int  Index, fact;

	factor = -1;
	fact = factor;
	for (Index = 1; Index <= NUMELEMS; Index ++) {
		Array[Index] = Index * fact/* * KNOWN_VALUE*/;
	}
}

object(2) void BubbleSort(int Array[])
/*
 * Sorts an array of integers of size NUMELEMS in ascending order.
 */
{
   int Sorted = FALSE;
   int Temp, Index, i;

   for (i = 1; i <= NUMELEMS - 1; i++) {
           Sorted = TRUE;
           for (Index = 1; Index <= NUMELEMS - 1;
                Index++) {
		   if (Index > NUMELEMS - i)
			   break;
		   if (Array[Index] > Array[Index + 1]) {
			   Temp = Array[Index];
			   Array[Index] = Array[Index + 1];
			   Array[Index + 1] = Temp;
			   Sorted = FALSE;
		   }
           }

           if (Sorted)
		   break;
   }
}
