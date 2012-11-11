#include <iostream>
#include "group.h"

using namespace std;
extern double user_time();
extern double system_time();

int main (){
	double start, finish;
	long i;	
	long a = 1;
	//Timing Tests//
	
	//quicksort
	GroupOfNumbers nums1(0,100,250000);
	cout<< "Quicksort(Random): ";
	start = user_time() + system_time();
	nums1.quicksort();
	finish = user_time() + system_time();
	cout << "Start: " << start << " Finish: " << finish << " Timing: " << finish - start << endl;
	
	//quicksort
	GroupOfNumbers nums2(250000);
	for(i = 0; i <= 250000; i++)
		nums2.add(i);
	//nums2.displayGroupOfNumbers();
	cout<< "Quicksort(sorted): ";
	start = user_time() + system_time();
	nums2.quicksort();
	finish = user_time() + system_time();
	cout << "Start: " << start << " Finish: " << finish << " Timing: " << finish - start << endl;
	
	//quicksort
	GroupOfNumbers nums3(250000);
	for(i = 249999; i >= 0; i--)
		nums3.add(i);
	//nums3.displayGroupOfNumbers();
	cout<< "Quicksort(reverse): ";
	start = user_time() + system_time();
	nums3.quicksort();
	finish = user_time() + system_time();
	cout << "Start: " << start << " Finish: " << finish << " Timing: " << finish - start << endl;
	
	//quicksort
	GroupOfNumbers nums4(250000);
	for(i = 0; i <= 250000; i++)
		nums4.add(a);
	//nums4.displayGroupOfNumbers();
	cout<< "Quicksort(identical): ";
	start = user_time() + system_time();
	nums4.quicksort();
	finish = user_time() + system_time();
	cout << "Start: " << start << " Finish: " << finish << " Timing: " << finish - start << endl;
	
	/*
	//quicksort Test
	GroupOfNumbers nums1(0,250000,250000);
	cout<< "*=====Before quicksort=====";
	nums1.displayGroupOfNumbers();
	start = user_time() + system_time();
	nums1.quicksort();
	finish = user_time() + system_time();
	cout<< "\n=====After quicksort=====";
	nums1.displayGroupOfNumbers();
	cout << "Start: " << start << " Finish: " << finish;
	cout << "\nTiming: " << finish - start << endl;

	//quicksort first Test
	GroupOfNumbers nums2(0,100,250000);
	cout<< endl << "*=====Before quicksort first=====";
	nums2.displayGroupOfNumbers();
	nums2.quick_choose_first();
	cout<< "=====After quicksort first=====";
	nums2.displayGroupOfNumbers();
	
	//quicksort middle Test
	GroupOfNumbers nums3(0,100,250000);
	cout<< endl << "*=====Before quicksort middle=====";
	nums3.displayGroupOfNumbers();
	nums3.quick_choose_middle();	
	cout<< "=====After quicksort middle=====";
	nums3.displayGroupOfNumbers();
	
	//quicksort last Test
	GroupOfNumbers nums4(0,100,250000);
	cout<< endl << "*=====Before quicksort last=====";
	nums4.displayGroupOfNumbers();
	nums4.quick_choose_last();	
	cout<< "=====After quicksort last=====";
	nums4.displayGroupOfNumbers();
	*/
}
