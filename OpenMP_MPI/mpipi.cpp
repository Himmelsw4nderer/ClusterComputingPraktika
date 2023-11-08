#include <stdio.h>

#include "mpi.h"

int max(int a, int b) {
  if (a > b) return a;
  return b;
}

int main(int argc, char** argv) {
  long N = 10000000;
  int chunkSize = 1000000;
  int chunkCount = N / chunkSize;
  int Tag1 = 1, buffer_count = 100, num_procs, rank, i;
  long buffer[buffer_count];

  double h = 1.0 / N;
  double pi_approximation = 0.0;
  clock_t start_time = clock();

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  if (rank == 0) {
    printf("Calculate Pi with MPI %d Threads Parralel \n", num_procs);
  }

  double local_pi_approximation = 0;

  int chunkNumber = rank - 1;
  while (chunkNumber < chunkCount - 1) {
    int flag = 1;
    MPI_Request request;
    while (flag) {
      int newChunkNumber = 0;
      MPI_Irecv(&newChunkNumber, buffer_count, MPI_INT, 1, MPI_ANY_TAG,
                MPI_COMM_WORLD, &request);
      MPI_Test(&request, &flag, MPI_STATUS_IGNORE);
      printf("Chunk %d %d from Thread %d prepared\n ", chunkNumber, flag, rank);
      if (!flag) chunkNumber = max(chunkNumber + 1, newChunkNumber + 1);
    }
    MPI_Bcast(&chunkNumber, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Chunk %d from Thread %d prepared\n ", chunkNumber, rank);
    if (chunkNumber > chunkCount - 1) {
      MPI_Reduce(&local_pi_approximation, &pi_approximation, 1, MPI_DOUBLE,
                 MPI_SUM, 0, MPI_COMM_WORLD);
    } else {
      printf("Chunk %d from Thread %d started\n ", chunkNumber, rank);

      int chunkStart = chunkNumber * chunkSize;

      int chunkEnd = chunkStart + chunkSize;
      clock_t start_time = clock();
      for (int i = chunkStart; i < chunkEnd; i++) {
        double x = (i + 0.5) * h;
        double fx = 4.0 / (1.0 + x * x);
        local_pi_approximation += fx;
      }
      printf("Chunk %d from Thread %d finished\n ", chunkNumber, rank);
    }
  }
  if (rank == 0) {
    clock_t end_time = clock();

    // Calculate the elapsed time in seconds
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Approximation of Pi: %lf\n", pi_approximation *= h);
    printf("Time taken: %lf seconds\n", elapsed_time);
  }
  MPI_Finalize();
}