#include <math.h>
#include "lab1.h"

void findPrimes(unsigned int *numbers, unsigned short count)
{
  int i, a, b;
  
  //makes the list of numbers
  for(i = 0; i < count; i++)  {
    numbers[i]= i;
  }//for

  //changing prime to 1, composite to 0
  for(a = 0; a < count; a++){
    for(b = 0; b < count; b++) { 
  
      //for the zero and one case      
      if(a == 0 || b == 0 || a == 1 || b == 1)  {
        numbers[b] = 1;
      }else if(numbers[b] == 0 || a == b)  {
      }else if((b % a) == 0)  {
        numbers[b] = 0;
      }else  {
        numbers[b] = 1;
      }//else-if
     }//for b
   }//for a

}//findPrimes

int fastExp(int base, int exponent, int modulus)
{
  int answer = 1;
  int power = base % modulus;
  int i;

  for(i = exponent; i > 1; i= i / 2)  {
    if(i % 2 == 1)  {
      answer = (answer * power) % modulus;
    }//if
    else  {
      power = (power * power) % modulus;
    }//else
  }//for
  
  return answer;
}//fastExp
