#ifndef _SPOTLIGHTSOURCE_H_
#define _SPOTLIGHTSOURCE_H_

#include "vec3d.h"
#include "color.h"
#include "lightsource_base.h"

class spotLightsource : public lightsource_base {
 public:
  //////////////////
  // Constructors //
  //////////////////
  spotLightsource(const vec3d& position=vec3d(0.0f, 0.0f, 0.0f), const color& intensity=color(1.0f, 1.0f, 1.0f), const vec3d& direction=vec3d(0.0f, 0.0f, 1.0f), float cutoffDegrees=30.0f, float sharpness=1.0f, const vec3d& attenuation=vec3d(0.0f, 0.0f, 1.0f));
  spotLightsource(const spotLightsource& ls);

  ///////////////
  // Operators //
  ///////////////
  spotLightsource& operator=(const spotLightsource& ls);

  /////////////
  // Methods //
  /////////////
  virtual vec3d getDirection(const vec3d& point) const;
  virtual color getIntensity(const vec3d& point, const vec3d& dir) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(spotLightsource& a, spotLightsource& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const spotLightsource& ls)
  {
    ls._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  void _swap(spotLightsource& ls);
  void _assign(const spotLightsource& ls);
  virtual void _print(std::ostream& s) const;

  ////////////////////////////
  // Protected Data Members //
  ////////////////////////////
  vec3d _position;
  color _intensity;
  vec3d _direction;
  float _cutoff;
  float _sharpness;
  vec3d _attenuation;
};


#endif /* _SPOTLIGHTSOURCE_H_ */
