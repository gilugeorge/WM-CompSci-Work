#include "sceneGraphNode.h"


/////////////////
// Constructor //
/////////////////
sceneGraphNode::sceneGraphNode(void)
{
  // Do Nothing
}


sceneGraphNode::sceneGraphNode(const transformation3d& t)
{
  _transformation = t;
}


sceneGraphNode::sceneGraphNode(const sceneGraphNode& node)
{
  // copy transformation
  _transformation = node._transformation;

  // copy children 
  _children = node._children;

  // Done.
}



///////////////
// Operators //
///////////////
sceneGraphNode& sceneGraphNode::operator=(const sceneGraphNode& node)
{
  _assign(node);
  return *this;
}



/////////////
// Methods //
/////////////
boundingBox sceneGraphNode::returnBoundingBox(void) const
{
  boundingBox bb;

  // get the bounding box of all the children, transform it (approximation!) and merge
  for(std::vector<const sceneGraph_base*>::const_iterator itr = _children.begin(); itr != _children.end(); itr++)
  {
    // get untransformed bounding box
    boundingBox child_bb = (*itr)->returnBoundingBox();
    
    // get all 8 corners
    std::vector<vec3d> corners;
    corners.push_back( child_bb.leftTopFront() );
    corners.push_back( child_bb.rightBottomBack() );
    corners.push_back( vec3d( corners[0].x, corners[0].y, corners[1].z ));
    corners.push_back( vec3d( corners[0].x, corners[1].y, corners[0].z ));
    corners.push_back( vec3d( corners[0].x, corners[1].y, corners[1].z ));
    corners.push_back( vec3d( corners[1].x, corners[0].y, corners[0].z ));
    corners.push_back( vec3d( corners[1].x, corners[0].y, corners[1].z ));
    corners.push_back( vec3d( corners[1].x, corners[1].y, corners[0].z ));

    // transform and add
    for(unsigned int i=0; i < corners.size(); i++)
      bb.expand( _transformation.transformPoint(corners[i]) );
  }

  // Done.
  return bb;
}


bool sceneGraphNode::isHit(const ray& r) const
{
  // HW4: implement this.
  //      return: true or false if any object in the scene graph node is hit by the ray r.
  //      modifies: nothing
  boundingBox bb;
	ray tempR = r;
	tempR.inverseTransform(_transformation);
  
  for(unsigned int i=0; i < _children.size(); i++)
  {
  	 bb = _children[i]->returnBoundingBox();
  	 if(!bb.isHit(tempR)){
  	 	return false;
  	 }
 		 if(_children[i]->isHit(tempR))
 		 	return true;	
	}
	return false;
}


intersectionPoint sceneGraphNode::intersect(const ray& r) const
{
  // HW4: implement this.
  //      return: the intersectionPoint of any object in the scene graph node that is closes to the origin of the ray r.
  //      modifies: nothing
	ray tempR = r;
	tempR.inverseTransform(_transformation);
	intersectionPoint ip;
	/*
  if(isHit(tempR) == false){
  		return intersectionPoint();
	}*/
	for(unsigned int i=0; i < _children.size(); i++){
		intersectionPoint tempIP = _children[i]->intersect(tempR);
		if(tempIP < ip)
			ip = tempIP;
	}
  
  ip.transform(_transformation);
  return ip;
}


void sceneGraphNode::addChildNode(const sceneGraph_base& node)
{
  // add to _children
  _children.push_back(&node);
}



///////////////////////
// Protected Methods //
///////////////////////
void sceneGraphNode::_assign(const sceneGraphNode& node)
{
  // test for trivial case
  if(&node == this) return;

  // create copy & swap
  sceneGraphNode copy(node);
  _swap(copy);

  // Done.
}


void sceneGraphNode::_swap(sceneGraphNode& swp)
{
  std::swap(_transformation, swp._transformation);
  std::swap(_children, swp._children);
}


void sceneGraphNode::_print(std::ostream& s) const
{
  s << "SceneGraphNode: " << _children.size() << " nodes, tranform = " << _transformation;
}


