#include <stdio.h>

#include "lab1.h"

int main(int argc, char** argv)
{
  if(fastExp(7, 644, 645) != 436) {
    printf("Incorrect result for 7^644 mod 645.\n");
  }

  if(fastExp(3, 2003, 99) != 27) {
    printf("Incorrect result for 3^2003 mod 99.\n");
  }

  return 0;
}
