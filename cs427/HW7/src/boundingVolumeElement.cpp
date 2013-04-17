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
  
  
  vec3d empty(-1.0f);
  //down to leaf, store triangle
  if((end_index - start_index) <= 0){
  	//std::cout << "Adding a Leaf! " << triangleList[start_index]->vertex(0) << triangleList[start_index]->vertex(1) << triangleList[start_index]->vertex(2) << std::endl;
  	
  	_triangle = triangleList[start_index];
  }
  else{
  	//std::cout << "Not a leaf, set _bb" << std::endl;
  	//set bounding volume
  	vec3d lfb(-1.0f);
  	vec3d rbt(-1.0f);
  	//vec3d vert0, vert1, vert2; 
  	for(int i = start_index; i < end_index; i++){
  		if(lfb == empty){
  			_bb = boundingBox();
  			lfb += vec3d(1.0f);
  			std::cout << "_bb empty" << std::endl;
  		}
  	
  		_bb.expand(triangleList[i]->vertex(0), EPSILON);
  		_bb.expand(triangleList[i]->vertex(1), EPSILON);
  		_bb.expand(triangleList[i]->vertex(2), EPSILON);
  		//std::cout << "Begin checking verts" << std::endl;
  		/*
  		vert0 = triangleList[i]->vertex(0);
  		if(lfb == empty || rbt == empty){
  			lfb = vert0;
  			rbt = vert0;
  		//	std::cout << "setting initial lfb rbt" << lfb << ", " << rbt << std::endl;
  		}else if(vert0.length() < lfb.length()){
  			lfb = vert0;
  		}else if(vert0.length() > rbt.length()){
  			rbt = vert0;
  		}
  		//std::cout << "After vert0 lfb: " << lfb << ", rbt: " << rbt << std::endl;
  		
  		
  		vert1 = triangleList[i]->vertex(1);
  		//std::cout << "about to check vert1: " << vert1 << std::endl;
  		if(vert1.length() < lfb.length()){
  			lfb = vert1;
  		}else if(vert1.length() > rbt.length()){
  			rbt = vert1;
  		//	std::cout << "rbt updated" << rbt << std::endl;
  		}
  		//std::cout << "After vert1 lfb: " << lfb << ", rbt: " << rbt << std::endl;
  		
  		
  		vert2 = triangleList[i]->vertex(2);
  		//std::cout << "about to check vert2: " << vert2 << std::endl;
  		if(vert2.length() < lfb.length()){
  			lfb = vert2;
  		}else if(vert2.length() > rbt.length()){
  			rbt = vert2;
  		}
  		//std::cout << "After vert2 lfb: " << lfb << ", rbt: " << rbt << std::endl;	
  		*/
  		
  	}
  	
  	
  	//sort objects using centroid (mergesort)
  	//std::cout << "Sort triangles from index: " << start_index << ", "<< end_index << std::endl;
  	int axis = 0;
  	quicksort(triangleList, start_index, end_index, axis);
  	
  	
  	//set left and right children
  	//std::cout << "Recurse to left: " << start_index << ", "<< end_index/2 <<std::endl;
  	_left = new boundingVolumeElement(triangleList, start_index, (start_index + end_index)/2);
  	//std::cout << "Recurse to right: " << (end_index/2)+ 1 << ", "<< end_index <<std::endl;
  	_right = new boundingVolumeElement(triangleList, ((start_index + end_index)/2)+ 1 , end_index );
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
  if(!isBoundingBoxHit(r)){
  	std::cout << "Returning False isHit()" << std::endl;
  	return false;
  }
  std::cout << "checking isHit" << std::endl;
  if(_triangle == NULL){
  	_left -> isHit(r);
  	_right -> isHit(r);
  }else{
  	// hit?
    float t;
    vec3d barycentric;
    if(_triangle->intersect(r, barycentric, t)) 
    	return true;
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
  return intersectionPoint();
  intersectionPoint ip, leftIP, rightIP;
  
  //check if at leaf, if so: calculate intersectionPoint, else recurse further down
  if(_left == NULL && _right == NULL){
    float t;
    vec3d barycentric;
    if(isHit(r)){  // hit?
    	_triangle -> intersect(r, barycentric, t);
			ip = intersectionPoint(r, barycentric, t, *_triangle, mesh.getMaterial());
		}else{
			ip = intersectionPoint();
		}	
  }else{ //recurse through tree
		leftIP = _left->intersect(r, mesh);
  	rightIP = _right->intersect(r, mesh);
  	if(leftIP > rightIP){
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
	if(left + 10 <= right){
		float pivot = median_of_3(_group, left, right, axis);
		
		int i = left, j = right-1;
		for(;;){
			while(centroid(_group, ++i, axis) < pivot){}
			while(pivot < centroid(_group, --j, axis)){}
			if(i < j)
				std::swap(_group[i], _group[j]);
			else
				break;
		}
		
		std::swap(_group[i], _group[right-1]); //Restore Pivot
		quicksort(_group, left, i-1, axis); //sort small elements
		quicksort(_group, i+1, right, axis); //sort large elements  		
	}else{ //do an insertion sort on the subarrays
		int x;  	
  	for(int p = left; p < right; p++){
	  	long tmp = centroid(_group, p, axis);
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
		std::swap(_group[left], _group[center]);
  if(centroid(_group, right, axis) < centroid(_group, left, axis))
      std::swap( _group[left], _group[right] );
  if( centroid(_group, right, axis) < centroid(_group, center, axis) )
      std::swap( _group[center], _group[right] );

      // Place pivot at position right - 1
  std::swap( _group[center], _group[right - 1] );
  return centroid(_group, right-1, axis);
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
