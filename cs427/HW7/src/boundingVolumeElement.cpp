#include "constants.h"
#include "boundingVolumeElement.h"
#include <iostream>

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
  //std::cout << "Starting a bve: " << end_index - start_index << std::endl;
  
  
  
  //down to leaf, store triangle
  if((end_index - start_index) <= 0){  	
  	_triangle = triangleList[start_index];
  	_bb = boundingBox();
  	_bb.expand(triangleList[start_index]->vertex(0), EPSILON);
		_bb.expand(triangleList[start_index]->vertex(1), EPSILON);
		_bb.expand(triangleList[start_index]->vertex(2), EPSILON);
  }
  else{
  	//sort objects using centroid (mergesort)
  	//give a random, or increment
  	int axis = rand() % 3;
  	axis = 0;
  	quicksort(triangleList, start_index, end_index, axis);
  	
  	//set left and right children
  	_left = new boundingVolumeElement(triangleList, start_index, (start_index + end_index)/2);
  	_right = new boundingVolumeElement(triangleList, ((start_index + end_index)/2)+ 1 , end_index );
  	
  	//set parent bounding box
  	_bb = _left->_bb + _right->_bb;
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
  //std::cout << "isBoundingBoxHit: " << _bb.isHit(r) << std::endl;
  return _bb.isHit(r);
}


bool boundingVolumeElement::isHit(const ray& r) const
{
  // Homework 7: returns true if this element or any of its children is hit by the ray r.
  //        modifies: nothing
  //        returns: true/false on hit/miss
  
  //test if you hit the bounding volume
  
  //test the children
  if(_triangle == NULL){
  	if(_left->isBoundingBoxHit(r)){
  		if(_left -> isHit(r))
  			return true;
  	}
  	if(_right->isBoundingBoxHit(r)){
  		if(_right -> isHit(r))
  			return true;
		}
  }else{
    float t;
    vec3d barycentric;
    return _triangle->intersect(r, barycentric, t);
  }
  return false;
}


intersectionPoint boundingVolumeElement::intersect(const ray& r, const triangleMesh& mesh) const
{
  // Homework 7: returns the intersection point of the triangle (stored in this element or any of its children) closest to the origin on the ray r.
  //             Note that the triangleMesh is provided in order to be able to create an intersection point (which needs the material, and which is
  //             not stored in the mesh).  You can assume that the mesh is the same as the one that was used for creating the bounding volume hierarchy.
  //        modifies: nothing
  //        returns: intersection point of the hit
  //return intersectionPoint();
  intersectionPoint ip = intersectionPoint(), leftIP, rightIP, tempIP;
  
  //check if at leaf, if so: calculate intersectionPoint, else recurse further down
  if(_left == NULL && _right == NULL){
    float t;
    vec3d barycentric;
    if(isBoundingBoxHit(r)){  // hit?
    	if(_triangle -> intersect(r, barycentric, t)){
				ip = intersectionPoint(r, barycentric, t, *_triangle, mesh.getMaterial());
    	}
		}
  }else{ //recurse through tree
  	if(_left != NULL && _left->isBoundingBoxHit(r)){
			leftIP = _left->intersect(r, mesh);
		}
		if(_right != NULL && _right -> isBoundingBoxHit(r)){
  		rightIP = _right->intersect(r, mesh);
  	}
  	if(leftIP < rightIP){
  		ip = leftIP;
  	}else{
  		ip = rightIP;
  	}
	}
	return ip;
}



/////////////////////
// Private Methods //
/////////////////////
float boundingVolumeElement::centroid(const std::vector<const triangle*>& list, unsigned int index, unsigned int coord)
{
  return (list[index]->vertex(0)[coord] + list[index]->vertex(1)[coord] + list[index]->vertex(2)[coord]) / 3.0f;
}
void boundingVolumeElement::quicksort(std::vector<const triangle*>& _group, unsigned int left, unsigned int right, int axis){
	int i = left, j = right;
      const triangle* tmp;
      float pivot = centroid(_group, (left + right) / 2, axis);
 
      /* partition */
      while (i <= j) {
            while (centroid(_group, i, axis) < pivot)
                  i++;
            while (centroid(_group, j, axis) > pivot)
                  j--;
            if (i <= j) {
                  tmp = _group[i];
                  _group[i] = _group[j];
                  _group[j] = tmp;
                  i++;
                  j--;
            }
      };
 
      /* recursion */
      if (left < j)
            quicksort(_group, left, j, axis);
      if (i < right)
            quicksort(_group, i, right, axis);
}
/*
void boundingVolumeElement::quicksort(std::vector<const triangle*>& _group, unsigned int left, unsigned int right, int axis){
	if(left + 10 <= right){
		float pivot = centroid(_group, median_of_3(_group, left, right, axis), axis);
		
		int i = left, j = right-1;
		for(;;){
			while(centroid(_group, ++i, axis) < pivot){}
			while(pivot < centroid(_group, --j, axis)){}
			if(i < j)
				swap(_group, i, j);
			else
				break;
		}
		
		swap(_group, i, right-1); //Restore Pivot
		quicksort(_group, left, i-1, axis); //sort small elements
		quicksort(_group, i+1, right, axis); //sort large elements		
	}else{ //do an insertion sort on the subarrays
		int x;
  	for(int p = left; p < right; p++){
	  	float tmp = centroid(_group, p, axis);
	  	for( x = p; x > 0 && tmp < centroid(_group, x-1, axis); x--){
	  		_group[x] = _group[x-1];
	  	}
	  	_group[x] = _group[p];
  	} 
	}	
}

float boundingVolumeElement::median_of_3(std::vector<const triangle*>& _group, unsigned int left, unsigned int right, int axis){
	int center = (left + right) / 2;
	if(centroid(_group, center, axis) < centroid(_group, left, axis))
		swap(_group, left, center);
  if(centroid(_group, right, axis) < centroid(_group, left, axis))
      swap( _group, left, right );
  if( centroid(_group, right, axis) < centroid(_group, center, axis) )
      swap(_group, center, right);

      // Place pivot at position right - 1
  swap( _group, center, right - 1);
  return centroid(_group, right-1, axis);
}*/

void boundingVolumeElement::swap(std::vector<const triangle*>& _group, int a, int b){
	const triangle* temp = _group[a];
	_group[a] = _group[b];
	_group[b] = temp;
}



/*
void GroupOfNumbers::mergesort(std::vector<const triangle*>& temp_group, unsigned int left, unsigned int right){
	if(left < right){
		int center = (left + right) / 2;
		mergesort(temp_group, left, center);
		mergesort(temp_group, center+1, right);
		merge(temp_group, left, center+1, right);  	
	}
}  
void GroupOfNumbers::merge(std::vector<const triangle*>& _group, int leftPos, int rightPos, int rightEnd){
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;
	
	while(leftPos <= leftEnd && rightPos <= rightEnd)
		if(_group[leftPos] <= _group[rightPos])
			temp_group[tmpPos++] = _group[leftPos++];
		else
			temp_group[tmpPos++] = _group[rightPos++];
	while(leftPos <= leftEnd) //Copy rest of first half
		temp_group[tmpPos++] = _group[leftPos++];
	while(rightPos <= rightEnd) //Copy rest of right half
		temp_group[tmpPos++] = _group[rightPos++];
		
	//Copy tmpArray back
	for(int i = 0; i < numElements; i++, rightEnd--)
		_group[rightEnd] = temp_group[rightEnd];
}
*/
