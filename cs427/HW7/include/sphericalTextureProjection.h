#ifndef _SPHERICALTEXTUREPROJECTION_H_
#define _SPHERICALTEXTUREPROJECTION_H_

#include "vec2d.h"
#include "textureProjection_base.h"

class sphericalTextureProjection : public textureProjection_base {
 public:
  //////////////////
  // Constructors //
  //////////////////
  sphericalTextureProjection(void);
  sphericalTextureProjection(const transformation3d& t);
  sphericalTextureProjection(const sphericalTextureProjection& stp);

  ///////////////
  // Operators //
  ///////////////
  sphericalTextureProjection& operator=(const sphericalTextureProjection& stp);

  /////////////
  // Friends //
  /////////////
  friend void swap(sphericalTextureProjection& a, sphericalTextureProjection& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const sphericalTextureProjection& stp)
  {
    stp._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  void _assign(const sphericalTextureProjection& stp);
  void _swap(sphericalTextureProjection& stp);
  virtual void _print(std::ostream& s) const;

  virtual vec2d computeTextureCoordinate(const vec3d& v) const;
};

#endif /* _SPHERICALTEXTUREPROJECTION_H_ */
