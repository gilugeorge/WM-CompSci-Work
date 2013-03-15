#include <cassert>
#include <algorithm>

#include "triangle.h"
#include "constants.h"


/////////////////
// Constructor //
/////////////////
triangle::triangle(const vec3d& v1, const vec3d& v2, const vec3d& v3)
{
  // copy vertices
  setVertices(v1, v2, v3);

  // set normals
  vec3d n = normal();
  setNormals(n, n, n);

  // set texture coordinates
  setTextureCoordinates(vec2d(0.0f, 0.0f), vec2d(0.0f, 0.0f), vec2d(0.0f, 0.0f));
}


triangle::triangle(const vec3d& v1, const vec3d& v2, const vec3d& v3, const vec3d& n1, const vec3d& n2, const vec3d& n3, const vec2d& t1, const vec2d& t2, const vec2d& t3)
{
  setVertices(v1, v2, v3);
  setNormals(n1, n2, n3);
  setTextureCoordinates(t1, t2, t3);
}


triangle::triangle(const triangle& t)
{
  for(size_t i = 0; i < 3; i++)
  {
    _vertex[i] = t._vertex[i];
    _normal[i] = t._normal[i];
    _texCoord[i] = t._texCoord[i];
  }
}



////////////////
// Inspectors //
////////////////
const vec3d& triangle::vertex(size_t index) const
{
  assert(index < 3);
  return _vertex[index];
}


vec3d triangle::normal(void) const
{
  vec3d edge1 = _vertex[1] - _vertex[0];
  vec3d edge2 = _vertex[2] - _vertex[0];
  vec3d normal = edge1.cross(edge2);
  return normal.normalize();
}



//////////////
// Mutators //
//////////////v
void triangle::transform(const transformation3d& t)
{
  // apply a transformation to each vertex & normal
  for(size_t i=0; i < 3; i++)
  {
    _vertex[i] = t.transformPoint(_vertex[i]);
    _normal[i] = t.transformNormal(_normal[i]);
  }
}


void triangle::inverseTransform(const transformation3d& t)
{
  // apply an inverse transformation to each vertex & normal
  for(size_t i=0; i < 3; i++)
  {
    _vertex[i] = t.inverseTransformPoint(_vertex[i]);
    _normal[i] = t.inverseTransformNormal(_normal[i]);
  }
}


void triangle::setVertices(const vec3d& v1, const vec3d& v2, const vec3d& v3)
{
  _vertex[0] = v1;
  _vertex[1] = v2;
  _vertex[2] = v3;
}


void triangle::setNormals(const vec3d& n1, const vec3d& n2, const vec3d& n3)
{
  _normal[0] = n1;
  _normal[1] = n2;
  _normal[2] = n3;
}


void triangle::setTextureCoordinates(const vec2d& t1, const vec2d& t2, const vec2d& t3)
{
  _texCoord[0] = t1;
  _texCoord[1] = t2;
  _texCoord[2] = t3;
}



///////////////
// Operators //
///////////////
triangle triangle::operator=(const triangle& t)
{
  _assign(t);
  return *this;
}



/////////////
// Methods //
/////////////
bool triangle::intersect(const ray& r, vec3d& barycentricCoord, float& t) const
{
  // intersect plane in which the triangle resides
  bool hit = _planeIntersection(r, t);

  // check if hit
  if(!hit) return false;

  // compute barycentric coordinates
  barycentricCoord = _barycentricCoord(r, t);

  // check if inside triangle
  if(barycentricCoord[0] < -EPSILON ||
     barycentricCoord[1] < -EPSILON ||
     barycentricCoord[2] < -EPSILON) return false;
  
  // Done.
  return true;
}


vec3d triangle::interpolateVertex(const vec3d& barycentricCoord) const
{
  vec3d result;
  for(size_t i=0; i < 3; i++)
    result += barycentricCoord[i] * _vertex[i];
  return result;
}


vec3d triangle::interpolateNormal(const vec3d& barycentricCoord) const
{
  vec3d result;
  for(size_t i=0; i < 3; i++)
    result += barycentricCoord[i] * _normal[i];
  return result.normalize();
}


vec2d triangle::interpolateTextCoord(const vec3d& barycentricCoord) const
{
  vec2d result;
  for(size_t i=0; i < 3; i++)
    result += barycentricCoord[i] * _texCoord[i];
  return result;
}



/////////////////////
// Private Methods //
/////////////////////
void triangle::_swap(triangle& t)
{
  std::swap_ranges(&_vertex[0], &_vertex[3], &t._vertex[0]);
  std::swap_ranges(&_normal[0], &_normal[3], &t._normal[0]);
  std::swap_ranges(&_texCoord[0], &_texCoord[3], &t._texCoord[0]);
}


void triangle::_assign(const triangle& t)
{
  // sanity check
  if(this == &t) return;

  // copy
  std::copy(&t._vertex[0], &t._vertex[3], &_vertex[0]);
  std::copy(&t._normal[0], &t._normal[3], &_normal[0]);
  std::copy(&t._texCoord[0], &t._texCoord[3], &_texCoord[0]);
  
  // Done.
}

bool triangle::_planeIntersection(const ray& r, float& t) const
{
  // get plane normal
  vec3d n = normal();

  // check if ray parallel to plane
  float VN = n.dot( r.direction() );
  if(fabs(VN) < EPSILON) return false;

  // compute t
  t = (_vertex[0] - r.origin()).dot(n) / VN;

  // check if behind origin:
  if(t < EPSILON) return false;

  // Done.
  return true;
}


vec3d triangle::_barycentricCoord(const ray& r, float t) const
{
  vec3d q = r(t);
  vec3d n = normal();
  vec3d e1 = _vertex[1] - _vertex[0];
  vec3d e2 = _vertex[2] - _vertex[0];
  vec3d p1 = _vertex[0] - q;
  vec3d p2 = _vertex[1] - q;
  vec3d p3 = _vertex[2] - q;

  // area triangle (x2)
  float area = (e1.cross(e2)).dot(n);
  
  // area v2-q-v3
  float alpha = (p2.cross(p3)).dot(n);
  alpha /= area;

  // area v1-q-v3
  float beta = (p3.cross(p1)).dot(n);
  beta /= area;

  // area v1-q-v2
  float gamma = 1.0f - alpha - beta;

  // Done.
  return vec3d(alpha, beta, gamma);
}
