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

  printf("Calculate Pi not Parralel \n");

  clock_t start_time = clock();
  for (int i = 0; i < N; i++) {
    double x = (i + 0.5) * h;
    double fx = 4.0 / (1.0 + x * x);
    pi_approximation += fx;
  }

  pi_approximation *= h;  // Multiply by the width of each subinterval

  // End timing
  clock_t end_time = clock();

  // Calculate the elapsed time in seconds
  double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

  printf("Approximation of Pi: %lf\n", pi_approximation);
  printf("Time taken: %lf seconds\n", elapsed_time);