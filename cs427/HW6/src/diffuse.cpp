#include "diffuse.h"

/////////////////
// Constructor //
/////////////////
diffuse::diffuse(void)
{
  // Do nothing.
}


diffuse::diffuse(const diffuse& d)
{
  // Do nothing
}



///////////////
// Operators //
///////////////
diffuse& diffuse::operator=(const diffuse& d)
{
  _assign(d);
  return *this;
}



/////////////
// Methods //
/////////////
float diffuse::evaluate(const vec3d& in, const vec3d& normal, const vec3d& /*out*/) const
{
  return std::max(in.dot(normal), 0.0f );
}



///////////////////////
// Protected Methods //
///////////////////////
void diffuse::_swap(diffuse& d)
{
  // Do nothing.
}


void diffuse::_assign(const diffuse& d)
{
  // Do nothing.
}


void diffuse::_print(std::ostream& s) const
{
  s << "Diffuse BRDF";
}
