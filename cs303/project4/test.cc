#include <iostream>
#include "group.h"

using namespace std;
<<<<<<< HEAD
extern double user_time();
extern double system_time();
int input1 = 0, input2 = 100, input3 = 20;
long a = 5, b, start, finish;
=======
//extern double user_time();
//extern double system_time();
int input1 = 0, input2 = 100, input3 = 25;
long a = 25, b;
>>>>>>> 3d3b3420c22c9c23290c199debd93f1a4e9a28ff
bool check;

int main (){

	GroupOfNumbers nums6(input1, input2, input3);
//	cout << "----- _group -----" << endl;
//	nums6.displayGroupOfNumbers();
	cout << "----- Sort Select -----" << endl;
	start = user_time() + system_time();
	check = nums6.sort_select(a,b);	
	finish = user_time() + system_time();
	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
	cout << "Start: " << start << " Finish: " << finish << " Timing: " << finish - start << endl;
	
	GroupOfNumbers nums3(input1, input2, input3);
//	cout << "----- _group -----" << endl;
//	nums3.displayGroupOfNumbers();
	cout << "----- Partial Sort Select -----" << endl;
	start = user_time() + system_time();
	check = nums3.partial_sort_select(a,b);	
	finish = user_time() + system_time();
	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
	cout << "Start: " << start << " Finish: " << finish << " Timing: " << finish - start << endl;	

	GroupOfNumbers nums7(input1, input2, input3);
	cout << "----- Min Heap Select -----" << endl;
	start = user_time() + system_time();
	check = nums7.min_heap_select(a,b);
	finish = user_time() + system_time();
	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
	cout << "Start: " << start << " Finish: " << finish << " Timing: " << finish - start << endl;

	GroupOfNumbers nums4(input1, input2, input3);
//	cout << "----- _group -----" << endl;
//	nums4.displayGroupOfNumbers();
	cout << "----- Partial Max Heap Select -----" << endl;
	start = user_time() + system_time();	
	check = nums4.partial_max_heap_select(a,b);
	finish = user_time() + system_time();
	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
	cout << "Start: " << start << " Finish: " << finish << " Timing: " << finish - start << endl;
	
	GroupOfNumbers nums2(input1, input2, input3);
//	cout << "----- _group -----" << endl;
//	nums2.displayGroupOfNumbers();	
	cout << "----- Quick Select -----" << endl;
	start = user_time() + system_time();
	check = nums2.quick_select(a,b);	
	finish = user_time() + system_time();
	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
	cout << "Start: " << start << " Finish: " << finish << " Timing: " << finish - start << endl;	
	
	GroupOfNumbers nums1(input1, input2, input3);
//	cout << "----- _group -----" << endl;
//	nums1.displayGroupOfNumbers();
	cout << "----- Linear Select -----" << endl;
	start = user_time() + system_time();
	check = nums1.linear_select(a,b);
	finish = user_time() + system_time();
	cout << "return: " << check << " k: " << a << " kth_smallest: " << b << endl;
	cout << "Start: " << start << " Finish: " << finish << " Timing: " << finish - start << endl;
	
}
