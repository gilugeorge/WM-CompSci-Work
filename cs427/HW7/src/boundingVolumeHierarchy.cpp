#include "boundingVolumeElement.h"
#include "boundingVolumeHierarchy.h"

//////////////////
// Constructors //
//////////////////
boundingVolumeHierarchy::boundingVolumeHierarchy(const triangleMesh& mesh)
{
  // Init
  _root = NULL;
  _mesh = &mesh;
  const std::vector<triangle>& triangleList = mesh.triangles();

  // 1) create a list of pointers to the triangles
  std::vector<const triangle*> trianglePointerList;
  for(unsigned int i=0; i < triangleList.size(); i++)
    trianglePointerList.push_back(&(triangleList[i]));

  // 2) create the hierarchy
  _root = new boundingVolumeElement(trianglePointerList, 0, trianglePointerList.size() - 1);

  // Done.
}



////////////////
// Destructor //
////////////////
boundingVolumeHierarchy::~boundingVolumeHierarchy(void)
{
  if(_root != NULL) delete _root;
}



/////////////
// Methods //
/////////////
bool boundingVolumeHierarchy::isHit(const ray& r) const
{
  return _root->isBoundingBoxHit(r) && _root->isHit(r);
}


intersectionPoint boundingVolumeHierarchy::intersect(const ray& r) const
{
  if(_root->isBoundingBoxHit(r)) return _root->intersect(r, *_mesh);
  else return intersectionPoint();
}


