#ifndef _PHONG_H_
#define _PHONG_H_

#include <ostream>

#include "vec3d.h"
#include "brdf_base.h"

class phong : public brdf_base {
 public:
  /////////////////
  // Constructor //
  /////////////////
  phong(float sharpness=1.0f);
  phong(const phong& d);

  ///////////////
  // Operators //
  ///////////////
  phong& operator=(const phong& d);

  /////////////
  // Methods //
  /////////////
  virtual float evaluate(const vec3d& in, const vec3d& normal, const vec3d& out) const;

  ////////////
  // Frieds //
  ////////////
  friend void swap(phong& a, phong& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const phong& d)
  {
    d._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  void _swap(phong& d);
  void _assign(const phong& d);
  virtual void _print(std::ostream& s) const;

  ////////////////////////////
  // Protected Data Members //
  ////////////////////////////
  float _sharpness;
};

#endif /* _PHONG_H_ */
