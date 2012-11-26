#include <iostream>
#include "group.h"

using namespace std;
//extern double user_time();
//extern double system_time();
int input1 = 0, input2 = 100, input3 = 20;
long a = 5, b;

int main (){
//	double start, finish; //timing variables
//	long i;	//loop iterator
//	long a = 1; //number used for identical elements
	GroupOfNumbers nums1(input1, input2, input3);
//	cout << "----- _group -----" << endl;
//	nums1.displayGroupOfNumbers();
	cout << "----- Sort Select -----" << endl;
	bool check = nums1.sort_select(a,b);
	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
	
	GroupOfNumbers nums2(input1, input2, input3);
//	cout << "----- _group -----" << endl;
//	nums2.displayGroupOfNumbers();
	cout << "----- Quick Select -----" << endl;
	nums2.quick_select(a,b);	
	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
	
	GroupOfNumbers nums3(input1, input2, input3);
	cout << "----- _group -----" << endl;
	nums3.displayGroupOfNumbers();
	cout << "----- Partial Sort Select -----" << endl;
	nums3.partial_sort_select(a,b);	
	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
}
