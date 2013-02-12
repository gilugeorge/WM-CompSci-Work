#ifndef _RAY_H_
#define _RAY_H_

#include <ostream>

#include "vec3d.h"
#include "transformation3d.h"

class ray
{
 public:
  //////////////////
  // Constructors //
  //////////////////
  ray(const vec3d& origin = vec3d(0.0f, 0.0f, 0.0f), const vec3d& direction = vec3d(0.0f, 0.0f, 1.0f));
  ray(const ray& r);

  ////////////////
  // Destructor //
  ////////////////
  ~ray(void) {}

  ////////////////
  // Inspectors //
  ////////////////
  const vec3d& origin(void) const;
  const vec3d& direction(void) const;

  //////////////
  // Mutators //
  //////////////
  ray& operator=(const ray& r);

  void setOrigin(const vec3d& origin);
  void setDirection(const vec3d& direction);

  void transform(const transformation3d& t);
  void inverseTransform(const transformation3d& t);

  /////////////
  // Methods //
  /////////////
  vec3d evaluate(float t) const;
  vec3d operator()(float t) const;

  float distanceToRay(const vec3d& point) const;
  vec3d closestPointOnRay(const vec3d& point) const;
  
  float getParameter(const vec3d& point) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(ray& a, ray& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const ray& r)
  {
    s << r.origin() << "->" << r.direction();
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(ray& r);
  void _assign(const ray& r);

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  vec3d _origin;
  vec3d _direction;
};


#endif /* _RAY_H_ */
