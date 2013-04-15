#include "sceneGraphObject.h"

/////////////////
// Constructor //
/////////////////
sceneGraphObject::sceneGraphObject(const triangleMesh& t)
{
  // create instance:
  // copy pointer, but do not clone object
  _mesh = &t;
  _bvh = NULL;
}


sceneGraphObject::sceneGraphObject(const triangleMesh& t, const boundingVolumeHierarchy& bvh)
{
  // create instance:
  // copy pointer, but do not clone object
  _mesh = &t;
  _bvh = &bvh;
}


sceneGraphObject::sceneGraphObject(const sceneGraphObject& node)
{
  // copy instance:
  // copy pointer, but do not clone object
  _mesh = node._mesh;
  _bvh = node._bvh;
}



//////////////
// Operator //
//////////////
sceneGraphObject& sceneGraphObject::operator=(const sceneGraphObject& node)
{
  _assign(node);
  return *this;
}



/////////////
// Methods //
/////////////
boundingBox sceneGraphObject::returnBoundingBox(void) const
{
  return _mesh->getBoundingBox();
}


bool sceneGraphObject::isHit(const ray& r) const
{
  // check if there exists an bvh?
  if(_bvh == NULL)
    // if none, intersect the triangle mesh
    return _mesh->isHit(r);
  else
    // if exists, intersect via the bvh
    return _bvh->isHit(r);
}


intersectionPoint sceneGraphObject::intersect(const ray& r) const
{
  // check if there exists an bvh?
  if(_bvh == NULL)
    // if none, intersect the triangle mesh
    return _mesh->intersect(r);
  else
    // if exists, intersect via the bvh
    return _bvh->intersect(r);
}



///////////////////////
// Protected Methods //
///////////////////////
void sceneGraphObject::_assign(const sceneGraphObject& node)
{
  // copy
  _mesh = node._mesh;
  _bvh = node._bvh;

  // Done.
}


void sceneGraphObject::_swap(sceneGraphObject& swp)
{
  std::swap(_mesh, swp._mesh);
  std::swap(_bvh, swp._bvh);
}


void sceneGraphObject::_print(std::ostream& s) const
{
  s << "SceneGraphObject: " << *_mesh;
  if(_bvh != NULL) s << ", with bvh";
}
