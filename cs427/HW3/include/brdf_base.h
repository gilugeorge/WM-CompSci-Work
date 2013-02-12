#ifndef _BRDF_BASE_H_
#define _BRDF_BASE_H_

#include <ostream>

#include "vec3d.h"

///////////////////////////////////
// Abstract base class for brdfs //
///////////////////////////////////
class brdf_base {
 public:
  /////////////
  // Methods //
  /////////////

  // in    : pointing towards the light source
  // out   : pointing towards the eye
  // normal: surface normal
  virtual float evaluate(const vec3d& in, const vec3d& normal, const vec3d& out) const = 0;

  /////////////
  // Friends //
  /////////////
  friend std::ostream& operator<<(std::ostream& s, const brdf_base& b)
  {
    b._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  virtual void _print(std::ostream& s) const = 0;
};

#endif /* _BRDF_BASE_H_ */
