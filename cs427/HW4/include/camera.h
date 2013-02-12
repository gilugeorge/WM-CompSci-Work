#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <ostream>

#include "ray.h"
#include "vec3d.h"
#include "transformation3d.h"

class camera {
 public:
  /////////////////
  // Constructor //
  /////////////////
  camera(void);
  camera(const vec3d& eye, const vec3d& viewDirection, const vec3d& up, float fov, size_t xres, size_t yres);
  camera(const camera& cam);

  ///////////////
  // Operators //
  ///////////////
  camera& operator=(const camera& cam);

  ray operator()(float x, float y) const;

  /////////////
  // Methods //
  /////////////
  ray generateViewRay(float x, float y) const;

  ////////////////
  // Inspectors //
  ///////////////
  const vec3d& origin(void) const;
  const vec3d& view(void) const;
  const vec3d& up(void) const;
  float fov(void) const;
  size_t width(void) const;
  size_t height(void) const;

  //////////////
  // Mutators //
  //////////////
  void transform(const transformation3d& t);
  void inverseTransform(const transformation3d& t);

  /////////////
  // Friends //
  /////////////
  friend void swap(camera& a, camera& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const camera& cam)
  {
    s << "Camera: {";
    s << "origin=" << cam._origin << ", ";
    s << "view=" << cam._view << ", ";
    s << "up=" << cam._up << "}, ";
    s << "fov=" << cam._fov << ", ";
    s << "resolution=[" << cam._width << "x" << cam._height << "]";
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(camera& cam);
  void _assign(const camera& cam);

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  vec3d _origin, _view, _up;
  float _fov;
  size_t _width, _height;
};


#endif /* _CAMERA_H_ */
