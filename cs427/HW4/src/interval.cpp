#include "interval.h"
#include "constants.h"

//////////////////
// Constrructor //
//////////////////
interval::interval(float lower, float upper)
{
  _lower = lower;
  _upper = upper;

  // ensure that _lower < _upper
  if(_upper < _lower) std::swap(_upper, _lower);
}


interval::interval(const interval& i)
{
  _lower = i._lower;
  _upper = i._upper;
}



///////////////
// Operators //
///////////////
interval& interval::operator=(const interval& i)
{
  _assign(i);
  return *this;
}


interval interval::operator+(float v) const
{
  return interval(_lower + v, _upper + v); 
}


interval interval::operator-(float v) const
{
  return interval(_lower - v, _upper - v); 
}


interval interval::operator*(float v) const
{
  return interval(_lower * v, _upper * v); 
}


interval interval::operator/(float v) const
{
  return interval(_lower / v, _upper / v); 
}
    

interval& interval::operator+=(float v)
{
  _lower += v;
  _upper += v;
  return *this;
}

interval& interval::operator-=(float v)
{
  _lower -= v;
  _upper -= v;
  return *this;
}


interval& interval::operator*=(float v)
{
  _lower *= v;
  _upper *= v;

  // ensure that _lower < _upper
  if(_upper < _lower) std::swap(_upper, _lower);

  // Done.
  return *this;
}

interval& interval::operator/=(float v)
{
  _lower /= v;
  _upper /= v;

  // ensure that _lower < _upper
  if(_upper < _lower) std::swap(_upper, _lower);

  // Done.
  return *this;
}


////////////////
// Inspectors //
////////////////
float interval::lower(void) const
{
  return _lower;
}


float interval::upper(void) const
{
  return _upper;
}


bool interval::empty(void) const
{
  return (_upper - _lower < EPSILON);
}



//////////////
// Mutators //
//////////////
void interval::intersect(const interval& i)
{
  _lower = std::max(_lower, i._lower);
  _upper = std::min(_upper, i._upper);
}



/////////////////////
// Private Methods //
/////////////////////
void interval::_assign(const interval& i)
{
  // check for trivial case
  if(&i == this) return;

  // copy
  _lower = i._lower;
  _upper = i._upper;

  // Done.
}


void interval::_swap(interval& i)
{
  std::swap(_lower, i._lower);
  std::swap(_upper, i._upper);
}
