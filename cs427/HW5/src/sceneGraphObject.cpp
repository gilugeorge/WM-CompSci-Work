#include "sceneGraphObject.h"

/////////////////
// Constructor //
/////////////////
sceneGraphObject::sceneGraphObject(const triangleMesh& t)
{
  // create instance:
  // copy pointer, but do not clone object
  _mesh = &t;
}


sceneGraphObject::sceneGraphObject(const sceneGraphObject& node)
{
  // copy instance:
  // copy pointer, but do not clone object
  _mesh = node._mesh;
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
  // intersect the triangle mesh
  return _mesh->isHit(r);
}


intersectionPoint sceneGraphObject::intersect(const ray& r) const
{
  // intersect the triangle mesh
  return _mesh->intersect(r);
}



///////////////////////
// Protected Methods //
///////////////////////
void sceneGraphObject::_assign(const sceneGraphObject& node)
{
  // copy
  _mesh = node._mesh;

  // Done.
}


void sceneGraphObject::_swap(sceneGraphObject& swp)
{
  std::swap(_mesh, swp._mesh);
}


void sceneGraphObject::_print(std::ostream& s) const
{
  s << "SceneGraphObject: " << *_mesh;
}
