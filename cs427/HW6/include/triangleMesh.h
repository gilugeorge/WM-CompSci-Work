#ifndef _TRIANGLEMESH_H_
#define _TRIANGLEMESH_H_

#include <string>
#include <vector>
#include <ostream>

#include "ray.h"
#include "triangle.h"
#include "material.h"
#include "boundingbox.h"
#include "transformation3d.h"
#include "intersectionPoint.h"
#include "textureProjection_base.h"

class triangleMesh {
 public:
  //////////////////
  // Constructors //
  //////////////////
  triangleMesh(const material& m);
  triangleMesh(const std::vector<triangle>& ts, const material& m);
  triangleMesh(const std::string& filename, const material& m);
  triangleMesh(const triangleMesh& tm);

  ///////////////
  // Operators //
  ///////////////
  triangleMesh& operator=(const triangleMesh& tm);
  
  ////////////////
  // Inspectors //
  ////////////////
  const std::vector<triangle>& triangles(void) const;
  const boundingBox& getBoundingBox(void) const;
  const material& getMaterial(void) const;

  //////////////
  // Mutators //
  //////////////
  void applyTextureProjection(const textureProjection_base& tp);

  /////////////
  // Methods //
  /////////////
  intersectionPoint intersect(const ray& r) const;
  bool isHit(const ray& r) const;

  /////////////
  // Friends //
  /////////////
  friend void swap(triangleMesh& a, triangleMesh& b) { a._swap(b); }
  
  friend std::ostream& operator<<(std::ostream& s, const triangleMesh& tm)
  {
    s << "Triangle mesh: " << tm._triangles.size() << " triangles, material = " << tm._material;
    return s;
  }

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _swap(triangleMesh& tm);
  void _assign(const triangleMesh& tm);
  void _importTriangles(const std::vector<triangle>& ts);
  void _importTriangles(const std::string& filename);

  //////////////////////////
  // Private Data Members //
  //////////////////////////
  boundingBox           _boundingBox;
  material              _material;
  std::vector<triangle> _triangles;
};

#endif /* _TRIANGLEMESH_H_ */
