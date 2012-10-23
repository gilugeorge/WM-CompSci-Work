#include <stdio.h>
#include <math.h>

 int sum(int *numbers, unsigned short count)
 {
  int x;
  int total = 0;

  for(x = 0;x < count;x++){
    total += numbers[x];
  }//for
 
    return  total;
 }//sum

 double average(int *numbers, unsigned short count)
 {
  int x;
  int avg = 0;
  
  if(count == 0){
   return 0;
  }
 
  for(x = 0;x < count;x++){
    avg += numbers[x];
  }//for
    avg = avg/count;
 
    return  avg;
 }//average
 
 double sd(int *numbers, unsigned short count)
 {
  int x;
  int add;
  double final = 0;
  int avg = average(numbers,count);
  
  for(x = 0; x<count; x++){
   add = numbers[x]-avg;
   add = pow(add, 2);
   final += add;
  }//for
   
   final = final/count; 
   final = sqrt(final);

  return final;
 }//sd

