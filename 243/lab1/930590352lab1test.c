#include <stdio.h>
#include "lab1.h"
#include <math.h>

int main()
{
  unsigned int primeCandidates[10];
  int i;
  int count = 10;

  //test a basic 10 count
  for(i = 0; i < count; i++)  {
    primeCandidates[i] = 1;
  }//for
  printf("Created the array\n");

  findPrimes(primeCandidates, count);
  for(i= 2; i < 10; i++) {
    if (i == 2 || i == 3 || i == 5 ||
        i == 7) {
      if(primeCandidates[i] != 1) {
        printf("You say that %d is composite, but it is prime.\n", i);
      }
    } else {
      if(primeCandidates[i] != 0) {
        printf("You say that %d is prime, but it is composite.\n", i);
      }
      }//else   
  }//for

  //test sending nothing
  unsigned int list[0];
  count = 0;

  for(i = 0; i < count; i++)  {
    list[i] = 1;
  }//for
  printf("Created the array2\n");

  findPrimes(list, count);


  //test large number
  unsigned int list1[999999];
  count = 999999;

  for(i = 0; i < count; i++)  {
    list1[i] = 1;
  }//for
  printf("Created the array3\n");

  findPrimes(list1, count);

  //test normal fastExp
  if(fastExp(7, 66, 34) != 15) {
    printf("Incorrect result for 7^66 mod 34.\n");
  }

  //test normal
  if(fastExp(2, 88, 7) != 2) {
    printf("Incorrect result for 7^644 mod 645.\n");
  }

  //test nothing
  if(fastExp(0, 0, 0) != 1) {
    printf("Incorrect result for 0^0 mod 0.\n");
  }
  return 0;
}//main
