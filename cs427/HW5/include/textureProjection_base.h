#ifndef _TEXTUREPROJECTION_H_
#define _TEXTUREPROJECTION_H_

#include <ostream>

#include "vec2d.h"
#include "triangle.h"
#include "transformation3d.h"

//////////////////////////////////////////////////
// Abstract super class for texture projections //
//////////////////////////////////////////////////
class textureProjection_base {
 public:
  //////////////////
  // Constructors //
  //////////////////
  textureProjection_base(void);
  textureProjection_base(const transformation3d& t);
  textureProjection_base(const textureProjection_base& tp);

  /////////////
  // Methods //
  /////////////
  void apply(triangle& t) const;

  /////////////
  // Friends //
  /////////////
  friend std::ostream& operator<<(std::ostream& s, const textureProjection_base& tp)
  {
    tp._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  void _assign(const textureProjection_base& tp);
  void _swap(textureProjection_base& tp);

  virtual void _print(std::ostream& s) const = 0;
  virtual vec2d computeTextureCoordinate(const vec3d& v) const = 0;

  ////////////////////////////
  // Protected Data Members //
  ////////////////////////////
  transformation3d _transformation;
};

#endif /* _TEXTUREPROJECTION_H_ */
