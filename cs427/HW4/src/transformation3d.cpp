#include "transformation3d.h"


//////////////////
// Constructors //
//////////////////
transformation3d::transformation3d(void)
{
  _translation = vec3d();
  _transformation = mat3d(1.0f);
  _inverseTransformation = mat3d(1.0f);
}


transformation3d::transformation3d(const vec3d& translation, const mat3d& transformation, const mat3d& inverseTransformation)
{
  _translation = translation;
  _transformation = transformation;
  _inverseTransformation = inverseTransformation;
}


transformation3d::transformation3d(const transformation3d& t)
{
  _translation = t._translation;
  _transformation = t._transformation;
  _inverseTransformation = t._inverseTransformation;
}


//////////////
// Operator //
//////////////
transformation3d& transformation3d::operator=(const transformation3d& t)
{
  _assign(t);
  return *this;
}


//////////////
// Mutators //
//////////////
void transformation3d::transform(const transformation3d& t) 
{
  _translation = t.transformPoint(_translation);
  _transformation = t._transformation * _transformation;
  _inverseTransformation = _inverseTransformation * t._inverseTransformation;
}


void transformation3d::inverseTransform(const transformation3d& t)
{
  _translation = t.inverseTransformPoint(_translation);
  _transformation = t._inverseTransformation * _transformation;
  _inverseTransformation = _inverseTransformation * t._transformation;
}


/////////////
// Methods //
/////////////
vec3d transformation3d::transformPoint(const vec3d& p) const
{
  // first transform, then translate
  vec3d transformed = _transformation * p;
  transformed += _translation;
  
  // Done.
  return transformed;
}


vec3d transformation3d::transformDirection(const vec3d& d) const
{
  // Only apply transformation
  vec3d transformed = _transformation * d;

  // Done.
  return transformed.normalize();
}


vec3d transformation3d::transformNormal(const vec3d& n) const
{
  // Don't apply translation.
  // n' = (_transformation^T)^-1 * n
  // n'^T = n^T * _transformation^-1
  // n'^T = n^T * _inverseTransformation
  vec3d transformed = n * _inverseTransformation;
  
  // Done.
  return transformed.normalize();
}


vec3d transformation3d::inverseTransformPoint(const vec3d& p) const
{
  // for undo transltation, then invert the transformation
  vec3d transformed = p - _translation;
  transformed = _inverseTransformation * transformed;

  // Done.
  return transformed;
}


vec3d transformation3d::inverseTransformDirection(const vec3d& d) const
{
  // Only invert the transformation
  vec3d transformed = _inverseTransformation * d;

  // Done.
  return transformed.normalize();
}


vec3d transformation3d::inverseTransformNormal(const vec3d& n) const
{
  // Don't apply translation. Undo (transformation^T)^-1
  vec3d transformed = n * _transformation;

  // Done.
  return transformed.normalize();
}


///////////////////////
// Protected Methods //
///////////////////////
void transformation3d::_swap(transformation3d& t)
{
  std::swap(_translation, t._translation);
  std::swap(_transformation, t._transformation);
  std::swap(_inverseTransformation, t._inverseTransformation);
}


void transformation3d::_assign(const transformation3d& t)
{
  // avoid copying when self-assigning
  if(&t == this) return;

  // Copy
  _translation = t._translation;
  _transformation = t._transformation;
  _inverseTransformation = t._inverseTransformation;

  // Done.
}


