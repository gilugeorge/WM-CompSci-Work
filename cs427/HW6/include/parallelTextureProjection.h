#ifndef _PARALLELTEXTUREPROJECTION_H_
#define _PARALLELTEXTUREPROJECTION_H_

#include "vec2d.h"
#include "textureProjection_base.h"

class parallelTextureProjection : public textureProjection_base {
 public:
  //////////////////
  // Constructors //
  //////////////////
  parallelTextureProjection(void);
  parallelTextureProjection(const transformation3d& t);
  parallelTextureProjection(const parallelTextureProjection& ptp);

  ///////////////
  // Operators //
  ///////////////
  parallelTextureProjection& operator=(const parallelTextureProjection& ptp);

  /////////////
  // Friends //
  /////////////
  friend void swap(parallelTextureProjection& a, parallelTextureProjection& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const parallelTextureProjection& ptp)
  {
    ptp._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  void _assign(const parallelTextureProjection& ptp);
  void _swap(parallelTextureProjection& ptp);
  virtual void _print(std::ostream& s) const;

  virtual vec2d computeTextureCoordinate(const vec3d& v) const;
};

#endif /* _PARALLELTEXTUREPROJECTION_H_ */
