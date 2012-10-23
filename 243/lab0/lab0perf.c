#include <stdio.h>
#include "lab0.h"

int main(int argc, char **argv)
{
  int numbers[] = {15, 0, -3, 7, 27743, 6, 8, 1, -5732, 1, 9};

  printf("The sum is %d\n", sum(numbers, 11));
  printf("The average is %7.2f\n", average(numbers, 11));
  printf("The standard deviation is %7.2f\n", sd(numbers, 11));

  return 0;
}
