#include <math.h>
#include "lab2.h"

int numGenerator()
{

  int modulus = 9;
  int multiplier = 7;
  int increment = 4;
  int seed = 3;
  int count;
  int output;

  if(output == null)  {
    output = (multiplier * 1 + increment) % modulus;
    return output;
  }else {
   output = (multiplier * output + increment) % modulus;
    return output; 
  }


}//numGenerator

int encrypt(String phrase, int p, int q, int e)
{

  return 0;
}//encrypt

int decrypt(int input, int p, int q, int e)
{

  return 0;
}//decrypt
