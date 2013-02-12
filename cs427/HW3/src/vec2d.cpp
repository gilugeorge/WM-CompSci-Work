#include <cassert>
#include "vec2d.h"

//////////////////
// Constructors //
//////////////////
vec2d::vec2d(float value)
{ 
  x = y = value;
}


vec2d::vec2d(float x, float y) 
{
  this->x = x;
  this->y = y;
}


vec2d::vec2d(const vec2d& v)
{
  x = v.x;
  y = v.y;
}
 

////////////////
// Inspectors //
////////////////
float vec2d::operator[](size_t index) const 
{ 
  assert(index < 2);
  return data[index]; 
}


float& vec2d::operator[](size_t index) 
{ 
  assert(index < 2);
  return data[index]; 
}



///////////////
// Operators //
///////////////
vec2d& vec2d::operator=(const vec2d& v) 
{ 
  _assign(v); 
  return *this; 
}


bool vec2d::operator==(const vec2d& v) const 
{ 
  return (x == v.x) && (y == v.y); 
}


bool vec2d::operator!=(const vec2d& v) const 
{ 
  return (x != v.x) || (y != v.y); 
}
  

vec2d vec2d::operator+(const vec2d& v) const 
{ 
  return vec2d(x + v.x, y + v.y); 
}


vec2d vec2d::operator-(const vec2d& v) const 
{ 
  return vec2d(x - v.x, y - v.y); 
}


vec2d vec2d::operator*(const vec2d& v) const 
{ 
  return vec2d(x * v.x, y * v.y); 
}


vec2d vec2d::operator*(float scale) const 
{ 
  return vec2d(x * scale, y * scale); 
}


vec2d vec2d::operator/(const vec2d& v) const 
{ 
  return vec2d(x / v.x, y / v.y); 
}


vec2d vec2d::operator/(float scale) const 
{ 
  return vec2d(x / scale, y / scale); 
}


vec2d& vec2d::operator+=(const vec2d& v) 
{ 
  x += v.x; 
  y += v.y; 
  return *this; 
}


vec2d& vec2d::operator-=(const vec2d& v) 
{ 
  x -= v.x; 
  y -= v.y; 
  return *this; 
}


vec2d& vec2d::operator*=(const vec2d& v) 
{ 
  x *= v.x; 
  y *= v.y; 
  return *this; 
}


vec2d& vec2d::operator*=(float scale) 
{ 
  x *= scale; 
  y *= scale; 
  return *this; 
}


vec2d& vec2d::operator/=(const vec2d& v) 
{ 
  x /= v.x; 
  y /= v.y; 
  return *this; 
}							


vec2d& vec2d::operator/=(float scale) 
{ 
  x /= scale; 
  y /= scale; 
  return *this; 
}



///////////////
// Modifiers //
///////////////
float vec2d::dot(const vec2d& v) const 
{ 
  return x*v.x + y*v.y; 
}


float vec2d::squared_length(void) const 
{ 
  return dot(*this); 
}


float vec2d::length(void) const 
{ 
  return sqrt(squared_length()); 
}


float vec2d::squared_distance(const vec2d& v) const 
{
  return (*this - v).squared_length(); 
}


float vec2d::distance(const vec2d& v) const 
{ 
  return sqrt(squared_distance(v)); 
}


vec2d vec2d::normalize(void) const
{ 
  return *this / length(); 
}



/////////////////////
// Private Methods //
/////////////////////
void vec2d::_assign(const vec2d& v)
{ 
  x = v.x;  
  y = v.y; 
}


void vec2d::_swap(vec2d& v) 
{
  std::swap(x, v.x);
  std::swap(y, v.y);
}
