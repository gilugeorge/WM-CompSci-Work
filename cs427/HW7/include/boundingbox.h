#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include <ostream>

#include "ray.h"
#include "vec3d.h"


class boundingBox {
 public:
  /////////////////
  // Constructor //
  /////////////////
  boundingBox(void);
  boundingBox(const vec3d& lfb, const vec3d& rbt);
  boundingBox(const boundingBox& bb);
  
  ///////////////
  // Operators //
  ///////////////
  boundingBox& operator=(const boundingBox& src);

  boundingBox& operator+=(const boundingBox& bb);
  boundingBox operator+(const boundingBox& bb) const;

  ////////////////
  // Inspectors //
  ////////////////
  const vec3d& leftFrontBottom(void) const;
  const vec3d& rightBackTop(void) const;
  vec3d size(void) const;

  /////////////
  // Methods //
  /////////////
  void expand(const vec3d& p);
  void expand(const vec3d& p, float border);
  void expand(float border);

  bool isIn(const vec3d& p) const;
  bool isHit(const ray& r) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(boundingBox& a, boundingBox& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const boundingBox& bb)
  {
    s << bb._lfb << " - " << bb._rbt;
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(boundingBox& bb);
  void _assign(const boundingBox& bb);

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  vec3d _lfb, _rbt;
};

#endif /* _BOUNDINGBOX_H_ */
