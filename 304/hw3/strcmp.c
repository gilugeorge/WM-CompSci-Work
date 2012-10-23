/*Eric Shih
 *This program takes in two input strings and compares the two to see
 *if they are the same or not.
 */

#include <stdio.h>

int sLength(char string[]);


int main(int argc, char *argv[]){
  int i = 0;//itarator for first loop
  int j = 0;//itarator for second loop
  int count = 0; //count for equals comparison

  /*Checks to see if they are the same*/
  for(i = 0; i < sLength(argv[1]); i++){
    for(j = 0; j < sLength(argv[2]); j++){
      
      //When x <equals> y
      if(sLength(argv[1]) == sLength(argv[2])){
	if(argv[1][i] == argv[2][j]){
	  count++;
	}//char if
	if(count == sLength(argv[1])){
	  printf("%s <equals> %s\n", argv[1], argv[2]);
	}//count if
      }//length if

      //When x <precedes> y
      if(argv[1][i] < argv[2][j]){
	printf("%s <precedes> %s\n", argv[1],argv[2]);
	i = sLength(argv[1]);
	break;
      }//less than if

      //When x <follows> y
      if(argv[1][i] > argv[2][j]){
	printf("%s <follows> %s\n", argv[1],argv[2]);
	i = sLength(argv[1]);
	break;
      }//less than if

    }//inner-for
  }//outer-for

  return 0;
}//main

/*
 *This function finds the length of a string
 */
int sLength(char string[]){
    int index = 0;

    while(string[index] != '\0'){
      index++;
    }//while

    return index;
}//sLength
