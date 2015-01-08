/*-----------------------------------------------------------------------*/
/* Program: Stream                                                       */
/* Adapted to StarSs by Rosa M. Badia (Barcelona Supercomputing Center)	 */
/* This version does not insert barriers after each set of operations,   */
/* to promote task chaining in StarSs					 */
/* Revision: $Id: stream.c,v 5.8 2007/02/19 23:57:39 mccalpin Exp mccalpin $ */
/* Original code developed by John D. McCalpin                           */
/* Programmers: John D. McCalpin                                         */
/*              Joe R. Zagar                                             */
/*                                                                       */
/* This program measures memory transfer rates in MB/s for simple        */
/* computational kernels coded in C.                                     */
/*-----------------------------------------------------------------------*/
/* Copyright 1991-2005: John D. McCalpin                                 */
/*-----------------------------------------------------------------------*/
/* License:                                                              */
/*  1. You are free to use this program and/or to redistribute           */
/*     this program.                                                     */
/*  2. You are free to modify this program for your own use,             */
/*     including commercial use, subject to the publication              */
/*     restrictions in item 3.                                           */
/*  3. You are free to publish results obtained from running this        */
/*     program, or from works that you derive from this program,         */
/*     with the following limitations:                                   */
/*     3a. In order to be referred to as "STREAM benchmark results",     */
/*         published results must be in conformance to the STREAM        */
/*         Run Rules, (briefly reviewed below) published at              */
/*         http://www.cs.virginia.edu/stream/ref.html                    */
/*         and incorporated herein by reference.                         */
/*         As the copyright holder, John McCalpin retains the            */
/*         right to determine conformity with the Run Rules.             */
/*     3b. Results based on modified source code or on runs not in       */
/*         accordance with the STREAM Run Rules must be clearly          */
/*         labelled whenever they are published.  Examples of            */
/*         proper labelling include:                                     */
/*         "tuned STREAM benchmark results"                              */
/*         "based on a variant of the STREAM benchmark code"             */
/*         Other comparable, clear and reasonable labelling is           */
/*         acceptable.                                                   */
/*     3c. Submission of results to the STREAM benchmark web site        */
/*         is encouraged, but not required.                              */
/*  4. Use of this program or creation of derived works based on this    */
/*     program constitutes acceptance of these licensing restrictions.   */
/*  5. Absolutely no warranty is expressed or implied.                   */
/*-----------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <getopt.h>
#include "limits.h"
#include <sys/time.h>

#include "taskplus.h"


#define HLINE "-------------------------------------------------------------\n"

#ifndef MIN
# define MIN(x,y) ((x)<(y)?(x):(y))
#endif
#ifndef MAX
# define MAX(x,y) ((x)>(y)?(x):(y))
#endif

#define N      40*1024*1024
#define NTIMES 10
#define BSIZE N/16

static double  a[N], b[N], c[N];
int nTimes = NTIMES;

#define BYTES  (10 * sizeof(double) * N)

void checkSTREAMresults();
int process_command_line(int argc, char **argv, int *noFlush, int *iterations);

/* Host functions */
void init(double *a, double *b, double *c, int size);
void copy(double *a, double *c, int size);
void scale (double *b, double *c, double scalar, int size);
void add (double *a, double *b, double *c, int size);
void triad (double *a, double *b, double *c, double scalar, int size);

using namespace cern_parallel;

int main(int argc, char *argv[])
{
    int				BytesPerWord;
    register int	j, k;
    double		scalar, total_time;
    int                 noFlush = 0;
    struct timeval      stop, start;
    TaskManager tm;

    /* --- SETUP --- determine precision and check timing --- */

    process_command_line(argc, argv, &noFlush, &nTimes);

    printf(HLINE);
    
    printf("STREAM version $Revision: 5.8 $\n");
    printf(HLINE);
    BytesPerWord = sizeof(double);
    printf("This system uses %d bytes per DOUBLE PRECISION word.\n", BytesPerWord);

    printf(HLINE);
    printf("Array size = %d\n" , N);
    printf("Total memory required = %.1f MB.\n", (3.0 * BytesPerWord) * ( (double) N / 1048576.0));
    printf(HLINE);

    gettimeofday(&start, NULL);

    tm.parallel_for(0, N, BSIZE, [=](int j){ init(&a[j],&b[j],&c[j], BSIZE); });

    /*	--- MAIN LOOP --- repeat test cases nTimes times --- */

    // assuming N % BSIZE == 0
    scalar = 3.0;
    for (k=0; k<nTimes; k++) {
    	tm.parallel_for(0, N, BSIZE, [=](int j){ copy(&a[j], &c[j], BSIZE); });

    	tm.parallel_for(0, N, BSIZE, [=](int j){ scale(&b[j], &c[j], scalar, BSIZE); });

    	tm.parallel_for(0, N, BSIZE, [=](int j){ add(&a[j], &b[j], &c[j], BSIZE); });

    	tm.parallel_for(0, N, BSIZE, [=](int j){ triad(&a[j], &b[j], &c[j], scalar, BSIZE); });
    }

    gettimeofday(&stop, NULL);

    total_time = (double)(stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec)*1.0E-06;
    
    /*	--- SUMMARY --- */

    printf ("Average Rate (MB/s): %11.4f \n", 1.0E-06 * BYTES *nTimes/total_time);
    printf("TOTAL time (including initialization) =  %f seconds\n", total_time);
    printf(HLINE);

    /* --- Check Results --- */

    checkSTREAMresults();
    printf(HLINE);

    return 0;
}

void checkSTREAMresults ()
{
	double aj,bj,cj,scalar;
	double asum,bsum,csum;
	double epsilon;
	int	j,k;

    /* reproduce initialization */
	aj = 1.0;
	bj = 2.0;
	cj = 0.0;
    /* a[] is modified during timing check */
	aj = 2.0E0 * aj;
    /* now execute timing loop */
	scalar = 3.0;
	for (k=0; k<nTimes; k++)
        {
            cj = aj;
            bj = scalar*cj;
            cj = aj+bj;
            aj = bj+scalar*cj;
        }
	aj = aj * (double) (N);
	bj = bj * (double) (N);
	cj = cj * (double) (N);

	asum = 0.0;
	bsum = 0.0;
	csum = 0.0;
	for (j=0; j<N; j++) {
		asum += a[j];
		bsum += b[j];
		csum += c[j];
	}
#ifdef VERBOSE
	printf ("Results Comparison: \n");
	printf ("        Expected  : %f %f %f \n",aj,bj,cj);
	printf ("        Observed  : %f %f %f \n",asum,bsum,csum);
#endif

#ifndef abs
#define abs(a) ((a) >= 0 ? (a) : -(a))
#endif
	epsilon = 1.e-8;

	if (abs(aj-asum)/asum > epsilon) {
		printf ("Failed Validation on array a[]\n");
		printf ("        Expected  : %f \n",aj);
		printf ("        Observed  : %f \n",asum);
	}
	else if (abs(bj-bsum)/bsum > epsilon) {
		printf ("Failed Validation on array b[]\n");
		printf ("        Expected  : %f \n",bj);
		printf ("        Observed  : %f \n",bsum);
	}
	else if (abs(cj-csum)/csum > epsilon) {
		printf ("Failed Validation on array c[]\n");
		printf ("        Expected  : %f \n",cj);
		printf ("        Observed  : %f \n",csum);
	}
	else {
		printf ("Solution Validates\n");
	}
}

int process_command_line(int argc, char **argv, int *noFlush, int *iterations)
{
    int opt;

    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"help", 0, NULL, 'h'},
            {"noflush", 0, NULL, 'n'},
            {"iterations", 1, NULL, 'i'},
            {NULL, 0, NULL, 0}
        };

        opt = getopt_long(argc, argv, "hni:", long_options, &option_index);

        if (opt == -1) {
            break;
        }

        switch (opt) {
        case 'h':
        case '?':
            printf("Usage: %s [--help] [--noflush|-n] [--iterations|-i NUM_ITERATIONS]\n", argv[0]);
            printf("\n");
            printf("Options:\n");
            printf("Options:\n");
            printf("--noflush,-n             Do not copy GPU data to main memory at the end of computation\n", argv[0]);
            printf("--iterations,-i N        Run N iterations\n", argv[0]);
            printf("\n");
            exit(EXIT_SUCCESS);
            break;
        case 'n':
            *noFlush = 1;
            break;
        case 'i':
            *iterations = strtoul(optarg, 0, 0);
            break;
        default:
            return 1;
        }
    }

    return 0;
}
