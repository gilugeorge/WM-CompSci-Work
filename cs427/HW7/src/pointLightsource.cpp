#include "pointLightsource.h"

//////////////////
// Constructors //
//////////////////
pointLightsource::pointLightsource(const vec3d& position, const color& intensity, const vec3d& attenuation)
{
  _position = position;
  _intensity = intensity;
  _attenuation = attenuation;
}


pointLightsource::pointLightsource(const pointLightsource& ls)
{
  _position = ls._position;
  _intensity = ls._intensity;
  _attenuation = ls._attenuation;
}



///////////////
// Operators //
///////////////
pointLightsource& pointLightsource::operator=(const pointLightsource& ls)
{
  _assign(ls);
  return *this;
}



/////////////
// Methods //
/////////////
vec3d pointLightsource::getDirection(const vec3d& point) const
{
  return (point - _position).normalize();
}


color pointLightsource::getIntensity(const vec3d& point, const vec3d& /*dir*/) const
{
  // compute distance
  float distance = point.distance(_position);

  // compute attenuation scale
  float scale = _attenuation[0] + _attenuation[1] * distance + _attenuation[2] * distance * distance;

  // Done.
  return _intensity / scale;
}



///////////////////////
// Protected Methods //
///////////////////////
void pointLightsource::_swap(pointLightsource& ls)
{
  std::swap(_position, ls._position);
  std::swap(_intensity, ls._intensity);
  std::swap(_attenuation, ls._attenuation);
}


void pointLightsource::_assign(const pointLightsource& ls)
{
  // avoid trivial case
  if(&ls == this) return;

  // copy
  _position = ls._position;
  _intensity = ls._intensity;
  _attenuation = ls._attenuation;

  // Done.
}


void pointLightsource::_print(std::ostream& s) const
{
  s << "Point Lightsource: " << _intensity << " @ " << _position << " (" << _attenuation << ")";
}
