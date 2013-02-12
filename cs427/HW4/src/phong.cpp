#include "phong.h"

/////////////////
// Constructor //
/////////////////
phong::phong(float sharpness)
{
  _sharpness = sharpness;
}


phong::phong(const phong& d)
{
  _sharpness = d._sharpness;
}



///////////////
// Operators //
///////////////
phong& phong::operator=(const phong& d)
{
  _assign(d);
  return *this;
}



/////////////
// Methods //
/////////////
float phong::evaluate(const vec3d& in, const vec3d& normal, const vec3d& out) const
{
  vec3d reflected = 2.0f * (normal.dot(in)) * normal - in;
  return std::pow(std::max( reflected.dot(out), 0.0f), _sharpness);
}



///////////////////////
// Protected Methods //
///////////////////////
void phong::_swap(phong& d)
{
  std::swap(_sharpness, d._sharpness);
}


void phong::_assign(const phong& d)
{
  _sharpness = d._sharpness;
}


void phong::_print(std::ostream& s) const
{
  s << "Phong BRDF: " << _sharpness;
}
