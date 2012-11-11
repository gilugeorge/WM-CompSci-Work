#include <iostream>
#include "group.h"

using namespace std;
extern double user_time();
extern double system_time();

int main (){
	double start, finish;

	//quicksort Test
	GroupOfNumbers nums(0,100,20);
	cout<< "*=====Before quicksort=====";
	nums.displayGroupOfNumbers();
	start = user_time() + system_time();
	nums.quicksort();
	finish = user_time() + system_time();
	cout<< "=====After quicksort=====";
	nums.displayGroupOfNumbers();
	cout << "Start: " << start << " Finish: " << finish;
	cout << "\nTiming: " << finish - start << endl;
	
	//quicksort first Test
	GroupOfNumbers nums2(0,100,20);
	cout<< endl << "*=====Before quicksort first=====";
	nums2.displayGroupOfNumbers();
	nums2.quick_choose_first();
	cout<< "=====After quicksort first=====";
	nums2.displayGroupOfNumbers();
	
	//quicksort middle Test
	GroupOfNumbers nums3(0,100,20);
	cout<< endl << "*=====Before quicksort middle=====";
	nums3.displayGroupOfNumbers();
	nums3.quick_choose_middle();	
	cout<< "=====After quicksort middle=====";
	nums3.displayGroupOfNumbers();
	
	//quicksort last Test
	GroupOfNumbers nums4(0,100,20);
	cout<< endl << "*=====Before quicksort last=====";
	nums4.displayGroupOfNumbers();
	nums4.quick_choose_last();	
	cout<< "=====After quicksort last=====";
	nums4.displayGroupOfNumbers();
	
}
