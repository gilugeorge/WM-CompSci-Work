#ifndef _INTERVAL_H_
#define _INTERVAL_H_

#include <ostream>

#include "constants.h"

class interval
{
 public:
  //////////////////
  // Constrructor //
  //////////////////
  interval(float lower=-LARGE, float upper=+LARGE);
  interval(const interval& i);

  ///////////////
  // Operators //
  ///////////////
  interval& operator=(const interval& i);

  interval operator+(float v) const;
  interval operator-(float v) const;
  interval operator*(float v) const;
  interval operator/(float v) const;
    
  interval& operator+=(float v);
  interval& operator-=(float v);
  interval& operator*=(float v);
  interval& operator/=(float v);

  ////////////////
  // Inspectors //
  ////////////////
  float lower(void) const;
  float upper(void) const;

  bool empty(void) const;

  //////////////
  // Mutators //
  //////////////
  void intersect(const interval& i);

  /////////////
  // Friends //
  /////////////
  friend void swap(interval& a, interval& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const interval& i)
  {
    s << "[" << i.lower() << ", " << i.upper() << "]";
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _assign(const interval& i);
  void _swap(interval& i);

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  float _lower, _upper;
};

#endif /* _INTERVAL_H_ */

