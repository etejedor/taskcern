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
#include <sys/time.h>


void init(double *a, double *b, double *c, int size)
{
	int j;
	for (j=0; j < size; j++){
	        a[j] = 1.0;
	        b[j] = 2.0;
	        c[j] = 0.0;
		a[j] = 2.0E0 * a[j];
  	}
}

void copy(double *a, double *c, int size)
{
	int j;	
	for (j=0; j < size; j++)
		c[j] = a[j];
}

void scale (double *b, double *c, double scalar, int size)
{
	int j;	
	for (j=0; j < size; j++)
	    b[j] = scalar*c[j];
}


void add (double *a, double *b, double *c, int size)
{
	int j;	
	for (j=0; j < size; j++)
	   c[j] = a[j]+b[j]; 
}


void triad (double *a, double *b, double *c, double scalar, int size)
{
    struct timeval      stop, start;
    double total_time;

	gettimeofday(&start, NULL);
	int j;	
	for (j=0; j < size; j++)
            a[j] = b[j]+scalar*c[j];
	gettimeofday(&stop, NULL);
	total_time = (double)(stop.tv_sec - start.tv_sec) + (stop.tv_usec - start.tv_usec)*1.0E-06;
	printf("TRIAD time =  %11.4f seconds\n", total_time);
}
