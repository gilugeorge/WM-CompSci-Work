/*Eric Shih
 *This program extracts intergers from the user, stores values
 *into an array and removes duplicates.
 */

#include <stdio.h>
#define MAX_NUMS 1000

int main(){
  int i = 0;
  int j = 0;
  int count = 0;
  int array [MAX_NUMS];
  int *ptr;//the pointer for the array

  /*Collect number input*/
  for(i = 0; i < MAX_NUMS; i++){
    printf("Input a number (-1 to exit): ");
    scanf("%d", &array[count]);
    count++;
    //Exit Statement
    if(array[i] == -1){
      count--;
      break;
    }//if
  }//for

  /*Find and Delete Duplicates*/  
  for(i = 0; i < count; i++){
    for(j = count; j >= 0; j--){
      if(i == j){
	//so that the same index will not be deleted
      }
      else if(array[i] == array[j]){
	array[j] = -1; //will replace all duplicates with -1
      }
    }//innter-for
  }//outer-for


 /*Print Contents of Array*/
  ptr = &array[0];
  for(j = 0; j < count; j++){
    if(*ptr != -1){
      printf("%d, ", *ptr);
    }//if

    ptr++;//moves pointer foreward
  }//for
  
  printf("\n");
  return 0;
}//main
