#include <iostream>
#include "group.h"

using namespace std;


int main (){
	//Insertion Test
	GroupOfNumbers nums(0,50,20);
	cout<< "=====Before Insertion Sort=====" << endl;
	nums.displayGroupOfNumbers();
	nums.insertion_sort();	
	cout<< "=====After Insertion Sort=====" << endl;
	nums.displayGroupOfNumbers();
	
}
