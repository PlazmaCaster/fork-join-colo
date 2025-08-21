#include "objects.h"
#include "rv.h"

/**
 * @file object18.c
 *
 * Port of the MRTC benchmark ud
 */

/* MDH WCET BENCHMARK SUITE. File version $Id: ud.c,v 1.4 2005/11/11 10:32:53 ael01 Exp $ */


/*************************************************************************/
/*                                                                       */
/*   SNU-RT Benchmark Suite for Worst Case Timing Analysis               */
/*   =====================================================               */
/*                              Collected and Modified by S.-S. Lim      */
/*                                           sslim@archi.snu.ac.kr       */
/*                                         Real-Time Research Group      */
/*                                        Seoul National University      */
/*                                                                       */
/*                                                                       */
/*        < Features > - restrictions for our experimental environment   */
/*                                                                       */
/*          1. Completely structured.                                    */
/*               - There are no unconditional jumps.                     */
/*               - There are no exit from loop bodies.                   */
/*                 (There are no 'break' or 'return' in loop bodies)     */
/*          2. No 'switch' statements.                                   */
/*          3. No 'do..while' statements.                                */
/*          4. Expressions are restricted.                               */
/*               - There are no multiple expressions joined by 'or',     */
/*                'and' operations.                                      */
/*          5. No library calls.                                         */
/*               - All the functions needed are implemented in the       */
/*                 source file.                                          */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  FILE: ludcmp.c                                                       */
/*  SOURCE : Turbo C Programming for Engineering                         */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Simultaneous linear equations by LU decomposition.                */
/*     The arrays alud[][] and blud[] are input and the array xlud[] is output    */
/*     row vector.                                                       */
/*     The variable n is the number of equations.                        */
/*     The input arrays are initialized in function main.                */
/*                                                                       */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/

/*************************************************************************
 *  This file:
 *
 *  - Name changed to "ud.c"
 *  - Modified for use with Uppsala/Paderborn tool
 *    : doubles changed to int
 *    : some tests removed
 *  - Program is much more linear, all loops will run to end
 *  - Purpose: test the effect of conditional flows
 *
 *************************************************************************/




/*
** Benchmark Suite for Real-Time Applications, by Sung-Soo Lim
**
**    III-4. ludcmp.c : Simultaneous Linear Equations by LU Decomposition
**                 (from the book C Programming for EEs by Hyun Soon Ahn)
*/



long int alud[50][50], blud[50], xlud[50];

int ludcmp(int nmax, int n);


/*  static double fabs(double n) */
/*  { */
/*    double f; */

/*    if (n >= 0) f = n; */
/*    else f = -n; */
/*    return f; */
/*  } */

void object(18)
object18()
{
  int      i, j, nmax = 50, n = 5, chkerr;
  long int /* eps, */ w;

  /* eps = 1.0e-6; */

  /* Init loop */
  for(i = 0; i <= n; i++)
    {
      w = 0.0;              /* data to fill in cells */
      for(j = 0; j <= n; j++)
        {
          alud[i][j] = (i + 1) + (j + 1);
          if(i == j)            /* only once per loop pass */
            alud[i][j] *= 2;
          w += alud[i][j];
        }
      blud[i] = w;
    }

  /*  chkerr = ludcmp(nmax, n, eps); */
  chkerr = ludcmp(nmax,n);
  EXIT;
}

int object(18)
ludcmp(int nmax, int n)
{
  int i, j, k;
  long w, y[100];

  /* if(n > 99 || eps <= 0.0) return(999); */
  for(i = 0; i < n; i++)
    {
      /* if(fabs(alud[i][i]) <= eps) return(1); */
      for(j = i+1; j <= n; j++) /* triangular loop vs. i */
        {
          w = alud[j][i];
          if(i != 0)            /* sub-loop is conditional, done
                                   all iterations except first of the
                                   OUTER loop */
            for(k = 0; k < i; k++) {
              w -= alud[j][k] * alud[k][i];
						}
          alud[j][i] = w / alud[i][i];
        }
      for(j = i+1; j <= n; j++) /* triangular loop vs. i */
        {
          w = alud[i+1][j];
          for(k = 0; k <= i; k++)  {/* triangular loop vs. i */
            w -= alud[i+1][k] * alud[k][j];
					}
          alud[i+1][j] = w;
        }
    }
  y[0] = blud[0];
  for(i = 1; i <= n; i++)       /* iterates n times */
    {
      w = blud[i];
      for(j = 0; j < i; j++) {    /* triangular sub loop */
        w -= alud[i][j] * y[j];
			}
      y[i] = w;
    }
  xlud[n] = y[n] / alud[n][n];
  for(i = n-1; i >= 0; i--)     /* iterates n times */
    {
      w = y[i];
      for(j = i+1; j <= n; j++) { /* triangular sub loop */
        w -= alud[i][j] * xlud[j];
			}
      xlud[i] = w / alud[i][i] ;
    }
  return(0);
}
