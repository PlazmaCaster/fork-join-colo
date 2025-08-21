#include "objects.h"
#include "rv.h"

/**
 * @file
 *
 * Port of the MRTC bs benchmark
 */


/* MDH WCET BENCHMARK SUITE. File version $Id: bs.c,v 1.1.1.1 2007-12-11 15:22:55 puaut Exp $ */

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
/*  FILE: bs.c                                                           */
/*  SOURCE : Public Domain Code                                          */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Binary search for the array of 15 integer elements.               */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/

struct DATA {
	int             key;
	int             value;
};

int binary_search(struct DATA data[15], int x);

void object(1) reset_data(struct DATA data[15]) {
        int keys[] = {1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        int values[] = {100, 200,  300,  700, 900, 250, 400, 600,
                        800, 1500, 1200, 110, 140, 133, 10};

        for (int i=0; i<15; i++) {
		data[i].key = keys[i];
		data[i].value = values[i];
	}
}

void object(1) object01(void) {
        struct DATA data[15];
        reset_data(data);
        binary_search(data, 8);
        EXIT;
}

int object(1)
binary_search(struct DATA data[15], int x)
{
	int             fvalue, mid, up, low;

	low = 0;
	up = 14;
	fvalue = -1 /* all data are positive */ ;
	while (low <= up) {
		mid = (low + up) >> 1;
		if (data[mid].key == x) {	/* found  */
			up = low - 1;
			fvalue = data[mid].value;
		} else
		 /* not found */ if (data[mid].key > x) {
			up = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	return fvalue;
}
