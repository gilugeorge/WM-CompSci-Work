#ifndef _REFLECTANCECOMPONENT_H_
#define _REFLECTANCECOMPONENT_H_

#include "color.h"
#include "vec2d.h"
#include "vec3d.h"
#include "brdf_base.h"
#include "albedo_base.h"

class reflectanceComponent {
 public:
  /////////////////
  // Constructor //
  /////////////////
  reflectanceComponent(const albedo_base* albedo, const brdf_base* brdf);
  reflectanceComponent(const reflectanceComponent& rc);

  ///////////////
  // Operators //
  ///////////////
  reflectanceComponent& operator=(const reflectanceComponent& rc);

  /////////////
  // Methods //
  /////////////
  color evaluate(const vec3d& in, const vec3d& normal, const vec3d& out, const vec2d& textureCoord) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(reflectanceComponent& a, reflectanceComponent& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const reflectanceComponent& rf)
  {
    s << "[" << *(rf._albedo) << " x " << *(rf._brdf) << "]";
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(reflectanceComponent& rc);
  void _assign(const reflectanceComponent& rc);

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  const albedo_base* _albedo;
  const brdf_base*   _brdf;
};

#endif /* _REFLECTANCECOMPONENT_H_ */

