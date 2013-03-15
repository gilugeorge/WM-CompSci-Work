#ifndef _SCENEGRAPH_BASE_H_
#define _SCENEGRAPH_BASE_H_

#include <ostream>

#include "ray.h"
#include "boundingbox.h"
#include "transformation3d.h"
#include "intersectionPoint.h"

//////////////////////////////////////////////
// Abstract class for a scene graph element //
//////////////////////////////////////////////
class sceneGraph_base {
 public:
  ////////////////
  // Destructor //
  ////////////////
  virtual ~sceneGraph_base(void) {}

  /////////////
  // Methods //
  /////////////
  virtual boundingBox returnBoundingBox(void) const = 0;
  virtual bool isHit(const ray& r) const = 0;
  virtual intersectionPoint intersect(const ray& r) const = 0;

  /////////////
  // Friends //
  /////////////
  friend std::ostream& operator<<(std::ostream& s, const sceneGraph_base& sg)
  {
    sg._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  virtual void _print(std::ostream& s) const = 0;
};

#endif /* _SCENEGRAPH_BASE_H_ */
