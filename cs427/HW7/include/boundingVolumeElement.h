#ifndef _BVH_ELEMENT_H_
#define _BVH_ELEMENT_H_

#include <cstdlib>
#include <vector>
#include "triangle.h"
#include "triangleMesh.h"
#include "ray.h"
#include "vec3d.h"


class boundingVolumeElement {
 public:
  /////////////////
  // Constructor //
  /////////////////
  boundingVolumeElement(std::vector<const triangle*>& triangleList, unsigned int start_index, unsigned int end_index);


  ////////////////
  // Destructor //
  ////////////////
  ~boundingVolumeElement(void);


  /////////////
  // Methods //
  /////////////
  bool isBoundingBoxHit(const ray& r) const;
  bool isHit(const ray& r) const;
  intersectionPoint intersect(const ray& r, const triangleMesh& mesh) const;


 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  static float centroid(const std::vector<const triangle*>& list, unsigned int index, unsigned int coord);
	void quicksort(std::vector<const triangle*>& _group, unsigned int left, unsigned int right, int axis);
	float median_of_3(std::vector<const triangle*>& _group, unsigned int left, unsigned int right, int axis);
	void swap(std::vector<const triangle*>& _group, int a, int b);
	
  //////////////////////////
  // Private Data Members //
  //////////////////////////
  boundingBox _bb;
  boundingVolumeElement* _left;
  boundingVolumeElement* _right;
  const triangle* _triangle;
};

#endif /* _BVH_ELEMENT_H_ */
