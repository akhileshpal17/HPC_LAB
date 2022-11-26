#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define ARRAY_SIZE 100000000

int main(int argc, char *argv[])
{
    int rank;
    int size;

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
    {
        fprintf(stderr, "Unable to initialize MPI!\n");
        return -1;
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;
    int *array = (int *)malloc(sizeof(int) * ARRAY_SIZE);
    int *chunk = (int *)malloc(sizeof(int) * ARRAY_SIZE / size);
    int i = 0;

    int total_sum = 0;
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = 1;
        total_sum += array[i];
    }

    double start = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Scatter(array, ARRAY_SIZE / size, MPI_INT, chunk, ARRAY_SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);
    int sum = 0;
    int temp = 0;
    int key = 1;
    for (i = 0; i < ARRAY_SIZE / size; i++)
        sum += chunk[i];

    /* Fancy stuff to keep the indexes correct */
    /* Number of processes participating halves each time */
    while (key <= size / 2)
    {
        if ((rank + 1) % key == 0)
            if (rank / key % 2 == 0)
            {
                MPI_Send(&sum, 1, MPI_INT, rank + key, 0, MPI_COMM_WORLD);
            }
            else
            {
                MPI_Recv(&temp, 1, MPI_INT, rank - key, 0, MPI_COMM_WORLD, &status);
                sum += temp;
            }
        key = 2 * key;
        MPI_Barrier(MPI_COMM_WORLD);
    }
    if (rank == size - 1)
    {
        double end = MPI_Wtime();
        printf("Total: %d\n", sum);
        printf("Correct Sum: %d\n\n", total_sum);
        printf("Time: %f\n", end - start);
    }
    free(array);
    free(chunk);
    MPI_Finalize();
    return 0;
}
