#ifndef _POINTLIGHTSOURCE_H_
#define _POINTLIGHTSOURCE_H_

#include "vec3d.h"
#include "color.h"
#include "lightsource_base.h"

class pointLightsource : public lightsource_base {
 public:
  //////////////////
  // Constructors //
  //////////////////
  pointLightsource(const vec3d& position=vec3d(0.0f, 0.0f, 0.0f), const color& intensity=color(1.0f, 1.0f, 1.0f), const vec3d& attenuation=vec3d(0.0f, 0.0f, 1.0f));
  pointLightsource(const pointLightsource& ls);

  ///////////////
  // Operators //
  ///////////////
  pointLightsource& operator=(const pointLightsource& ls);

  /////////////
  // Methods //
  /////////////
  virtual vec3d getDirection(const vec3d& point) const;
  virtual color getIntensity(const vec3d& point, const vec3d& dir) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(pointLightsource& a, pointLightsource& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const pointLightsource& ls)
  {
    ls._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  void _swap(pointLightsource& ls);
  void _assign(const pointLightsource& ls);
  virtual void _print(std::ostream& s) const;

  ////////////////////////////
  // Protected Data Members //
  ////////////////////////////
  vec3d _position;
  color _intensity;
  vec3d _attenuation;
};


#endif /* _POINTLIGHTSOURCE_H_ */
