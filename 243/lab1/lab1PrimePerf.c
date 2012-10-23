#include <stdio.h>

#include "lab1.h"

int main(int argc, char** argv)
{
  int i = 0;
  unsigned int primeCandidates[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

  findPrimes(primeCandidates, 100);

  for(i= 2; i < 100; i++) {
    if (i == 2 || i == 3 || i == 5 ||
        i == 7 || i == 11 || i == 13 ||
        i == 17 || i == 19 || i == 23 ||
        i == 29 || i == 31 || i == 37 ||
        i == 41 || i == 43 || i == 47 ||
        i == 53 || i == 59 || i == 61 ||
        i == 67 || i == 71 || i == 73 ||
        i == 79 || i == 83 || i == 89 ||
        i == 97) {
      if(primeCandidates[i] != 1) {
        printf("You say that %d is composite, but it is prime.\n", i);
      }
    } else {
      if(primeCandidates[i] != 0) {
        printf("You say that %d is prime, but it is composite.\n", i);
      }
    } 

  }//for
  return 0;
}
