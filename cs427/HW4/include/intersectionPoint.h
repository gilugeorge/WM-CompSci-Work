#ifndef _INTERSECTIONPOINT_H_
#define _INTERSECTIONPOINT_H_

#include "ray.h"
#include "vec2d.h"
#include "vec3d.h"
#include "triangle.h"
#include "material.h"
#include "transformation3d.h"
#include "lightsource_base.h"

class intersectionPoint {
 public:
  /////////////////
  // Constructor //
  /////////////////
  intersectionPoint(void);
  intersectionPoint(const ray& r, const vec3d& barycentricCoord, float rayParameter, const triangle& t, const material& mat);
  intersectionPoint(const intersectionPoint& ip);

  ///////////////
  // Operators //
  ///////////////
  intersectionPoint& operator=(const intersectionPoint& ip);

  bool operator<(const intersectionPoint& ip) const;
  bool operator<(float rayParameter) const;
  bool operator<(const vec3d& point) const;

  bool operator>(const intersectionPoint& ip) const;
  bool operator>(float rayParameter) const;
  bool operator>(const vec3d& point) const;

  ////////////////
  // Inspectors //
  ////////////////
  const ray& getRay(void) const;
  float rayParameter(void) const;
  const vec3d& point(void) const;
  const vec3d& normal(void) const;
  const vec2d& textureCoordinate(void) const;

  /////////////
  // Methods //
  /////////////
  bool isHit(void) const;

  void transform(const transformation3d& t);
  void inverseTransform(const transformation3d& t);

  color evaluate(const lightsource_base& ls) const;
  color evaluate(const vec3d& dir) const;
  
  //////////////
  // Friends //
  /////////////
  friend void swap(intersectionPoint& a, intersectionPoint& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const intersectionPoint& ip)
  {
    if(ip._hit) s << "IntersectionPoint: ray=" << ip._r << ", point=" << ip._point << " (parameter=" << ip._rayParameter << ", normal=" << ip._normal << ", texture coordinate=" << ip._textureCoord << ", material=" << ip._material;
    else s << "IntersectionPoint: empty";
    return s;
  }
 
 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(intersectionPoint& ip);
  void _assign(const intersectionPoint& ip);

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  ray _r;
  bool _hit;
  float _rayParameter;
  vec3d _point;
  vec3d _normal;
  vec2d _textureCoord;
  material _material;
};

#endif /* _INTERSECTIONPOINT_H_ */
