#ifndef _DIRECTIONALLIGHTSOURCE_H_
#define _DIRECTIONALLIGHTSOURCE_H_

#include "vec3d.h"
#include "color.h"
#include "lightsource_base.h"

class directionalLightsource : public lightsource_base {
 public:
  //////////////////
  // Constructors //
  //////////////////
  directionalLightsource(const color& intensity=color(1.0f, 1.0f, 1.0f), const vec3d& dir=vec3d(0.0f, 0.0f, 1.0f));
  directionalLightsource(const directionalLightsource& ls);

  ///////////////
  // Operators //
  ///////////////
  directionalLightsource& operator=(const directionalLightsource& ls);

  /////////////
  // Methods //
  /////////////
  virtual vec3d getDirection(const vec3d& point) const;
  virtual color getIntensity(const vec3d& point, const vec3d& dir) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(directionalLightsource& a, directionalLightsource& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const directionalLightsource& ls)
  {
    ls._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  void _swap(directionalLightsource& ls);
  void _assign(const directionalLightsource& ls);
  virtual void _print(std::ostream& s) const;

  ////////////////////////////
  // Protected Data Members //
  ////////////////////////////
  color _intensity;
  vec3d _direction;
};


#endif /* _DIRECTIONALLIGHTSOURCE_H_ */
