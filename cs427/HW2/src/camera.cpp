#include "camera.h"

#include <cmath>

/////////////////
// Constructor //
/////////////////
camera::camera(void)
{
  _origin = vec3d();
  _view = vec3d(0.0f, 0.0f, -1.0f);
  _up = vec3d(0.0f, 1.0f, 0.0f);
  _fov = (60.0f / 360.0f) * 2.0f * M_PI;
  _width = _height = 256;
}


camera::camera(const vec3d& eye, const vec3d& viewDirection, const vec3d& up, float fov, size_t xres, size_t yres)
{
  _origin = eye;
  _view = viewDirection.normalize();
  _up = up.normalize();
  _fov = fov;
  _width = xres;
  _height = yres;
}


camera::camera(const camera& cam)
{
  _origin = cam._origin;
  _view = cam._view;
  _up = cam._up;
  _fov = cam._fov;
  _width = cam._width;
  _height = cam._height;
}


///////////////
// Operators //
///////////////
camera& camera::operator=(const camera& cam)
{
  _assign(cam);
  return *this;
}


ray camera::operator()(float x, float y) const
{
  return generateViewRay(x,y);
}


/////////////
// Methods //
/////////////
ray camera::generateViewRay(float x, float y) const
{
  // Z = view, Y = up, compute X (right)
  vec3d right = _view.cross(_up);
  
  // aspect ratio (fov is in the U (horizontal) direction)
  float aspect = (float)(_height) / (float)(_width);
  float tanFov = tan(_fov);
  
  // compute the center position, (un-normalized) U and V axis of the viewplane at distance d=1
  vec3d center = _origin + _view;
  vec3d U = 2.0f * tanFov * right;
  vec3d V = -2.0f * tanFov * aspect * _up;    // Note: minus sign because y-coordinate runs from top to bottom (opposite direction of _up vector)

  // Compute point on viewplane
  vec3d p = center + ((float)(x) / (float)(_width) - 0.5f) * U + ((float)(y) / (float)(_height) - 0.5f) * V;

  // generate ray
  return ray(_origin, p - _origin);
}


////////////////
// Inspectors //
///////////////
const vec3d& camera::origin(void) const
{
  return _origin;
}


const vec3d& camera::view(void) const
{
  return _view;
}


const vec3d& camera::up(void) const
{
  return _up;
}


float camera::fov(void) const
{
  return _fov;
}


size_t camera::width(void) const
{
  return _width;
}


size_t camera::height(void) const
{
  return _height;
}


//////////////
// Mutators //
//////////////
void camera::transform(const transformation3d& t)
{
  t.transformPoint(_origin);
  t.transformDirection(_view);
  t.transformDirection(_up);
}


void camera::inverseTransform(const transformation3d& t)
{
  t.inverseTransformPoint(_origin);
  t.inverseTransformDirection(_view);
  t.inverseTransformDirection(_up);
}


/////////////////////
// Private Methods //
/////////////////////
void camera::_swap(camera& cam)
{
  std::swap(_origin, cam._origin);
  std::swap(_view, cam._view);
  std::swap(_up, cam._up);
  std::swap(_fov, cam._fov);
  std::swap(_width, cam._width);
  std::swap(_height, cam._height);
}


void camera::_assign(const camera& cam)
{
  // avoid trivial case: self-assignment
  if(&cam == this) return;

  // copy data
  _origin = cam._origin;
  _view = cam._view;
  _up = cam._up;
  _fov = cam._fov;
  _width = cam._width;
  _height = cam._height;

  // Done.
}
