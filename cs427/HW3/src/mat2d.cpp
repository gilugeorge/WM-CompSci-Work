#include <cassert>
#include <algorithm>

#include "mat2d.h"

/////////////////
// Constructor //
/////////////////
mat2d::mat2d(void)
{
  clear(0.0f);
}


mat2d::mat2d(mat2d::value_type diag)
{
  _data[0] = _data[3] = diag;
  _data[1] = _data[2] = 0.0f;
}


mat2d::mat2d(const vec2d& X, const vec2d& Y)
{
  setColumn(X,0);
  setColumn(Y,1);
}


mat2d::mat2d(const mat2d& m)
{
  std::copy(m.begin(), m.end(), begin());
}


////////////////
// Inspectors //
////////////////
mat2d::iterator mat2d::begin(void)
{
  return &(_data[0]);
}


mat2d::const_iterator mat2d::begin(void) const
{
  return &(_data[0]);
}


mat2d::iterator mat2d::end(void)
{
  return &(_data[size()]);
}


mat2d::const_iterator mat2d::end(void) const
{
  return &(_data[size()]);
}


mat2d::reference mat2d::operator()(mat2d::size_type row, mat2d::size_type col)
{
  assert(row < height() && col < width());
  return _at(row, col);
}


mat2d::const_reference mat2d::operator()(mat2d::size_type row, mat2d::size_type col) const
{
  assert(row < height() && col < width());
  return _at(row, col);
}


vec2d mat2d::row(mat2d::size_type row) const
{
  assert(row < height());
  return vec2d( _at(row, 0), _at(row, 1) );
}


vec2d mat2d::column(mat2d::size_type col) const
{
  assert(col < width());
  return vec2d( _at(0, col), _at(1, col) );
}



//////////////
// Mutators //
//////////////
void mat2d::clear(mat2d::value_type value)
{
  std::fill(begin(), end(), value);
}


void mat2d::identity(mat2d::value_type diag)
{
  _data[0] = _data[3] = diag;
  _data[1] = _data[2] = 0.0f;
}


void mat2d::set(const vec2d& X, const vec2d& Y)
{
  setColumn(X, 0);
  setColumn(Y, 1);
}


void mat2d::setDiagonal(mat2d::value_type d)
{
  _at(0,0) = _at(1,1) = d;
}


void mat2d::setDiagonal(const vec2d& d)
{
  _at(0,0) = d[0];
  _at(1,1) = d[1];
}


void mat2d::setRow(const vec2d& v, mat2d::size_type row)
{
  assert(row < height());
  _at(row, 0) = v.x;
  _at(row, 1) = v.y;
}


void mat2d::setColumn(const vec2d& v, mat2d::size_type col)
{
  assert(col < width());
  _at(0, col) = v.x;
  _at(1, col) = v.y;
}


mat2d mat2d::transpose(void) const
{
  mat2d result;
  result(0,0) = _at(0,0);
  result(1,0) = _at(0,1);
  result(0,1) = _at(1,0);
  result(1,1) = _at(1,1);
  return result;
}



///////////////
// Operators //
///////////////
mat2d mat2d::operator=(const mat2d& m)
{
  _assign(m);
  return *this;
}


mat2d mat2d::operator+(const mat2d& m) const
{
  mat2d result;
  std::transform(begin(), end(), m.begin(), result.begin(), std::plus<float>());
  return result;
}


mat2d mat2d::operator-(const mat2d& m) const
{
  mat2d result;
  std::transform(begin(), end(), m.begin(), result.begin(), std::minus<float>());
  return result;
}


mat2d mat2d::operator*(const mat2d& m) const
{
  mat2d result;
  for(size_type i=0; i < result.height(); i++)
    for(size_type j=0; j < result.width(); j++)
      for(size_type k=0; k < width(); k++)
	result(i,j) += _at(i,k) * m(k, j);
  return result;
}


vec2d mat2d::operator*(const vec2d& v) const
{
  return vec2d( v.x * _at(0,0) + v.y * _at(0,1),
		v.x * _at(1,0) + v.y * _at(1,1) );
}


mat2d mat2d::operator*(mat2d::value_type scale) const
{
  mat2d result;
  std::transform(begin(), end(), result.begin(), std::bind2nd( std::multiplies<float>(), scale ));
  return result;
}


mat2d mat2d::operator/(mat2d::value_type scale) const
{
  mat2d result;
  std::transform(begin(), end(), result.begin(), std::bind2nd( std::divides<float>(), scale ));
  return result;
}


mat2d& mat2d::operator+=(const mat2d& m)
{
  std::transform(begin(), end(), m.begin(), begin(), std::plus<float>());
  return *this;
}


mat2d& mat2d::operator-=(const mat2d& m)
{
  std::transform(begin(), end(), m.begin(), begin(), std::minus<float>());
  return *this;
}


mat2d& mat2d::operator*=(const mat2d& m)
{
  *this = *this * m;
  return *this;
}


mat2d& mat2d::operator*=(mat2d::value_type scale)
{
  std::transform(begin(), end(), begin(), std::bind2nd( std::multiplies<float>(), scale ));
  return *this;
}


mat2d& mat2d::operator/=(mat2d::value_type scale)
{
  std::transform(begin(), end(), begin(), std::bind2nd( std::divides<float>(), scale ));
  return *this;
}
  

/////////////////////
// Private Methods //
/////////////////////
void mat2d::_swap(mat2d& m)
{
  std::swap_ranges(begin(), end(), m.begin());
}


void mat2d::_assign(const mat2d& m)
{
  std::copy(m.begin(), m.end(), begin());
}


mat2d::reference mat2d::_at(mat2d::size_type row, mat2d::size_type col)
{
  // column major storage
  return _data[ row * width() + col ];
}


mat2d::const_reference mat2d::_at(mat2d::size_type row, mat2d::size_type col) const
{
  // column major storage
  return _data[ row * width() + col ];
}


vec2d mat2d::_premultiply(const vec2d& v) const
{
  // result = v * *this
  return vec2d( v.x * _at(0,0) + v.y * _at(1,0),
		v.x * _at(0,1) + v.y * _at(1,1) );
}
