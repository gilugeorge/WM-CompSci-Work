/*Eric Shih
 *This program accepts numbers entered by the user until a
 *number is repeated. The program then prints out the list
 *of numbers and their sum.
 */

#include <stdio.h>
#define MAX_NUMS 1000

int main(){
  int sum = 0;
  int i;//iterators for the for loops
  int count = 0; //keeps track of numbers entered
  int array[MAX_NUMS];
  
  for(i = 0; i < MAX_NUMS; i++){ 
      printf("Number : ");
      scanf("%d", &array[count]);
      
      /*Check to see if it is a repeated number*/
	if(array[count] == array[count-1]){
	  i = MAX_NUMS;
	  count--;
	}//if

      count++;//shifts the index of the array to the next spot
  }//for

  /*sums the numbers and prints the results*/
  for(i = 0; i < count; i++){
    sum += array[i];
  }
  printf("%d numbers were entered and their sum is %d\n", count, sum);

  return 0;
}//main
