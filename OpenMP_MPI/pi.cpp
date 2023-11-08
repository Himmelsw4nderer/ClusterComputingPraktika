#include <omp.h>
#include <stdio.h>
#include <time.h>

#include "mpi.h"

int main() {
  long N;

  // Prompt the user for the number of intervals
  printf("Enter the number of intervals (N): ");

  // Read the user's input
  if (scanf("%ld", &N) != 1) {
    printf("Invalid input. Please enter a valid number of intervals (N).\n");
  }
  double h = 1.0 / N;  // Width of each subinterval
  double pi_approximation = 0.0;

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

  printf("\nCalculate Pi with OpenMP Parralel \n");

  pi_approximation = 0.0;
  start_time = clock();
#pragma omp parallel for reduction(+ : pi_approximation)
  for (int i = 0; i < N; i++) {
    double x = (i + 0.5) * h;
    double fx = 4.0 / (1.0 + x * x);
    pi_approximation += fx;
  }

  pi_approximation *= h;  // Multiply by the width of each subinterval

  // End timing
  end_time = clock();

  // Calculate the elapsed time in seconds
  elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

  printf("Approximation of Pi: %lf\n", pi_approximation);
  printf("Time taken: %lf seconds\n", elapsed_time);

  return 0;
}