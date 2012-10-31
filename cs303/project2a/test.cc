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
	
	//Mergesort Test
	GroupOfNumbers nums2(0,100,50);
	cout<< "=====Before mergeSort Sort=====" << endl;
	nums2.displayGroupOfNumbers();
	nums2.mergesort();	
	cout<< "=====After mergeSort Sort=====" << endl;
	nums2.displayGroupOfNumbers();
	
	//heapsort Test
	GroupOfNumbers nums3(0,100,50);
	cout<< "=====Before heapsort Sort=====" << endl;
	nums3.displayGroupOfNumbers();
	nums3.heapsort();	
	cout<< "=====After heapsort Sort=====" << endl;
	nums3.displayGroupOfNumbers();
	
	//quicksort Test
	GroupOfNumbers nums4(0,100,50);
	cout<< "=====Before quicksort Sort=====" << endl;
	nums4.displayGroupOfNumbers();
	nums4.heapsort();	
	cout<< "=====After quicksort Sort=====" << endl;
	nums4.displayGroupOfNumbers();
}
