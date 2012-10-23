//*****************************************************
// Eric Shih
// CS 303 Algorithms
// Project 1, Part A
// Fall 2012
//*****************************************************
/*
#include <cstdlib>  // include for the function exit()
#include <iostream> // include for the input/output members
#include <iomanip>  // include for input/output formatting
*/

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
	  for(i = 0; i < _LIMIT; i++){
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
    if(count < givenLimit){
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

  // mutators
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
  
  long GroupOfNumbers::Equilikely(long lower, long upper){
    return (lower + (long) ((upper - lower + 1) * Random()) );
  }//end Equilikely
