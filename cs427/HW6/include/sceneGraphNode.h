#ifndef _SCENEGRAPHNODE_H_
#define _SCENEGRAPHNODE_H_

#include <vector>

#include "triangleMesh.h"
#include "sceneGraph_base.h"
#include "sceneGraphObject.h"

class sceneGraphNode : public sceneGraph_base {
 public:
  /////////////////
  // Constructor //
  /////////////////
  sceneGraphNode(void);
  sceneGraphNode(const transformation3d& t);
  sceneGraphNode(const sceneGraphNode& node);

  //////////////
  // Operator //
  //////////////
  sceneGraphNode& operator=(const sceneGraphNode& node);

  /////////////
  // Methods //
  /////////////
  virtual boundingBox returnBoundingBox(void) const;
  virtual bool isHit(const ray& r) const;
  virtual intersectionPoint intersect(const ray& r) const;

  void addChildNode(const sceneGraph_base& node);

  /////////////
  // Friends //
  /////////////
  friend void swap(sceneGraphNode& a, sceneGraphNode& b) { a._swap(b); }

  friend std::ostream& operator<<(std::ostream& s, const sceneGraphNode& sg)
  {
    sg._print(s);
    return s;
  }

 protected:
  ///////////////////////
  // Protected Methods //
  ///////////////////////
  void _assign(const sceneGraphNode& node); 
  void _swap(sceneGraphNode& swp);

  virtual void _print(std::ostream& s) const;

  ////////////////////////////
  // Protected Data Members //
  ////////////////////////////
  transformation3d _transformation;
  std::vector<const sceneGraph_base*> _children;
};

#endif /* _SCENEGRAPHNODE_H_ */
