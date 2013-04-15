#ifndef _SCENEGRAPHOBJECT_H_
#define _SCENEGRAPHOBJECT_H_

#include "triangleMesh.h"
#include "sceneGraph_base.h"
#include "boundingVolumeHierarchy.h"

class sceneGraphObject : public sceneGraph_base {
 public:
  /////////////////
  // Constructor //
  /////////////////
  sceneGraphObject(const triangleMesh& t);
  sceneGraphObject(const triangleMesh& t, const boundingVolumeHierarchy& bvh);
  sceneGraphObject(const sceneGraphObject& node);

  //////////////
  // Operator //
  //////////////
  sceneGraphObject& operator=(const sceneGraphObject& node);

  /////////////
  // Methods //
  /////////////
  virtual boundingBox returnBoundingBox(void) const;
  virtual bool isHit(const ray& r) const;
  virtual intersectionPoint intersect(const ray& r) const;


  /////////////
  // Friends //
  /////////////
  friend void swap(sceneGraphObject& a, sceneGraphObject& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const sceneGraphObject& sg)
  {
    sg._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  void _assign(const sceneGraphObject& node); 
  void _swap(sceneGraphObject& swp);

  virtual void _print(std::ostream& s) const;

  ////////////////////////////
  // Protected Data Members //
  ////////////////////////////
  const triangleMesh* _mesh;
  const boundingVolumeHierarchy* _bvh;
};

#endif /* _SCENEGRAPHNODE_H_ */
