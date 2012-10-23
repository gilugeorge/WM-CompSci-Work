#include <stdio.h>
#include "lab0.h"

int main()
{
 int numbers[]= {1,2,3,4,5,6,7,8,9,10};
 int fail[]= {};

 printf("\nStart set1\n");
 printf("The Sum is %d\n", sum(numbers, 10));
 printf("The Average is %7.2f\n", average(numbers,10));
 printf("The SD is %7.2f\n", sd(numbers,10));

 //zero case
 printf("\nStart set 2\n");
 printf("The Sum is %d\n", sum(fail, 0));
 printf("The Average is %7.2f\n", average(fail, 0));
 printf("The SD is %7.2f\n", sd(fail, 0));

 //edge cases
 int edge[]= {1};
 printf("\nStart set 4\n");
 printf("The Sum is %d\n", sum(edge, 1));
 printf("The Average is %7.2f\n", average(edge, 1));
 printf("The SD is %7.2f\n", sd(edge, 1));

 //negative edge
 int edge1[]= {-1};
 printf("\nStart set 5\n");
 printf("The Sum is %d\n", sum(edge1, 1));
 printf("The Average is %7.2f\n", average(edge1, 1));
 printf("The SD is %7.2f\n", sd(edge1, 1));

 //negative and positive test
 int negpos[] = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
 printf("\nStart set 6\n");
 printf("The Sum is %d\n", sum(negpos, 11));
 printf("The Average is %7.2f\n", average(negpos, 11));
 printf("The SD is %7.2f\n", sd(negpos, 11));


 return 0;
}//main
