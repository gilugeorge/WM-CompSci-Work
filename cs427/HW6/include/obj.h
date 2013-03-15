#ifndef _OBJ_H_
#define _OBJ_H_

#include <string>
#include <vector>
#include <cassert>

#include "vec3d.h"
#include "vec2d.h"
#include "obj.detail.h"

class obj {
 public:
  /////////////////
  // Constructor //
  /////////////////
  obj(const std::string& filename);
  obj(const obj& o);

  //////////////
  // Operator //
  //////////////
  obj operator=(const obj& o);

  /////////////
  // Methods //
  /////////////
  unsigned int numberOfPolygons(void) const;
  unsigned int numberOfPolygonVertices(unsigned int poly) const;
  const vec3d& vertex(unsigned int poly, unsigned int vert) const;
  vec3d normal(unsigned int poly, unsigned int vert) const;
  vec2d textureCoord(unsigned int poly, unsigned int vert) const;

 private:
  /////////////////////
  // Private Methods //
  /////////////////////
  void _assign(const obj& o);
  void _swap(obj& o);
  void _load(const std::string& filename);

  //////////////////
  // Private Data //
  //////////////////
  std::vector<vec3d> _vertexList;
  std::vector<vec3d> _normalList;
  std::vector<vec2d> _textureCoordList;
  std::vector<detail::polygon> _polygonList;
};

#endif /* _OBJ_H_ */
