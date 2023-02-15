#include <stdio.h>

static long num_steps = 1000000; //num rectangles
double step;

int main () {
  double x;
  double pi;
  double sum = 0.0; //sum of all rectangles

  //change in x (i.e., width of the rectange)
  step = 1.0/(double)num_steps;

  //calculate the summation of F(x)
  //(i.e., sum of the rectangles)
  //(i.e., the approximation of pi)
  for (int i=0; i < num_steps; i++) {
    x = (i+0.5)*step;
    sum = sum + 4/(1.0+x*x);
  }
  pi = step * sum;
  printf("pi = %f\n", pi);
}