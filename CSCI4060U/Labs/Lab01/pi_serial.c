#include <stdio.h>

static long num_steps = 1000000;
double step;

int main() {
  double x;
  double pi;
  double sum = 0.0;

  //change in x (i.e. width of rectangle)
  step = 1.0/(double)num_steps;

  //calculate the summation of F(x)
  // (i.e. sum of rectangles)
  //in the approximation of pi
  for (int i=0; i < num_steps; i++) {
    //calculate height
    x = (i+0.5)*step;
    sum = sum + 4/(1.0+x*x); //sum F(x)
  }
  pi = step * sum;
  printf("pi = %f", pi);
}