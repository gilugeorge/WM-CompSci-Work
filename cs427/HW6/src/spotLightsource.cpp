#include "spotLightsource.h"
#include <cmath>

//////////////////
// Constructors //
//////////////////
spotLightsource::spotLightsource(const vec3d& position, const color& intensity, const vec3d& direction, float cutoffDegrees, float sharpness, const vec3d& attenuation)
{
  _position = position;
  _intensity = intensity;
  _direction = direction.normalize();
  _cutoff = cos(cutoffDegrees * M_PI / 180.0f);
  _sharpness = sharpness;
  _attenuation = attenuation;
}


spotLightsource::spotLightsource(const spotLightsource& ls)
{
  _position = ls._position;
  _intensity = ls._intensity;
  _direction = ls._direction;
  _cutoff = ls._cutoff;
  _sharpness = ls._sharpness;
  _attenuation = ls._attenuation;
}



///////////////
// Operators //
///////////////
spotLightsource& spotLightsource::operator=(const spotLightsource& ls)
{
  _assign(ls);
  return *this;
}



/////////////
// Methods //
/////////////
vec3d spotLightsource::getDirection(const vec3d& point) const
{
  return (point - _position).normalize();
}


color spotLightsource::getIntensity(const vec3d& point, const vec3d& dir) const
{
  // HW6: implement this.
  //      returns: the color/intensity which the spot light emits towards 'point' in the direction 'dir'.
  //               The spot light should take attenuation in account which is encoded as a vector, where 
  //               the 1st component is the constant attenuation, the 2nd component is the scale of the 
  //               linear with distance attenuations, and the 3th component is the scale of the distance
  //               squared attenuation.  'cutoff' is the cosine of the angle at which the spot light is 
  //               cut off (i.e., black), and sharpness is the similar as in phong shading a factor that
  //               controlls the fall off.
  //      modifies: nothing.
  return color(0.0f, 0.0f, 0.0f);
}



///////////////////////
// Protected Methods //
///////////////////////
void spotLightsource::_swap(spotLightsource& ls)
{
  std::swap(_position, ls._position);
  std::swap(_intensity, ls._intensity);
  std::swap(_direction, ls._direction);
  std::swap(_cutoff, ls._cutoff);
  std::swap(_sharpness, ls._sharpness);
  std::swap(_attenuation, ls._attenuation);
}


void spotLightsource::_assign(const spotLightsource& ls)
{
  // avoid trivial case
  if(&ls == this) return;

  // copy
  spotLightsource temp(ls);
  _swap(temp);

  // Done.
}


void spotLightsource::_print(std::ostream& s) const
{
  s << "Spot Lightsource: " << _intensity << " @ " << _position << " -> " << _direction << " (" << _cutoff  << ", " << _sharpness << ", " << _attenuation << ")";
}
