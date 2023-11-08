#include <mpi.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  long N;

  if (rank == 0) {
    // Prompt the user for the number of intervals
    printf("Enter the number of intervals (N): ");
    
    // Read the user's input
    if (scanf("%ld", &N) != 1) {
      printf("Invalid input. Please enter a valid number of intervals (N).\n");
      MPI_Finalize();
      return 1;
    }
  }

  // Broadcast N to all processes
  MPI_Bcast(&N, 1, MPI_LONG, 0, MPI_COMM_WORLD);

  double h = 1.0 / N;  // Width of each subinterval
  double pi_approximation = 0.0;

  printf("Calculate Pi with MPI on %d Processes\n", size);

  // Start timing
  double start_time = MPI_Wtime();
  
  for (int i = rank; i < N; i += size) {
    double x = (i + 0.5) * h;
    double fx = 4.0 / (1.0 + x * x);
    pi_approximation += fx;
  }

  // Sum the results from all processes
  double global_pi_approximation;
  MPI_Reduce(&pi_approximation, &global_pi_approximation, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  // End timing
  double end_time = MPI_Wtime();

  if (rank == 0) {
    global_pi_approximation *= h;  // Multiply by the width of each subinterval

    printf("Approximation of Pi: %lf\n", global_pi_approximation);
    printf("Time taken: %lf seconds\n", end_time - start_time);
  }

  MPI_Finalize();
  return 0;
}
