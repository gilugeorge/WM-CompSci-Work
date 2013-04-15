#ifndef _DIFFUSE_H_
#define _DIFFUSE_H_

#include <ostream>

#include "vec3d.h"
#include "brdf_base.h"

class diffuse : public brdf_base {
 public:
  /////////////////
  // Constructor //
  /////////////////
  diffuse(void);
  diffuse(const diffuse& d);

  ///////////////
  // Operators //
  ///////////////
  diffuse& operator=(const diffuse& d);

  /////////////
  // Methods //
  /////////////
  virtual float evaluate(const vec3d& in, const vec3d& normal, const vec3d& out) const;

  ////////////
  // Frieds //
  ////////////
  friend void swap(diffuse& a, diffuse& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const diffuse& d)
  {
    d._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  void _swap(diffuse& d);
  void _assign(const diffuse& d);
  virtual void _print(std::ostream& s) const;
};

#endif /* _DIFFUSE_H_ */
