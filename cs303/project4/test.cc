#include <iostream>
#include "group.h"

using namespace std;
//extern double user_time();
//extern double system_time();
int input1 = 0, input2 = 100, input3 = 25;
long a = 1, b;
bool check;

int main (){
	GroupOfNumbers nums1(input1, input2, input3);
	cout << "----- _group -----" << endl;
	nums1.displayGroupOfNumbers();
	cout << "----- Linear Select -----" << endl;
	bool check = nums1.linear_select(a,b);
	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
	
//	GroupOfNumbers nums2(input1, input2, input3);
//	cout << "----- _group -----" << endl;
//	nums1.displayGroupOfNumbers();	
//	cout << "----- Quick Select -----" << endl;
//	check = nums1.quick_select(a,b);	
//	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;	
//	cout << "----------" << endl;
//	nums1.insertion_sort();
//	nums1.displayGroupOfNumbers();
	
//	GroupOfNumbers nums3(input1, input2, input3);
//	cout << "----- _group -----" << endl;
//	nums3.displayGroupOfNumbers();
//	cout << "----- Partial Sort Select -----" << endl;
//	check = nums3.partial_sort_select(a,b);	
//	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
//	
//	GroupOfNumbers nums4(input1, input2, input3);
//	cout << "----- _group -----" << endl;
//	nums4.displayGroupOfNumbers();
//	cout << "----- Partial Max Heap Select -----" << endl;
//	check = nums4.partial_max_heap_select(a,b);	
//	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
//	check = nums4.quick_select(a,b);	
//	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;

//	GroupOfNumbers nums5(input1, input2, input3);
//	cout << "----- _group -----" << endl;
//	nums5.displayGroupOfNumbers();
//	
//		cout << "----- Sort Select -----" << endl;
//	check = nums5.partial_sort_select(a,b);
//	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
//	
//	cout << "----- Min Heap Select -----" << endl;
//	check = nums5.min_heap_select(a,b);	
//	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;

//	nums5.displayGroupOfNumbers();	
}
