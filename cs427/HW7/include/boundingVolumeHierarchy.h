#ifndef _BVH_H_
#define _BVH_H_

#include "ray.h"
#include "triangleMesh.h"
#include "intersectionPoint.h"
#include "boundingVolumeElement.h"

class boundingVolumeHierarchy {
 public:
  //////////////////
  // Constructors //
  //////////////////
  boundingVolumeHierarchy(const triangleMesh& mesh);

  ////////////////
  // Destructor //
  ////////////////
  ~boundingVolumeHierarchy(void);

  /////////////
  // Methods //
  /////////////
  bool isHit(const ray& r) const;
  intersectionPoint intersect(const ray& r) const;

 private:
  //////////////////////////
  // Private Data Members //
  //////////////////////////
  const triangleMesh* _mesh;
  boundingVolumeElement* _root;
};

#endif /* _BVH_H_ */
