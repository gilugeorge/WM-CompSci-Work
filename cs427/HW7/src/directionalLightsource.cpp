#include "directionalLightsource.h"

//////////////////
// Constructors //
//////////////////
directionalLightsource::directionalLightsource(const color& intensity, const vec3d& dir)
{
  _intensity = intensity;
  _direction = dir.normalize();
}


directionalLightsource::directionalLightsource(const directionalLightsource& ls)
{
  _intensity = ls._intensity;
  _direction = ls._direction;
}



///////////////
// Operators //
///////////////
directionalLightsource& directionalLightsource::operator=(const directionalLightsource& ls)
{
  _assign(ls);
  return *this;
}



/////////////
// Methods //
/////////////
vec3d directionalLightsource::getDirection(const vec3d& point) const
{
  return _direction;
}


color directionalLightsource::getIntensity(const vec3d& /*point*/, const vec3d& /*dir*/) const
{
  return _intensity;
}



///////////////////////
// Protected Methods //
///////////////////////
void directionalLightsource::_swap(directionalLightsource& ls)
{
  std::swap(_intensity, ls._intensity);
  std::swap(_direction, ls._direction);
}


void directionalLightsource::_assign(const directionalLightsource& ls)
{
  // avoid trivial case
  if(&ls == this) return;

  // copy
  _intensity = ls._intensity;
  _direction = ls._direction;

  // Done.
}


void directionalLightsource::_print(std::ostream& s) const
{
  s << "Directional Lightsource: " << _intensity << " -> " << _direction;
}
