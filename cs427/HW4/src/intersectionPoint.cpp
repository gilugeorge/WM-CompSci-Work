#include "intersectionPoint.h"

//////////////////
// Constructors //
//////////////////
intersectionPoint::intersectionPoint(void)
{
  _hit = false;
}


intersectionPoint::intersectionPoint(const ray& r, const vec3d& barycentricCoord, float rayParameter, const triangle& t, const material& mat)
{
  _hit = true;
  _r = r;
  _rayParameter = rayParameter;
  _point = r(rayParameter);
  _normal = t.interpolateNormal(barycentricCoord);
  _textureCoord = t.interpolateTextCoord(barycentricCoord);
  _material = mat;
}


intersectionPoint::intersectionPoint(const intersectionPoint& ip)
{
  _hit = ip._hit;

  // copy remainder of the data if hit.
  if(_hit)
  {
    _r = ip._r;
    _rayParameter = ip._rayParameter;
    _point = ip._point;
    _normal = ip._normal;
    _textureCoord = ip._textureCoord;
    _material = ip._material;  
  }
}


///////////////
// Operators //
///////////////
intersectionPoint& intersectionPoint::operator=(const intersectionPoint& ip)
{
  _assign(ip);
  return *this;
}


bool intersectionPoint::operator<(const intersectionPoint& ip) const
{
  // handle case where either one of the intersectionPoints is not a hit
  // => assume no-hit equals a hit at infinity
  if(!_hit) return false;
  if(!ip._hit) return true;

  // decide based on rayParameter
  return _rayParameter < ip._rayParameter;
}


bool intersectionPoint::operator<(float rayParameter) const
{
  // handle the case where this intersectionPoint is not a hit
  // => assume no-hit equals a hit at infinity
  if(!_hit) return false;

  // otherwise decide based on rayParameter
  return _rayParameter < rayParameter;
}


bool intersectionPoint::operator<(const vec3d& point) const
{
  // handle the case where this intersectionPoint is not a hit
  // => assume no-hit equals a hit at infinity
  if(!_hit) return false;

  // otherwise decide based on rayParameter
  return _rayParameter < _r.getParameter(point);
}

bool intersectionPoint::operator>(const intersectionPoint& ip) const
{
  // handle case where either one of the intersectionPoints is not a hit
  // => assume no-hit equals a hit at infinity
  if(!_hit) return true;
  if(!ip._hit) return false;

  // decide based on rayParameter
  return _rayParameter > ip._rayParameter;
}


bool intersectionPoint::operator>(float rayParameter) const
{
  // handle the case where this intersectionPoint is not a hit
  // => assume no-hit equals a hit at infinity
  if(!_hit) return true;

  // otherwise decide based on rayParameter
  return _rayParameter > rayParameter;
}


bool intersectionPoint::operator>(const vec3d& point) const
{
  // handle the case where this intersectionPoint is not a hit
  // => assume no-hit equals a hit at infinity
  if(!_hit) return true;

  // otherwise decide based on rayParameter
  return _rayParameter > _r.getParameter(point);
}



////////////////
// Inspectors //
////////////////
const ray& intersectionPoint::getRay(void) const
{
  return _r;
}


float intersectionPoint::rayParameter(void) const
{
  return _rayParameter;
}


const vec3d& intersectionPoint::point(void) const
{
  return _point;
}


const vec3d& intersectionPoint::normal(void) const
{
  return _normal;
}


const vec2d& intersectionPoint::textureCoordinate(void) const
{
  return _textureCoord;
}



/////////////
// Methods //
/////////////
bool intersectionPoint::isHit(void) const
{
  return _hit;
}


void intersectionPoint::transform(const transformation3d& t)
{
  // sanity check
  if(!_hit) return;

  /// transform
  _r.transform(t);
  _point = t.transformPoint(_point);
  _normal = t.transformNormal(_normal);

  // recompute the ray parameter (to account for potential scaling)
  _rayParameter = _r.getParameter(_point);
}


void intersectionPoint::inverseTransform(const transformation3d& t)
{
  // sanity check
  if(!_hit) return;

  // inverse transform
  _r.inverseTransform(t);
  _point = t.inverseTransformPoint(_point);
  _normal = t.inverseTransformNormal(_normal);

  // recompute the ray parameter (to account for potential scaling)
  _rayParameter = _r.getParameter(_point);
}


color intersectionPoint::evaluate(const lightsource_base& ls) const
{
  // sanity check
  if(!_hit) return color(0.0f, 0.0f, 0.0f);

  // NOTE: this assume the light source is visible!
  // get light source direction & intensity
  vec3d in = ls.getDirection(_point);
  color intensity = ls.getIntensity(_point, in);

  // get shading (note: flip in direction to point towards the camera and towards the light source)
  color shading = _material.evaluate(-1.0f * in, _normal, -1.0f * _r.direction(), _textureCoord);

  // Done.
  return intensity * shading;
}


color intersectionPoint::evaluate(const vec3d& dir) const
{
  // sanity check
  if(!_hit) return color(0.0f, 0.0f, 0.0f);

  // get shading
  color shading = _material.evaluate(dir, _normal, -1.0f * _r.direction(), _textureCoord);

  // Done.
  return shading;
}

/////////////////////
// Private Methods //
/////////////////////
void intersectionPoint::_swap(intersectionPoint& ip)
{
  std::swap(_r, ip._r);
  std::swap(_hit, ip._hit);
  std::swap(_rayParameter, ip._rayParameter);
  std::swap(_point, ip._point);
  std::swap(_normal, ip._normal);
  std::swap(_textureCoord, ip._textureCoord);
  std::swap(_material, ip._material);
}


void intersectionPoint::_assign(const intersectionPoint& ip)
{
  // check for trivial case: self-assignment
  if(&ip == this) return;

  // copy
  _hit = ip._hit;

  // copy remainder of the data if hit.
  if(_hit)
  {
    _r = ip._r;
    _rayParameter = ip._rayParameter;
    _point = ip._point;
    _normal = ip._normal;
    _textureCoord = ip._textureCoord;
    _material = ip._material;  
  }

  // Done.
}
