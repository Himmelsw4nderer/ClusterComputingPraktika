#include <stdio.h>

#include "mpi.h"
int main(int argc, char **argv) {
  long N = 100000;
  int Tag1 = 1, Tag2 = 2, buffer_count = 100, num_procs, rank, i;
  long buffer[buffer_count];

  double h = 1.0 / N;
  double pi_approximation = 0.0;
 

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  if (rank == 0) {
    printf("Calculate Pi with MPI %d Threads Parralel \n", num_procs);
  }

  int chunkSize = N / num_procs;
  int chunkStart = rank * chunkSize;
  double local_pi_approximation = 0.0;

  int chunkEnd = chunkStart + chunkSize;
  clock_t start_time = clock();
  for (int i = chunkStart; i < chunkEnd; i++) {
    double x = (i + 0.5) * h;
    double fx = 4.0 / (1.0 + x * x);
    local_pi_approximation += fx;
  }

  MPI_Reduce(&local_pi_approximation, &pi_approximation, 1, MPI_DOUBLE, MPI_SUM,
             0, MPI_COMM_WORLD);

  clock_t end_time = clock();

  // Calculate the elapsed time in seconds
  double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  if (rank == 0) {
    printf("Approximation of Pi: %lf\n", pi_approximation *= h);
    printf("Time taken: %lf seconds\n", elapsed_time);
  }

  MPI_Finalize();
}