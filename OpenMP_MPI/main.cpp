#include <stdio.h>

int main() {
  int N;

  // Prompt the user for the number of intervals
  printf("Enter the number of intervals (N): ");

  // Read the user's input
  if (scanf("%d", &N) != 1) {
    printf("Invalid input. Please enter a valid number of intervals (N).\n");
    return -1;
  }
  double h = 1.0 / N;  // Width of each subinterval
  double pi_approximation = 0.0;

  for (int i = 0; i < N; i++) {
    double x = (i + 0.5) * h;
    double fx = 4.0 / (1.0 + x * x);
    pi_approximation += fx;
  }

  pi_approximation *= h;  // Multiply by the width of each subinterval

  printf("Approximation of Pi: %lf\n", pi_approximation);

  return 0;
}