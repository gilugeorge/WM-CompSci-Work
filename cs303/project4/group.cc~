//*****************************************************
// Eric Shih
// CS 303 Algorithms
// Project 3
// Fall 2012
//*****************************************************


#include "group.h"
#include "rng.h"

using namespace std;

  // constructors
  // ============

	/** The default constructor. Will set default limit as the _LIMIT if given size
	    is not great enough. Then creates the empty array _group.
   Error handling:
    exits with 1 if there is insufficient memory available to
    create a GroupOfNumbers object with defaultLimit entries.
  */
  GroupOfNumbers::GroupOfNumbers(long defaultLimit)
      : _LIMIT(defaultLimit), _total(0){
    if (defaultLimit < default_LIMIT) {
	    _LIMIT = default_LIMIT;
    }
    try{
	    _group = new long[_LIMIT];
    }catch(bad_alloc){
	    cerr << " GroupOfNumbers: bad_alloc " << endl;
	    cerr << " GroupOfNumbers: allocation of size " << _LIMIT << " failed" 
	      << endl;
	    cerr << " GroupOfNumbers: line: " << (__LINE__ - 5) << endl;
	    cerr << " GroupOfNumbers: file " << __FILE__ << endl;
	    cerr << " GroupOfNumbers: exit: " << 1 << endl;
	    exit(1);
    }//end catch
  }// end default constructor

	/* The default copy constructor (deep copy).
     The deep copy should be identical in every respect.
  */
  GroupOfNumbers::GroupOfNumbers(const GroupOfNumbers & G)
      : _LIMIT(default_LIMIT), _total(0), _group(NULL) {
  	*this = G;
	}//constructor G

  /* Initialize GroupOfNumbers with a requested number of entries in the array.
     Entries are of a random number between lower and upper.
  */
  GroupOfNumbers::GroupOfNumbers(long lower, long upper, long total_requested)
      :_LIMIT(total_requested), _total(0) {
    long i;
    if (lower > upper){
      cerr << " GroupOfNumbers: " << "incorrect values for the arguments lower and upper: ("
        << lower << "," << upper << ")" << endl;
      cerr << " GroupOfNumbers: " << "lower is required to be less than or equal to upper" << endl;
      cerr << " GroupOfNumbers: " << (__LINE__ - 6) << endl;
      cerr << " GroupOfNumbers: file: " << __FILE__ << endl;
	    cerr << " GroupOfNumbers: exit: " << 2 << endl;
      exit(2);
    }
    if (total_requested < default_LIMIT) {
	    _LIMIT = default_LIMIT;
    }else{
      _LIMIT = total_requested;
    }
    try{
	    _group = new long[_LIMIT];
    }catch(bad_alloc){
	    cerr << " GroupOfNumbers: bad_alloc " << endl;
	    cerr << " GroupOfNumbers: allocation of size " << _LIMIT << " failed"<< endl;
	    cerr << " GroupOfNumbers: line: " << (__LINE__ - 5) << endl;
	    cerr << " GroupOfNumbers: file " << __FILE__ << endl;
	    cerr << " GroupOfNumbers: exit: " << 1 << endl;
	    exit(1);
	  }
	  //cout << "Size(ln 87 group): " << _LIMIT << endl;
	  for(i = 0; i < total_requested; i++){
	    add(Equilikely(lower,upper));
	  }
  }//

  /* Initialize the new GroupOfNumbers object with numbers from a file.
  
   Error handling:
    1- there is insufficient memory available
    3- file fname cannot be opened/found.  
    4- number of entries available in the file fname is incompatible with
       the array size.  
    5- number of entries actually available in the file fname is discovered to be fewer than
       total_requested.
  */  
  GroupOfNumbers::GroupOfNumbers(const char* fname, long total_requested)
      : _LIMIT(total_requested), _total(0){
    //allocate an array of sufficient size
    if (total_requested < default_LIMIT) {
	    _LIMIT = default_LIMIT;
    }else{
      _LIMIT = total_requested;
    }
    try{
	    _group = new long[_LIMIT];
    }catch(bad_alloc){
	    cerr << " GroupOfNumbers: bad_alloc " << endl;
	    cerr << " GroupOfNumbers: allocation of size " << _LIMIT << " failed"<< endl;
	    cerr << " GroupOfNumbers: line: " << (__LINE__ - 5) << endl;
	    cerr << " GroupOfNumbers: file " << __FILE__ << endl;
	    cerr << " GroupOfNumbers: exit: " << 1 << endl;
	    exit(1);
	  }
    //open the file fname
    ifstream myfile;
    myfile.open(fname);
    if(!myfile){
      cerr << " GroupOfNumbers: " << fname << ": No such file" << endl;
      cerr << " GroupOfNumbers: line: " << (__LINE__ - 3) << endl;
	    cerr << " GroupOfNumbers: file " << __FILE__ << endl;
	    cerr << " GroupOfNumbers: exit: " << 3 << endl;
      exit(3);
    }
    
    //find # of entries in fname
    string str;
    getline(myfile, str);    
    long givenLimit = atol(str.c_str());
    //cout << i << endl;
    if(givenLimit < total_requested){
      cerr << " GroupOfNumbers: Insufficient number of entries in file: "<< fname << endl;
	    cerr << " GroupOfNumbers: Number requested from file: " << total_requested << endl;
	    cerr << " GroupOfNumbers: Number reputedly available: " << givenLimit << endl;	    
	    cerr << " GroupOfNumbers: line: " << (__LINE__ - 5) << endl;
	    cerr << " GroupOfNumbers: file " << __FILE__ << endl;
	    cerr << " GroupOfNumbers: exit: " << 4 << endl;
	    exit(4);
    }
            
    //initilize entries from fname into array
    long fileNum, count = 0;
    while(myfile >> fileNum && (count <= total_requested)){
      add(fileNum);
      count++;
    }
    if(count < total_requested){
      cerr << " GroupOfNumbers: Insufficient number of entries in file: "<< fname << endl;
	    cerr << " GroupOfNumbers: Number requested from file: " << total_requested << endl;
	    cerr << " GroupOfNumbers: Number reputedly available: " << givenLimit << endl;	    
	    cerr << " GroupOfNumbers: Number actually available: " << count << endl;	    
	    cerr << " GroupOfNumbers: line: " << (__LINE__ - 5) << endl;
	    cerr << " GroupOfNumbers: file " << __FILE__ << endl;
	    cerr << " GroupOfNumbers: exit: " << 5 << endl;
	    exit(5);
    }    

    //close fname before the return
    myfile.close();    
  }//end fname constructor

  // destructor
  // ==========
  GroupOfNumbers::~GroupOfNumbers(){
  	delete [] _group;
  }//end destructor

  // accessors
  // =========

  // Returns true if the group is empty;
  // otherwise, returns false.
  bool GroupOfNumbers::isEmpty() const {
	  return ( _total == 0);
  }//end isEmpty

  // Returns the total number of entries in the group.
  long GroupOfNumbers::total() const{
    return _total;
  }//end total

  // Displays the numbers in the group, separated by one blank
  // space, with a carriage return after every 10 numbers.
  void GroupOfNumbers::displayGroupOfNumbers() const{
    long i;
	  cout.setf(ios::right);
	  for(i = 0; i< _total; i++){
		  if((i%10) == 0)
			  cout << "\n" << setw(8) << _group[i];
		  else
			  cout << setw(8) << _group[i];
	  }
    cout << endl;
  }//end displayGroupOfNumbers
  
  // Writes to the file fname:
  // - the number of entries in the group (which should be the first
  //   entry on the first line of the file, followed by a carriage return)
  // - all the numbers in the group (each separated by one blank
  //   space, with a carriage return after every 10 numbers).
  // Closes the file before returning.
  void GroupOfNumbers::writeGroupOfNumbersTo(const char* fname) const{
    ofstream outFile;
    outFile.open(fname);
    long i;
	  outFile.setf(ios::right);
	  outFile << " " << total() << endl;
	  for(i = 0; i< _total; i++){
		  if((i%10) == 0)
			  outFile << "\n" << " " << _group[i];
		  else
			  outFile << " " << _group[i];
	  }
    cout << endl;
    outFile.close();
  }//end writeGroupOfNumbersTo

  // Each of the following methods returns the kth smallest
  // number in the group in the argument kth_smallest.
  // **The original group is unchanged.
  // The return value for each of these methods is true if the
  // value of k is valid (i.e., 1 <= k <= total()); otherwise,
  // the return value of each of these methods is false.
  // The difference is in the algorithm used, and thus in the
  // time complexity that can either be expected (or guaranteed).
  bool GroupOfNumbers::sort_select(long k, long & kth_smallest) const{
   	if(k < 1 || k > _total)
  		return false;
  	
  	long* temp_group = new long[_total];
  	for(int i = 0; i < _total; i++){
  		temp_group[i] = _group[i];
  	}
  	insertion_sort(temp_group, 0, total());
		
//		output_temp_group(temp_group);  	
	
  	kth_smallest = temp_group[k-1];
  	delete[] temp_group;
  	return true;
  }//sort_select
 	void GroupOfNumbers::insertion_sort(long *temp_group, long left, long right) const{
 		int i, j;
 		for(i = left; i < right; i++){
 			long temp = temp_group[i];
 			for(j = i; j > left && temp < temp_group[j-1]; j--){
 				temp_group[j] = temp_group[j-1];
 			}
 			temp_group[j] = temp;
 		}
 	}//insertion_sort
  
  bool GroupOfNumbers::partial_sort_select(long k, long & kth_smallest) const{
   	if(k < 1 || k > _total)
			return false;
  	long* temp_group = new long[_total];
  	for(int i = 0; i < _total; i++){
  		temp_group[i] = _group[i];
  	}
		insertion_sort(temp_group, 0, k);
		int i;
		for(i = k; i < _total; i++){
				if (temp_group[i] < temp_group[k-1]){
					temp_group[k-1] = temp_group[i];
					for(int j = k-1; j >0; j--){
						if(temp_group[j] < temp_group[j-1]){
							swap(temp_group[j] , temp_group[j-1]);
						}
						else{
							break;
						}
					}
				}
		}
		
//		output_temp_group(temp_group);
		
		kth_smallest = temp_group[k-1];
		delete[] temp_group;
		return true;
  }//partial_sort_select
  
  bool GroupOfNumbers::min_heap_select(long k, long & kth_smallest) const{
   	if(k < 1 || k > _total)
  		return false;
  		
		long* temp_group = new long[_total+1];
  	for(int i = 0; i < _total; i++){
  		temp_group[i+1] = _group[i];
  	}
	
		long currentSize = _total;
		for( int i = _total / 2; i > 0; i-- )
			percolate_down2(temp_group, i, _total );

//		long tempMin;
		for(int i = 0; i < k; i++ ){
//			tempMin= temp_group[1];
			temp_group[ 1 ] = temp_group[currentSize-- ]; 
			percolate_down2(temp_group, 1, currentSize);
		}
		
//		output_temp_group(temp_group);
		kth_smallest = temp_group[1];
		return true;
  }//min_heap_select
  void GroupOfNumbers::percolate_down2(long* temp_group, long hole, long currentSize ) const{

		long child;
		long temp = temp_group[ hole ];

		for( ; hole * 2 <= currentSize; hole = child ){
			child = hole * 2;
			if( child != currentSize && temp_group[ child + 1 ] < temp_group[ child ]){
				child++;	
			}
			if( temp_group[ child ] < temp ){
				temp_group[ hole ] = temp_group[ child ];
			}
			else
				break;
		}
		temp_group[ hole ] = temp;
	}//percolate_down2
  
  bool GroupOfNumbers::partial_max_heap_select(long k, long & kth_smallest) const{
   	if(k < 1 || k > _total)
  		return false;
		
  	long* temp_group = new long[_total];
  	for(int i = 0; i < _total; i++){
  		temp_group[i] = _group[i];
  	}
		int x;
		for( int i = k / 2; i >= 0; i-- ) /* buildHeap */
			percolate_down(temp_group, i, k);
		
		for(x = k; x < _total; x++){
			if(temp_group[x] < temp_group[0]){
				long temp_hold = temp_group[x]; //delete max
				temp_group[x] = temp_group[0];
				temp_group[0] = temp_hold;
				percolate_down(temp_group, 0, k);
			}
		}
		
//		output_temp_group(temp_group);
		kth_smallest= temp_group[0];
		delete[] temp_group;
		return true;
  }//partial_max_heap_select
  void GroupOfNumbers::percolate_down(long *temp_group, long i, long n)const{
  	long child, tmp;
  	
  	for(tmp = temp_group[i]; left_child(i) < n; i = child){
  		child = left_child(i);
  		if(child != n-1 && temp_group[child] < temp_group[child+1])
  			child++;
  		if(tmp < temp_group[child])
  			temp_group[i] = temp_group[child];
  		else
  			break;
  	}
  	_group[i] = tmp;
  }
  
  bool GroupOfNumbers::quick_select(long k, long & kth_smallest) const{
   	if(k < 1 || k > _total)
  		return false;
  	long* temp_group = new long[_total];
  	for(int i = 0; i < _total; i++){
  		temp_group[i] = _group[i];
  	}
//  	output_temp_group(temp_group);
  	quick_select(temp_group, 0, total()-1, k);
  	
//  	output_temp_group(temp_group);
  	
  	kth_smallest = temp_group[k-1];
//  	cout << kth_smallest << temp_group[k-1]<< endl;
		delete[] temp_group;
  	return true;
  }//quick_select
	void GroupOfNumbers::quick_select(long *temp_group, long left, long right, long k) const{
		if(left + CutOff <= right){
  		long pivot = median_of_3(temp_group,left, right);
//  		output_temp_group(temp_group);
  		long i = left, j = right-1;
  		for(;;){
  			while(temp_group[++i] < pivot){}
  			while(pivot < temp_group[--j]){}
  			if(i < j)
  				swap(temp_group[i], temp_group[j]);
  			else
  				break;
  		}
  		swap(temp_group[i], temp_group[right-1]); //Restore Pivot
  		if(k <= i){
	  		quick_select(temp_group, left, i, k); //sort small elements
  		}else if(k > i+1){ // if k=(i+1). No need to sort. As (i+1)th item is the pivot element.
  			quick_select(temp_group, i, right, k);
 		 	}
  	}else{ //do an insertion sort on the subarrays
  			insertion_sort(temp_group, left,right);  		
  	}	
	}//quick select
	long GroupOfNumbers::median_of_3(long *temp_group, long left, long right)const{
		int center = (left + right) / 2;
		if(temp_group[center] < temp_group[left])
			swap(temp_group[left], temp_group[center]);
    if( temp_group[right] < temp_group[left] )
        swap( temp_group[left], temp_group[right] );
    if( temp_group[right] < temp_group[center] )
        swap( temp_group[center], temp_group[right] );
        // Place pivot at position right - 1
    swap( temp_group[center], temp_group[right - 1] );
    return temp_group[right - 1];
  }
  
  bool GroupOfNumbers::linear_select(long k, long & kth_smallest) const{
  	if(k < 1 || k > _total)
  		return false;
  	long* temp_group = new long[_total];
  	for(int i = 0; i < _total; i++){
  		temp_group[i] = _group[i];
  	}
  //	output_temp_group(temp_group);
  	linear_select(temp_group, 0, total()-1, k);
  	
  	output_temp_group(temp_group);
  	
  	kth_smallest = temp_group[k-1];
//  	cout << kth_smallest << temp_group[k-1]<< endl;
		delete[] temp_group;
  	return true;
  }//public linear_select
  
  void GroupOfNumbers::linear_select(long *temp_group, long left, long right, long k) const{
  	if(left + CutOff <= right){
  		long pivot = median_of_median_of_5(temp_group, left, right);
//				long pivot = momo_five(temp_group, left, right);
//  		cout << "Pivot: " << pivot << endl;
//  		cout << "Left: " << left << endl;
//  		cout << "Right: " << right << endl;  		  		
//  		output_temp_group(temp_group);
  		
  		long i = left-1, j = right+1;
  		for(;;){
  			while(temp_group[++i] < pivot){}
  			while(pivot < temp_group[--j]){}
  			if(i < j)
  				swap(temp_group[i], temp_group[j]);
  			else
  				break;
  		}
//  		cout << "i " << i << endl;
//  		cout << "j: " << j << endl;
//  		output_temp_group(temp_group);  		
  		swap(temp_group[i], temp_group[right-1]); //Restore Pivot	
  		if(k <= i){
	  		linear_select(temp_group, left, i, k); //sort small elements
  		}else if(k > i+1){ // if k=(i+1). No need to sort. As (i+1)th item is the pivot element.
  			linear_select(temp_group, i, right, k);
 		 	}
		}else{ //do an insertion sort on the subarrays
			insertion_sort(temp_group, left,right+1);
  	}
  }//protected linear_select 

  //median of median of 5 used for linear select
	long GroupOfNumbers::median_of_median_of_5(long *tempArr, long left, long right) const{
		//output_temp_group(tempArr);
//		cout<< temp_size << endl;
		long temp_size= right-left+1;
		long *median_5= new long[temp_size];
		long *med_med= new long[(temp_size/5)];
		if(temp_size>=5){
			int k = 0;
			for(int i=left; i<(left+temp_size/5); i++){
				for(int j=0; j<5; j++){
					median_5[(5*k)+j]= tempArr[left+(5*k)+j];
				}
				k++;
			}
			for(int m=0; m< temp_size/5; m++){
				int temp_m= m*5;
				if(median_5[temp_m]>median_5[temp_m+1])
					swap(median_5[temp_m], median_5[temp_m+1]);
				if(median_5[temp_m+3]>median_5[temp_m+4])
					swap(median_5[temp_m+3], median_5[temp_m+4]);
				if(median_5[temp_m]>median_5[temp_m+3])
					swap(median_5[temp_m], median_5[temp_m+3]);
				if(median_5[temp_m+1]>median_5[temp_m+4])
					swap(median_5[temp_m+1], median_5[temp_m+4]);
				if(median_5[temp_m+2]>median_5[temp_m+3])
					swap(median_5[temp_m+2], median_5[temp_m+3]);
				if(median_5[temp_m+1]>median_5[temp_m+2])
					swap(median_5[temp_m+1], median_5[temp_m+2]);
				if(median_5[temp_m+2]>median_5[temp_m+3])
					swap(median_5[temp_m+2], median_5[temp_m+3]);
//				swap(median_5[m+2], median_5[m+3]);
//				insertion_sort(median_5, temp_m, temp_m+4);
//				cout << "----median 5----" << endl;
//				output_temp_group(median_5);
				med_med[m]= median_5[temp_m+2];
			}
			return med_med[temp_size/10];
//			return median_of_median_of_5(med_med, temp_size/5);
		}else{ //if the size is less than 5, return the indiv number
			if(temp_size==4){
				return tempArr[1];
			}else if(temp_size==3){
				return tempArr[1];
			}else if(temp_size==2){
				return tempArr[0];
			}
			return tempArr[0];
		}
	}//med of med of 5

  
 	void GroupOfNumbers::output_temp_group(long *temp_group)const{
  	long i;
	  for(i = 0; i< _total; i++){
		  if((i%10) == 0)
			  cout << "\n" << setw(8) << temp_group[i];
		  else
			  cout << setw(8) << temp_group[i];
	  }
    cout << endl;  	
 	}//
  // MUTATORS
  // ========

  /* If possible, adds newNumber to the group---duplicates
   * allowed; returns true if newNumber can be added to
   * the group and false if the addition of newNumber
   * to the group is not possible because the array is full.
   */
  bool GroupOfNumbers::add(const long& newNumber){
    bool success = (_total < _LIMIT);
  	if (success){
      _group[_total] = newNumber;
      _total++;
    }
    return success;
  }//end add


  // If Number is contained in the group, remove one instance of
  // Number from the group; i.e., if the group contains more than
  // one entry with the same value as Number (duplicates are
  // allowed), only one instance is removed. Returns false if
  // Number is not contained in the group; otherwise, returns true.
  bool GroupOfNumbers::remove(const long& Number){
    bool success;
	  long i;
	  //first, find the culprit
	  for(i = 0; (i < _total) && (_group[i] != Number); i++)
      {}
	  success = (i < _total);
    //if its successful, then remove
	  if(success){
		  _group[i] = _group[--_total];
	  }
    return success;
  }//end remove

  // The assignment should be identical in every respect.
  // Error handling:
  //  exits with 1 if there is insufficient memory available to
  //  assign an identical copy of G to the attached object.
  GroupOfNumbers& GroupOfNumbers::operator=(const GroupOfNumbers& G){
	  if(this != &G){
		  delete[] _group;
		  try{
			  _group = new long [G._LIMIT];
		  }catch(bad_alloc){
		    cerr << " operator bad_alloc" << endl;
		    cerr << " GroupOfNumbers: bad_alloc" << endl;
		    cerr << " GroupOfNumbers: allocation of size " << _LIMIT << " failed" <<endl;
		    cerr << " GroupOfNumbers: line: " << (__LINE__ - 5) << endl;
		    cerr << " GroupOfNumbers: file " << __FILE__ << endl;
		    cerr << " GroupOfNumbers: exit: " << 1 << endl;
		    exit(1);
      }//end catch
		  _LIMIT = G._LIMIT;
		  long i;
		  for(i = 0; i < G._total; i++){
			  _group[i] = G._group[i];
		  }
		  _total = G._total;
	  }//end if

	  return *this;
  }//end operator=
  
  /** Sorting algorithms **/
  /***************************************/
	/*Implementation of Weiss's insertion_sort*/
  void GroupOfNumbers::insertion_sort(){
 		insertion_sort(0,total());
  }//insertion_sort
	// protected method for insertion sort
  void GroupOfNumbers::insertion_sort(long left, long right){
  	int j;  	
  	for(int p = left; p < right; p++){
	  	long tmp = _group[p];
	  	for( j = p; j > 0 && tmp < _group[j-1]; j--){
	  		_group[j] = _group[j-1];
	  	}
	  	_group[j] = tmp;
  	} 
  }
  
	/*Implementation of Weiss's heapsort*/
  void GroupOfNumbers::heapsort(){
  	for(int i = total()/2; i >= 0; i--) /* buildHeap */
  		percolate_down(i, total() );
  	for(int j = total() - 1; j > 0; j--){
  		//swap(_group[0], _group[j]);
  		long temp = _group[0];
  		_group[0] = _group[j];
  		_group[j] = temp;
  		percolate_down(0, j);
  	}
  }//heapsort
  // protected methods for heapsort
  void GroupOfNumbers::percolate_down(long i, long n){
  	long child, tmp;
  	
  	for(tmp = _group[i]; left_child(i) < n; i = child){
  		child = left_child(i);
  		if(child != n-1 && _group[child] < _group[child+1])
  			child++;
  		if(tmp < _group[child])
  			_group[i] = _group[child];
  		else
  			break;
  	}
  	_group[i] = tmp;
  }
  
	/*Implementation of Weiss's mergesort*/
  void GroupOfNumbers::mergesort(){
  	long* temp_group = new long[_total];
  	mergesort(temp_group, 0, total()-1);
  }//mergesort
  // protected methods for mergesort
  void GroupOfNumbers::mergesort(long *temp_group, long left, long right){
  	if(left < right){
  		long center = (left + right) / 2;
  		mergesort(temp_group, left, center);
  		mergesort(temp_group, center+1, right);
  		merge(temp_group, left, center+1, right);  	
  	}
  }  
  void GroupOfNumbers::merge(long *temp_group, long leftPos, long rightPos, long rightEnd){
  	long leftEnd = rightPos - 1;
  	long tmpPos = leftPos;
  	long numElements = rightEnd - leftPos + 1;
  	
  	while(leftPos <= leftEnd && rightPos <= rightEnd)
  		if(_group[leftPos] <= _group[rightPos])
  			temp_group[tmpPos++] = _group[leftPos++];
  		else
  			temp_group[tmpPos++] = _group[rightPos++];
  	while(leftPos <= leftEnd) //Copy rest of first half
  		temp_group[tmpPos++] = _group[leftPos++];
  	while(rightPos <= rightEnd) //Copy rest of right half
  		temp_group[tmpPos++] = _group[rightPos++];
  		
  	//Copy tmpArray back
  	for(int i = 0; i < numElements; i++, rightEnd--)
  		_group[rightEnd] = temp_group[rightEnd];
  }
  
 	/*Implementation of Weiss's quicksort*/
  void GroupOfNumbers::quicksort(){
  	quicksort(0, total()-1);
  }//quicksort
  // protected methods for quicksort
  void GroupOfNumbers::quicksort(long left, long right){
  	if(left + CutOff <= right){
  		long pivot = median_of_3(left, right);
  		
  		long i = left, j = right-1;
  		for(;;){
  			while(_group[++i] < pivot){}
  			while(pivot < _group[--j]){}
  			if(i < j)
  				swap(_group[i], _group[j]);
  			else
  				break;
  		}
  		
  		swap(_group[i], _group[right-1]); //Restore Pivot
  		quicksort(left, i-1); //sort small elements
  		quicksort(i+1, right); //sort large elements  		
  	}else //do an insertion sort on the subarrays
  		insertion_sort(left,right+1);  	
  }
  
  long GroupOfNumbers::median_of_3(long left, long right){
		int center = (left + right) / 2;
		if(_group[center] < _group[left])
			swap(_group[left], _group[center]);
    if( _group[right] < _group[left] )
        swap( _group[left], _group[right] );
    if( _group[right] < _group[center] )
        swap( _group[center], _group[right] );

        // Place pivot at position right - 1
    swap( _group[center], _group[right - 1] );
    return _group[right - 1];
  }
  
  /* Quicksort Pivot Alternative Methods */
  // always uses the first element of the partition(left) as the pivot for quicksort
  void GroupOfNumbers::quick_choose_first(){
	 	quick_choose_first(0, total()-1);
  }
  void GroupOfNumbers::quick_choose_first(long left, long right){
  	if(left + CutOff <= right){
  		long pivot = _group[left];
  		
  		long i = left, j = right + 1;
  		for(;;){
  			while(i < right && _group[++i] < pivot){}
  			while(j > left && pivot < _group[--j]){}
  			if(i < j)
  				swap(_group[i], _group[j]);
  			else
  				break;
  		}
  		
  		swap(_group[left], _group[j]); //Restore Pivot
  		quick_choose_first(left, j-1); //sort small elements
  		quick_choose_first(j + 1, right); //sort large elements  		
  	}else //do an insertion sort on the subarrays
  		insertion_sort(left,right+1); 
  		
  	/*for(int x = 0; x<right;x++){
  		if(x+1 > right ||	 _group[x]>_group[x+1]){
  			cout<<"!!!check failed!!!"<<endl;
  			exit(1);
  		}
  	}*/
  		
  }
  
  // always uses the middle element of the partition((left + right)/2) as the pivot for quicksort
  void GroupOfNumbers::quick_choose_middle(){
 	 	quick_choose_middle(0, total()-1);
  }
  void GroupOfNumbers::quick_choose_middle(long left, long right){
   	if(left + CutOff <= right){
  		long pivot = _group[(left + right)/2];
  		swap(_group[right],_group[(left+right)/2]);
  		long i = left, j = right-1;
  		for(;;){
  			while(_group[++i] < pivot){}
  			while(j > left && pivot < _group[--j]){}
  			if(i < j)
  				swap(_group[i], _group[j]);
  			else
  				break;
  		}
  		
  		swap(_group[i], _group[right]); //Restore Pivot
  		quick_choose_middle(left, i); //sort small elements
  		quick_choose_middle(i, right); //sort large elements  		
  	}else //do an insertion sort on the subarrays
  		insertion_sort(left,right+1);
  		
  	/*for(int x = 0; x<right;x++){
  		if(x+1 > right || _group[x]>_group[x+1]){
  			cout<<"!!!check failed!!!"<<endl;
  		}
  	}*/	  	
  }

  // always uses the last element of the partition (right) as the pivot for quicksort
  void GroupOfNumbers::quick_choose_last(){
 	 	quick_choose_last(0, total()-1);
  }
  void GroupOfNumbers::quick_choose_last(long left, long right){
   	if(left + CutOff <= right){
  		long pivot = _group[right];  		
  		long i = left, j = right-1;
  		for(;;){
  			while(i <= right && _group[++i] < pivot){}
  			while(j >= left && pivot < _group[--j]){}
  			if(i < j)
  				swap(_group[i], _group[j]);
  			else
  				break;
  		}
  		
  		swap(_group[i], _group[right]); //Restore Pivot
  		quick_choose_last(left, i - 1); //sort small elements
  		quick_choose_last(i, right); //sort large elements  		
  	}else //do an insertion sort on the subarrays
  		insertion_sort(left,right+1);
  		
  	/*for(int x = 0; x<right;x++){
  		if(x+1 > right || _group[x]>_group[x+1]){
  			cout<<"!!!check failed!!!"<<endl;
  		}
  	}*/		  	
  }

  long GroupOfNumbers::Equilikely(long lower, long upper){
    return (lower + (long) ((upper - lower + 1) * Random()) );
  }//end Equilikely
