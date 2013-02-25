#ifndef _TRANSFORMATION3D_H_
#define _TRANSFORMATION3D_H_

#include <ostream>

#include "vec3d.h"
#include "mat3d.h"

class transformation3d {
 public:
  //////////////////
  // Constructors //
  //////////////////
  transformation3d(void);
  transformation3d(const vec3d& translation, const mat3d& transformation, const mat3d& inverseTransform);
  transformation3d(const transformation3d& t);

  //////////////
  // Operator //
  //////////////
  transformation3d& operator=(const transformation3d& t);

  //////////////
  // Mutators //
  //////////////
  void transform(const transformation3d& t);
  void inverseTransform(const transformation3d& t);

  /////////////
  // Methods //
  /////////////
  vec3d transformPoint(const vec3d& p) const;
  vec3d transformDirection(const vec3d& d) const;
  vec3d transformNormal(const vec3d& n) const;

  vec3d inverseTransformPoint(const vec3d& p) const;
  vec3d inverseTransformDirection(const vec3d& d) const;
  vec3d inverseTransformNormal(const vec3d& n) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(transformation3d& a, transformation3d& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const transformation3d& t)
  {
    s << "{";
    s << "Translation = " << t._translation << ", ";
    s << "Transformation = " << t._transformation << ", ";
    s << "Inverse Trans. = " << t._inverseTransformation;
    s << "}";
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  void _swap(transformation3d& t);
  void _assign(const transformation3d& t);

  ////////////////////////////
  // Protected Data Members //
  ////////////////////////////
  vec3d _translation;
  mat3d _transformation;
  mat3d _inverseTransformation;
};

#endif /* _TRANSFORMATION3D_H_ */
