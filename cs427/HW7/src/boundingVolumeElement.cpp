#include "constants.h"
#include "boundingVolumeElement.h"


//////////////////
// Constructor //
/////////////////
boundingVolumeElement::boundingVolumeElement(std::vector<const triangle*>& triangleList, unsigned int start_index, unsigned int end_index)
{
  // init
  _left = _right = NULL;
  _triangle = NULL;

  // Homework 7: This is the constructor that will create the bounding volume hierarchy. This hierarchy will be in the form of a binary tree, where each bounding
  //             volume element refers to zero, one or two child elements. As input you get a list of (pointers to) triangles, and a start and end index
  //             which indicate which part of the triangleList you need to create the bounding volume hierarchy for: triangleList[start_index] to 
  //             (including) triangleList[end_index].  The object itself stores the following information: a bounding box, a pointer to two child elements (_left and 
  //             _right), and a pointer to a triangle (_triangle).  You are free to choose whether you want to include a triangle in every element, or only at the leaf
  //             nodes (in which case you leave the pointer to _triangle at NULL).
  //     modifies: triangleList can be altered (optional).  Note that you can only change the _order_ of the pointers, not the content of the linked triangles.
  //     returns: nothing
  
  //down to leaf, store triangle
  if(end_index - start_index == 0){
  	_triangle = triangleList[start_index];
  }
  else{
  	//sort objects using centroid (mergesort)
  	
  	
  	//set left and right children
  	_left = new boundingVolumeElement(triangleList, start_index, end_index/2);
  	_right = new boundingVolumeElement(triangleList, (end_index/2)+ 1, end_index );
  	
  }
  
  
}



////////////////
// Destructor //
////////////////
boundingVolumeElement::~boundingVolumeElement(void)
{
  if(_left) delete _left;
  if(_right) delete _right;
  if(_triangle) _triangle = NULL;
}



/////////////
// Methods //
/////////////
bool boundingVolumeElement::isBoundingBoxHit(const ray& r) const
{
  // Homework 7: returns true if the bounding box of this node is hit by the ray r.
  //        modifes: nothing
  //        returns: true/false when hit/missed.
  return false;
}


bool boundingVolumeElement::isHit(const ray& r) const
{
  // Homework 7: returns true if this element or any of its children is hit by the ray r.
  //        modifies: nothing
  //        returns: true/false on hit/miss
  return false;
}


intersectionPoint boundingVolumeElement::intersect(const ray& r, const triangleMesh& mesh) const
{
  // Homework 7: returns the intersection point of the triangle (stored in this element or any of its children) closest to the origin on the ray r.
  //             Note that the triangleMesh is provided in order to be able to create an intersection point (which needs the material, and which is
  //             not stored in the mesh).  You can assume that the mesh is the same as the one that was used for creating the bounding volume hierarchy.
  //        modifies: nothing
  //        returns: intersection point of the hit
  return intersectionPoint();
}



/////////////////////
// Private Methods //
/////////////////////
float boundingVolumeElement::centroid(const std::vector<const triangle*>& list, unsigned int index, unsigned int coord)
{
  return (list[index]->vertex(0)[coord] + list[index]->vertex(1)[coord] + list[index]->vertex(2)[coord]) / 3.0f;
}

