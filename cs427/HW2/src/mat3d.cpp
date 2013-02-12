#include <cassert>
#include <algorithm>

#include "mat3d.h"

/////////////////
// Constructor //
/////////////////
mat3d::mat3d(void)
{
  clear(0.0f);
}


mat3d::mat3d(mat3d::value_type diag)
{
  clear(0.0f);
  setDiagonal(diag);
}


mat3d::mat3d(const vec3d& X, const vec3d& Y, const vec3d& Z)
{
  setColumn(X,0);
  setColumn(Y,1);
  setColumn(Z,2);
}


mat3d::mat3d(const mat3d& m)
{
  std::copy(m.begin(), m.end(), begin());
}


////////////////
// Inspectors //
////////////////
mat3d::iterator mat3d::begin(void)
{
  return &(_data[0]);
}


mat3d::const_iterator mat3d::begin(void) const
{
  return &(_data[0]);
}


mat3d::iterator mat3d::end(void)
{
  return &(_data[size()]);
}


mat3d::const_iterator mat3d::end(void) const
{
  return &(_data[size()]);
}


mat3d::reference mat3d::operator()(mat3d::size_type row, mat3d::size_type col)
{
  assert(row < height() && col < width());
  return _at(row, col);
}


mat3d::const_reference mat3d::operator()(mat3d::size_type row, mat3d::size_type col) const
{
  assert(row < height() && col < width());
  return _at(row, col);
}


vec3d mat3d::row(mat3d::size_type row) const
{
  assert(row < height());
  return vec3d( _at(row, 0), _at(row, 1), _at(row, 2) );
}


vec3d mat3d::column(mat3d::size_type col) const
{
  assert(col < width());
  return vec3d( _at(0, col), _at(1, col), _at(2, col) );
}



//////////////
// Mutators //
//////////////
void mat3d::clear(mat3d::value_type value)
{
  std::fill(begin(), end(), value);
}


void mat3d::identity(mat3d::value_type diag)
{
  clear(0.0f);
  setDiagonal(1.0f);
}


void mat3d::set(const vec3d& X, const vec3d& Y, const vec3d& Z)
{
  setColumn(X, 0);
  setColumn(Y, 1);
  setColumn(Z, 2);
}


void mat3d::setDiagonal(mat3d::value_type d)
{
  for(size_type i=0; i < width(); i++)
    _at(i,i) = d;
}


void mat3d::setDiagonal(const vec3d& d)
{
  for(size_type i=0; i < width(); i++)
    _at(i,i) = d[i];
}


void mat3d::setRow(const vec3d& v, mat3d::size_type row)
{
  assert(row < height());
  for(size_type i=0; i < height(); i++)
    _at(row, i) = v[i];
}


void mat3d::setColumn(const vec3d& v, mat3d::size_type col)
{
  assert(col < width());
  for(size_type i=0; i < width(); i++)
    _at(i, col) = v[i];
}


mat3d mat3d::transpose(void) const
{
  mat3d result;
  for(size_type i=0; i < height(); i++)
    for(size_type j=0; j < width(); j++)
      result(i,j) = _at(j,i);
  return result;
}



///////////////
// Operators //
///////////////
mat3d mat3d::operator=(const mat3d& m)
{
  _assign(m);
  return *this;
}


mat3d mat3d::operator+(const mat3d& m) const
{
  mat3d result;
  std::transform(begin(), end(), m.begin(), result.begin(), std::plus<float>());
  return result;
}


mat3d mat3d::operator-(const mat3d& m) const
{
  mat3d result;
  std::transform(begin(), end(), m.begin(), result.begin(), std::minus<float>());
  return result;
}


mat3d mat3d::operator*(const mat3d& m) const
{
  mat3d result;
  for(size_type i=0; i < result.height(); i++)
    for(size_type j=0; j < result.width(); j++)
      for(size_type k=0; k < width(); k++)
	result(i,j) += _at(i,k) * m(k, j);
  return result;
}


vec3d mat3d::operator*(const vec3d& v) const
{
  vec3d result;
  for(size_type i=0; i < height(); i++)
    for(size_type j=0; j < width(); j++)
      result[i] += v[j] * _at(i,j);
  return result;
}


mat3d mat3d::operator*(mat3d::value_type scale) const
{
  mat3d result;
  std::transform(begin(), end(), result.begin(), std::bind2nd( std::multiplies<float>(), scale ));
  return result;
}


mat3d mat3d::operator/(mat3d::value_type scale) const
{
  mat3d result;
  std::transform(begin(), end(), result.begin(), std::bind2nd( std::divides<float>(), scale ));
  return result;
}


mat3d& mat3d::operator+=(const mat3d& m)
{
  std::transform(begin(), end(), m.begin(), begin(), std::plus<float>());
  return *this;
}


mat3d& mat3d::operator-=(const mat3d& m)
{
  std::transform(begin(), end(), m.begin(), begin(), std::minus<float>());
  return *this;
}


mat3d& mat3d::operator*=(const mat3d& m)
{
  *this = *this * m;
  return *this;
}


mat3d& mat3d::operator*=(mat3d::value_type scale)
{
  std::transform(begin(), end(), begin(), std::bind2nd( std::multiplies<float>(), scale ));
  return *this;
}


mat3d& mat3d::operator/=(mat3d::value_type scale)
{
  std::transform(begin(), end(), begin(), std::bind2nd( std::divides<float>(), scale ));
  return *this;
}
  

/////////////////////
// Private Methods //
/////////////////////
void mat3d::_swap(mat3d& m)
{
  std::swap_ranges(begin(), end(), m.begin());
}


void mat3d::_assign(const mat3d& m)
{
  std::copy(m.begin(), m.end(), begin());
}


mat3d::reference mat3d::_at(mat3d::size_type row, mat3d::size_type col)
{
  // column major storage
  return _data[ row * width() + col ];
}


mat3d::const_reference mat3d::_at(mat3d::size_type row, mat3d::size_type col) const
{
  // column major storage
  return _data[ row * width() + col ];
}


void mat3d::_transpose(void)
{
  for(size_type i=0; i < height(); i++)
    for(size_type j=i+1; j < width(); j++)
      std::swap( _at(i,j), _at(j,i) );
}


vec3d mat3d::_premultiply(const vec3d& v) const
{
  // result = v * *this
  vec3d result;
  for(size_type i=0; i < height(); i++)
    for(size_type j=0; j < width(); j++)
      result[j] += v[i] * _at(i,j);
  return result;
}
