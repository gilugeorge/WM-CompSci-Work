/*Eric Shih
 *This program takes in 4 numbers and ouputs all letter combinations
 *that the number can represent.
 */


#include <stdio.h>
int getc(FILE *stream);

int doTranslate(char ch1, char ch2, char ch3, char ch4);


int main(){
  char ch1, ch2, ch3, ch4;

  //prompt and take in the value
  printf("Please enter a 4 digit number (will only take in first 4 numbers entered): \n");
  ch1 = getc(stdin);  
  ch2 = getc(stdin);
  ch3 = getc(stdin);  
  ch4 = getc(stdin);
  
  //send the values into the function to be translated.
  doTranslate(ch1, ch2, ch3, ch4);
 
 return 0;
}//main

int doTranslate(char ch1, char ch2, char ch3, char ch4){
  int w, x, y, z; //counters
  int set1, set2, set3, set4; //ascii values

  //finds the correct ascii location
  set1 = 65 + ((ch1 - 50) * 3);
  set2 = 65 + ((ch2 - 50) * 3);
  set3 = 65 + ((ch3 - 50) * 3);
  set4 = 65 + ((ch4 - 50) * 3);

  //finds and prints each letter associated with the number
  for(w = 0; w < 3; w++){
    for(x = 0; x< 3; x++){
      for(y = 0; y < 3; y++){
	for(z = 0; z < 3; z++){
	 
	  //This block is the set of checks to make sure 0 and 1 is outputted correctly.
	  //and for q to be omitted.

	  //checks for 0 & 1 in 1st location
	  if(ch1 == '0'){
	    w = 3;
	    set1 = 45;
	  }
	  if(ch1 == '1'){
	    w = 3;
	    set1 = 46;
	  }
	  if(set1 + w == 81){
	    set1++;
	  }
	    //checks for 0 & 1 in 2nd location
	  if(ch2 == '0'){
	    x = 3;
	    set2 = 45;
	  }
	  if(ch2 == '1'){
	    x = 3;
	    set2 = 46;
	  }
	  if(set2 + x == 81){
	    set2++;
	  }
	    //checks for 0 & 1 in 3rd location
	  if(ch3 == '0'){
	    y = 3;
	    set3 = 45;
	  }
	  if(ch3 == '1'){
	    y = 3;
	    set3 = 46;
	  } 
	  if(set3 +y == 81){
	    set3++;
	  }
	  //checks for 0 & 1 in 4th location
	  if(ch4 == '0'){
	    z = 3;
	    set4 = 45;
	  }
	  if(ch4 == '1'){
	    z = 3;
	    set4 = 46;
	  }
	  if(set4 +z == 81){
	    set4++;
	    
	  }

	  

	  //prints the combination
	  printf("%c%c%c%c ", (set1 + w), (set2 + x), (set3 + y), (set4 +z));
	}//for
      }//for
    }//for
  }//for

  return 0;
}//doTranslate


