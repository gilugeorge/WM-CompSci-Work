//*****************************************************
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

using namespace std;

  // constructors
  // ============

	// The default constructor.  If the user gives no default
  // limit on the maximum possible size of the group of numbers,
  // default_LIMIT is assumed.  But the limit on the total
  // number of entries that can be represented using the
  // GroupOfNumbers class object should be the maximum of
  // default_Limit and whatever limit the user provides.
  // Error handling:
  //  exits with 1 if there is insufficient memory available to
  //  create a GroupOfNumbers object with defaultLimit entries.
  GroupOfNumbers::GroupOfNumbers(long defaultLimit) : _LIMIT(defaultLimit), _total(0){
    if (defaultLimit < default_LIMIT) {
	    _LIMIT = default_LIMIT;
    }
    try{
	    _group = new long[_LIMIT];
    }catch(bad_alloc){
	    cerr << " GroupOfNumbers: bad_alloc " << endl;
	    cerr << " GroupOfNumbers: allocation of size " << _LIMIT << " failed" << endl;
	    cerr << " GroupOfNumbers: line: " << (__LINE__ - 5) << endl;
	    cerr << " GroupOfNumbers: file " << __FILE__ << endl;
	    cerr << " GroupOfNumbers: exit: " << 1 << endl;
	    exit(1);
    }//end catch
  }// end default constructor

	// The default copy constructor (deep copy).
  // The deep copy should be identical in every respect.
  // Error handling:
  //  exits with 1 if there is insufficient memory available to
  //  create a GroupOfNumbers object identical to G.
  GroupOfNumbers::GroupOfNumbers(const GroupOfNumbers & G): _LIMIT(default_LIMIT), _total(0), _group(NULL) {
  	*this = G;
	}//constructor G

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
		    cerr << "operator bad_alloc" << endl;
		    cerr << "GroupOfNumbers: bad_alloc" << endl;
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
