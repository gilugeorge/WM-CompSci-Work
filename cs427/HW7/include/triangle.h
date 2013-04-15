#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <ostream>

#include "ray.h"
#include "vec2d.h"
#include "vec3d.h"
#include "transformation3d.h"

class triangle {
 public:
  /////////////////
  // Constructor //
  /////////////////
  triangle(const vec3d& v1=vec3d(0.0f, 0.0f, 0.0f), const vec3d& v2=vec3d(1.0f, 0.0f, 0.0f), const vec3d& v3=vec3d(0.0f, 1.0f, 0.0f));
  triangle(const vec3d& v1, const vec3d& v2, const vec3d& v3, const vec3d& n1, const vec3d& n2, const vec3d& n3, const vec2d& t1, const vec2d& t2, const vec2d& t3);
  triangle(const triangle& t);

  ////////////////
  // Destructor //
  ////////////////
  ~triangle(void) {}

  ////////////////
  // Inspectors //
  ////////////////
  const vec3d& vertex(size_t index) const;
  vec3d normal(void) const;

  //////////////
  // Mutators //
  //////////////
  void transform(const transformation3d& t);
  void inverseTransform(const transformation3d& t);

  void setVertices(const vec3d& v1, const vec3d& v2, const vec3d& v3);
  void setNormals(const vec3d& n1, const vec3d& n2, const vec3d& n3);
  void setTextureCoordinates(const vec2d& t1, const vec2d& t2, const vec2d& t3);

  ///////////////
  // Operators //
  ///////////////
  triangle operator=(const triangle& t);

  /////////////
  // Methods //
  /////////////
  bool intersect(const ray& r, vec3d& barycentricCoord, float& t) const;

  vec3d interpolateVertex(const vec3d& barycentricCoord) const;
  vec3d interpolateNormal(const vec3d& barycentricCoord) const;
  vec2d interpolateTextCoord(const vec3d& barycentricCoord) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(triangle& a, triangle& b) { a._swap(b); }
  
  friend std::ostream& operator<<(std::ostream& s, const triangle& t)
  {
    s << "Triangle: v=(" << t._vertex[0]   << "," << t._vertex[1]   << "," << t._vertex[2]   << "), ";
    s           << "n=(" << t._normal[0]   << "," << t._normal[1]   << "," << t._normal[2]   << "), ";
    s           << "t=(" << t._texCoord[0] << "," << t._texCoord[1] << "," << t._texCoord[2] << ")";
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(triangle& t);
  void _assign(const triangle& t);

  bool _planeIntersection(const ray& r, float& t) const;
  vec3d _barycentricCoord(const ray& r, float t) const;

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  vec3d _vertex[3];
  vec3d _normal[3];
  vec2d _texCoord[3];
};

#endif /* _TRIANGLE_H_ */
