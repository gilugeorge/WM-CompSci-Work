#include "ray.h"

//////////////////
// Constructors //
//////////////////
ray::ray(const vec3d& origin, const vec3d& direction)
{
  _origin = origin;
  _direction = direction.normalize();
}


ray::ray(const ray& r)
{
  _origin = r._origin;
  _direction = r._direction;
}



////////////////
// Inspectors //
////////////////
const vec3d& ray::origin(void) const
{
  return _origin;
}


const vec3d& ray::direction(void) const
{
  return _direction;
}



//////////////
// Mutators //
//////////////
ray& ray::operator=(const ray& r)
{
  _assign(r);
  return *this;
}


void ray::setOrigin(const vec3d& origin)
{
  _origin = origin;
}


void ray::setDirection(const vec3d& direction)
{
  _direction = direction.normalize();
}


void ray::transform(const transformation3d& t)
{
  _origin = t.transformPoint(_origin);
  _direction = t.transformDirection(_direction);
}


void ray::inverseTransform(const transformation3d& t)
{
  _origin = t.inverseTransformPoint(_origin);
  _direction = t.inverseTransformDirection(_direction);
}


/////////////
// Methods //
/////////////
vec3d ray::evaluate(float t) const
{
  return _origin + _direction*t;
}


vec3d ray::operator()(float t) const
{
  return evaluate(t);
}


float ray::distanceToRay(const vec3d& point) const
{
  vec3d closestPoint = closestPointOnRay(point);
  return point.distance(closestPoint);
}


vec3d ray::closestPointOnRay(const vec3d& point) const
{
  float t = getParameter(point);
  return evaluate(t);
}
  

float ray::getParameter(const vec3d& point) const
{
  return _direction.dot( point - _origin );
}



/////////////////////
// Private Methods //
/////////////////////
void ray::_swap(ray& r)
{
  std::swap(_origin, r._origin);
  std::swap(_direction, r._direction);
}


void ray::_assign(const ray& r)
{
  _origin = r._origin;
  _direction = r._direction;
}

