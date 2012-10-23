/*Eric Shih
 *This program takes in a 16 bit pattern and does an and bitwise
 *function to find which location are turned on (1) or off (0).
 */

#include <stdio.h>
#include <math.h>
int onMachines(int vector);
void checkMachines(int v1, int v2);

int main(){
  int vector1, vector2;
  int v1, v2;


  //extract vectors
  printf("Input Vector 1: ");
  scanf("%x", &vector1);
  printf("Input Vector 2: ");
  scanf("%x", &vector2);
  
  //find count of machines on
  v1 = onMachines(vector1);
  v2 = onMachines(vector2);

  //print number of machines
  printf("Number of busy machines (vector 1): %d\n",v1);
  printf("Number of busy machines (vector 2): %d\n", v2);
  
  //find the change between machines and outputs which machines have changed state
  checkMachines(vector1, vector2);  
  
  return 0;
}//main

/*This function counts the number of on machines by doing basic
 *subtraction with the 
 */
int onMachines(int vector){
  int count = 0;
  int x;

  for(x = 15; x >= 0; x--){
    if(pow(2, x) <= vector){
      vector -= pow(2, x);
      count++;
    }
  }


  return count;
}//onMachines

/*This function is very similar to onMachines, except that it gets
 *difference between the on machines.
 */
void checkMachines(int v1, int v2){
  int combined = v1 ^ v2; //the bitwise combination of the two numbers
  int count = 0;
  int x;

  printf("Machines that changed state: ");
  for(x = 15; x >= 0; x--){
    if(pow(2, x) <= combined){
      combined -= pow(2, x);
      printf(" %d", count);
    }
    count++;
  }

  printf("\n");
}//checkMachines
