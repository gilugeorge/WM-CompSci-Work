#include <cmath>
#include <cassert>
#include "color.h"

//////////////////
// Constructors //
//////////////////
color::color(float value)
{ 
  r = g = b = value;
}


color::color(float r, float g, float b) 
{
  this->r = r;
  this->g = g;
  this->b = b;
}


color::color(const color& col)
{
  r = col.r;
  g = col.g;
  b = col.b;
}
 

////////////////
// Inspectors //
////////////////
const float& color::operator[](size_t index) const 
{ 
  assert(index < 3);
  return data[index]; 
}


float& color::operator[](size_t index) 
{ 
  assert(index < 3);
  return data[index]; 
}



///////////////
// Operators //
///////////////
color& color::operator=(const color& col) 
{ 
  _assign(col); 
  return *this; 
}


bool color::operator==(const color& col) const 
{ 
  return (r == col.r) && (g == col.g) && (b == col.b); 
}


bool color::operator!=(const color& col) const 
{ 
  return (r != col.r) || (g != col.g) || (b != col.b); 
}
  

color color::operator+(const color& col) const 
{ 
  return color(r + col.r, g + col.g, b + col.b); 
}


color color::operator-(const color& col) const 
{ 
  return color(r - col.r, g - col.g, b - col.b); 
}


color color::operator*(const color& col) const 
{ 
  return color(r * col.r, g * col.g, b * col.b); 
}


color color::operator*(float scale) const 
{ 
  return color(r * scale, g * scale, b * scale); 
}


color color::operator/(const color& col) const 
{ 
  return color(r / col.r, g / col.g, b / col.b); 
}


color color::operator/(float scale) const 
{ 
  return color(r / scale, g / scale, b / scale); 
}


color& color::operator+=(const color& col) 
{ 
  r += col.r; 
  g += col.g; 
  b += col.b; 
  return *this; 
}


color& color::operator-=(const color& col) 
{ 
  r -= col.r; 
  g -= col.g; 
  b -= col.b; 
  return *this; 
}


color& color::operator*=(const color& col) 
{ 
  r *= col.r; 
  g *= col.g;
  b *= col.b;  
  return *this; 
}


color& color::operator*=(float scale) 
{ 
  r *= scale; 
  g *= scale; 
  b *= scale; 
  return *this; 
}


color& color::operator/=(const color& col) 
{ 
  r /= col.r; 
  g /= col.g; 
  b /= col.b; 
  return *this; 
}							


color& color::operator/=(float scale) 
{ 
  r /= scale; 
  g /= scale; 
  b /= scale; 
  return *this; 
}



///////////////
// Modifiers //
///////////////
void color::abs(void)
{
  for(unsigned int i=0; i < 3; i++)
    data[i] = std::abs(data[i]); 
}


void color::clamp(float lowerBound, float upperBound)
{
  for(unsigned int i=0; i < 3; i++)
  {
    if(data[i] < lowerBound) data[i] = lowerBound;
    else if(data[i] > upperBound) data[i] = upperBound;
  }
}


float color::average(void) const
{
  return (r + g + b) / 3.0f;
}


/////////////////////
// Private Methods //
/////////////////////
void color::_assign(const color& col)
{ 
  r = col.r;  
  g = col.g; 
  b = col.b; 
}


void color::_swap(color& col) 
{
  std::swap(r, col.r);
  std::swap(g, col.g);
  std::swap(b, col.b);
}
