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
  // HW3: Implement me
  //      Input: in = light source direction
  //             normal = surface normal
  //             out = view direction
  //      Modifies: nothing
  //      Returns: evaluation of the phong brdf.

  return pow(out.dot((2*(normal.dot(in))*normal) - in), _sharpness);
  return 0.0f;
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
