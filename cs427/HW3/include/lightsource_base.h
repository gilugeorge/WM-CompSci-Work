#ifndef _LIGHTSOURCE_BASE_H_
#define _LIGHTSOURCE_BASE_H_

#include <ostream>

///////////////////////////////////////////
// Abstract base class for light sources //
///////////////////////////////////////////
class lightsource_base {
 public:
  /////////////
  // Methods //
  /////////////
  virtual vec3d getDirection(const vec3d& point) const = 0;
  virtual color getIntensity(const vec3d& point, const vec3d& dir) const = 0;

  /////////////
  // Friends //
  /////////////
  friend std::ostream& operator<<(std::ostream& s, const lightsource_base& ls)
  {
    ls._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  virtual void _print(std::ostream& s) const = 0;
};

#endif /* _LIGHTSOURCE_BASE_H_ */
