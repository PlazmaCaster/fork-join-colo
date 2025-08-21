#include "objects.h"
#include "rv.h"

/**
 * @file object09.c
 *
 * Port of matmult from the MRTC benchmarks
 */
/* MDH WCET BENCHMARK SUITE. File version $Id: matmult.c,v 1.1.1.1 2007-12-11 15:22:56 puaut Exp $ */

/* matmult.c */
/* was mm.c! */

/*----------------------------------------------------------------------*
 * To make this program compile under our assumed embedded environment,
 * we had to make several changes:
 * - Declare all functions in ANSI style, not K&R.
 *   this includes adding return types in all cases!
 * - Declare function prototypes
 * - Disable all output
 * - Disable all UNIX-style includes
 *
 * This is a program that was developed from mm.c to matmult.c by
 * Thomas Lundqvist at Chalmers.
 *----------------------------------------------------------------------*/

/* Changes:
 * JG 2005/12/12: Indented program.
 */

#define UPPSALAWCET 1


/* ***UPPSALA WCET***:
   disable stupid UNIX includes */
#ifndef UPPSALAWCET
#include <sys/types.h>
#include <sys/times.h>
#endif

/*
 * MATRIX MULTIPLICATION BENCHMARK PROGRAM:
 * This program multiplies 2 square matrices resulting in a 3rd
 * matrix. It tests a compiler's speed in handling multidimensional
 * arrays and simple arithmetic.
 */

#define UPPERLIMIT 20

typedef int     matrix[UPPERLIMIT][UPPERLIMIT];

int             Seeds;
matrix          A, B, Res;

#ifdef UPPSALAWCET
/* Our picky compiler wants prototypes! */
void            Multiply(/*matrix A, matrix B, matrix Res*/);
void            InitSeeds(void);
void            Test(/*matrix A, matrix B, matrix Res*/);
/*void            Initialize(matrix Array);*/
void            InitializeA(/*matrix Array*/);
void            InitializeB(/*matrix Array*/);
int             RandomInteger(void);
#endif

void object(9)
object09(void)
{
	InitSeeds();
/* ***UPPSALA WCET***:
   no printing please! */
#ifndef UPPSALAWCET
	printf("\n   *** MATRIX MULTIPLICATION BENCHMARK TEST ***\n\n");
	printf("RESULTS OF THE TEST:\n");
#endif
    Test(/*ArrayA, ArrayB, ResultArray*/);
    EXIT;
}


void object(9)
InitSeeds(void)
/*
 * Initializes the Seeds used in the random number generator.
 */
{
	/*
	 * ***UPPSALA WCET***: changed Thomas Ls code to something simpler.
	 * Seeds = KNOWN_VALUE - 1;
	 */
	Seeds = 0;
}


void object(9)
Test(/*matrix A, matrix B, matrix Res*/)
/*
 * Runs a multiplication test on an array.  Calculates and prints the
 * time it takes to multiply the matrices.
 */
{
#ifndef UPPSALAWCET
	long            StartTime, StopTime;
	float           TotalTime;
#endif

	InitializeA(/*A*/);
	InitializeB(/*B*/);

	/* ***UPPSALA WCET***: don't print or time */
#ifndef UPPSALAWCET
	StartTime = ttime();
#endif

	Multiply(/*A, B, Res*/);

	/* ***UPPSALA WCET***: don't print or time */
#ifndef UPPSALAWCET
	StopTime = ttime();
	TotalTime = (StopTime - StartTime) / 1000.0;
	printf("    - Size of array is %d\n", UPPERLIMIT);
	printf("    - Total multiplication time is %3.3f seconds\n\n", TotalTime);
#endif
}

void object(9)
InitializeA(/*matrix Array*/)
/*
 * Intializes the given array with random integers.
 */
{
	int             OuterIndex, InnerIndex;

	for (OuterIndex = 0; OuterIndex < UPPERLIMIT; OuterIndex++) {
	  for (InnerIndex = 0; InnerIndex < UPPERLIMIT; InnerIndex++) {
	    A[OuterIndex][InnerIndex] = RandomInteger();
	  }
	}
}

void object(9)
InitializeB(/*matrix Array*/)
/*
 * Intializes the given array with random integers.
 */
{
	int             OuterIndex, InnerIndex;

	for (OuterIndex = 0; OuterIndex < UPPERLIMIT; OuterIndex++) {
	  for (InnerIndex = 0; InnerIndex < UPPERLIMIT; InnerIndex++) {
	    B[OuterIndex][InnerIndex] = RandomInteger();
	  }
	}
}





int object(9)
RandomInteger(void)
/*
 * Generates random integers between 0 and 8095
 */
{
	Seeds = ((Seeds * 133) + 81) % 8095;
	return (Seeds);
}


#ifndef UPPSALAWCET
int object(9)
ttime()
/*
 * This function returns in milliseconds the amount of compiler time
 * used prior to it being called.
 */
{
	struct tms      buffer;
	int             utime;

	/* times(&buffer);   times not implemented */
	utime = (buffer.tms_utime / 60.0) * 1000.0;
	return (utime);
}
#endif

void object(9)
Multiply(/*matrix A, matrix B, matrix Res*/)
/*
 * Multiplies arrays A and B and stores the result in ResultArray.
 */
{
  register int    Outer, Inner, Index;

  for (Outer = 0; Outer < UPPERLIMIT; Outer++) {
    for (Inner = 0; Inner < UPPERLIMIT; Inner++) {
      Res[Outer][Inner] = 0;
      for (Index = 0; Index < UPPERLIMIT; Index++) {
	Res[Outer][Inner] +=
	  A[Outer][Index] * B[Index][Inner];
      }
    }
  }
}
