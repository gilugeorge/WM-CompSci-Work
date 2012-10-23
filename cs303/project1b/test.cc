#include <iostream>
#include "group.h"

using namespace std;


int main (){
  /*long a = 10, b = 100, c = 20;
  GroupOfNumbers nums(a, b, c);
  nums.displayGroupOfNumbers();
  */
  
  long d = 16;
  GroupOfNumbers nums("file.txt", d);
  nums.displayGroupOfNumbers();
  nums.writeGroupOfNumbersTo("output.txt");
  
  GroupOfNumbers funs("output.txt", d);
  funs.displayGroupOfNumbers();
}
