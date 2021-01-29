#ifndef MATUTIL_H
#define MATUTIL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <omp.h>

// Generate a random matrix.

void GenMatrix(int *mat, const size_t N);

// Compare the content of two integer arrays. Return true if they are
// exactly the same; otherwise return false.

bool CmpArray(const int *l, const int *r, const size_t eleNum);

// Compute APSP using single thread.

void ST_APSP(int *mat, const size_t N);

// Compute APSP using multiple thread.

void MT_APSP(int *mat, const size_t N);

#endif
