#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "MatUtil.h"

// mpicc APSP.c MatUtil.c MatUtil.h

int main(int argc, char **argv)
{

	struct timeval tv1, tv2;
	int rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (argc != 2)
	{
		printf(" Usage: test {N}\n");
		exit(-1);
	}

	//generate a random matrix.
	size_t N = atoi(argv[1]);
	int *mat = (int *)malloc(sizeof(int) * N * N);

	GenMatrix(mat, N);

	//compute the reference result.
	int *ref = (int *)malloc(sizeof(int) * N * N);
	memcpy(ref, mat, sizeof(int) * N * N);
	gettimeofday(&tv1, NULL);
	ST_APSP(ref, N);
	gettimeofday(&tv2, NULL);
	if (rank == 0)
	{
		printf("Elasped time = %ld usecs\n",
			   (tv2.tv_sec - tv1.tv_sec) * 1000000 + tv2.tv_usec - tv1.tv_usec);
	}

	//compute your results
	int *result = (int *)malloc(sizeof(int) * N * N);
	memcpy(result, mat, sizeof(int) * N * N);
	//replace by parallel algorithm

	gettimeofday(&tv1, NULL);
	// MT_APSP(result, N); //matrix
	MT_SM_APSP(result, N); //row
	gettimeofday(&tv2, NULL);
	if (rank == 0)
	{
		printf("Elasped Parallel time = %ld usecs\n",
			   (tv2.tv_sec - tv1.tv_sec) * 1000000 + tv2.tv_usec - tv1.tv_usec);
	}

	//compare your result with reference result
	if (rank == 0)
	{
		if (CmpArray(result, ref, N * N))
			printf("Rank = %d Your result is correct.\n", rank);
		else
			printf("Rank = %d Your result is wrong.\n", rank);
	}

	MPI_Finalize();
}
