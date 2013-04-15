#include "constantAlbedo.h"

/////////////////
// Constructor //
/////////////////
constantAlbedo::constantAlbedo(const color& col)
{
  _albedo = col;
}


constantAlbedo::constantAlbedo(const constantAlbedo& ca)
{
  _albedo = ca._albedo;
}



//////////////
// Operator //
//////////////
constantAlbedo& constantAlbedo::operator=(const constantAlbedo& ca)
{
  _assign(ca);
  return *this;
}



/////////////
// Methods //
/////////////
color constantAlbedo::evaluate(const vec2d& /*textureCoord*/) const
{
  return _albedo;
}



/////////////////////
// Private Methods //
/////////////////////
void constantAlbedo::_swap(constantAlbedo& ca)
{
  std::swap(_albedo, ca._albedo);
}


void constantAlbedo::_assign(const constantAlbedo& ca)
{
  _albedo = ca._albedo;
}


void constantAlbedo::_print(std::ostream& s) const
{
  s << "Constant Albedo: " << _albedo;
}

