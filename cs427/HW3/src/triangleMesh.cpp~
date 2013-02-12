#include "constants.h"
#include "triangleMesh.h"
#include "obj.h"

//////////////////
// Constructors //
//////////////////
triangleMesh::triangleMesh(const material& m)
{
  _material = m;
}


triangleMesh::triangleMesh(const std::vector<triangle>& ts, const material& m)
{
  _material = m;
  _importTriangles(ts);
}


triangleMesh::triangleMesh(const std::string& filename, const material& m)
{
  _material = m;
  _importTriangles(filename);
}


triangleMesh::triangleMesh(const triangleMesh& tm)
{
  _material = tm._material;
  _triangles = tm._triangles;
  _boundingBox = tm._boundingBox;
}



///////////////
// Operators //
///////////////
triangleMesh& triangleMesh::operator=(const triangleMesh& tm)
{
  _assign(tm);
  return *this;
}


  
////////////////
// Inspectors //
////////////////
const std::vector<triangle>& triangleMesh::triangles(void) const
{
  return _triangles;
}


const boundingBox& triangleMesh::getBoundingBox(void) const
{
  return _boundingBox;
}


const material& triangleMesh::getMaterial(void) const
{
  return _material;
}


//////////////
// Mutators //
//////////////
void triangleMesh::applyTextureProjection(const textureProjection_base& tp)
{
  // for every triangle => apply projection
  for(std::vector<triangle>::iterator itr = _triangles.begin(); itr != _triangles.end(); itr++)
    tp.apply(*itr);

  // Done.
}


/////////////
// Methods //
/////////////
bool triangleMesh::isHit(const ray& r) const
{
  // check bounding box, and bail if not hit
  if(!_boundingBox.isHit(r)) return false;
  
  // for every triangle
  for(std::vector<triangle>::const_iterator itr = _triangles.begin(); itr != _triangles.end(); itr++)
  {
    // hit?
    float t;
    vec3d barycentric;
    if(itr->intersect(r, barycentric, t)) return true;
  }

  // Done.
  return false;
}


intersectionPoint triangleMesh::intersect(const ray& r) const
{
  // HW3: Implement this
  //      Input: a ray
  //      Modifies: nothing
  //      Returns: The intersection point with the ray r and the triangle mesh which is closest to the origin of the ray.
  //               If no intersection point is found, return an empty intersectionPoint (i.e., construct without parameters)
  // check bounding box, and bail if not hit
  int closest_triangle = -1;
  float closest_t = 10000000;
	vec3d closest_barycentric;
  if(!_boundingBox.isHit(r)) return intersectionPoint();
  
  // for every triangle
  int counter = 0;
  for(std::vector<triangle>::const_iterator itr = _triangles.begin(); itr != _triangles.end(); itr++)
  {
    // hit?
    float t;
	  vec3d barycentric;
    if(itr->intersect(r, barycentric, t)){
    	if(t < closest_t){
    		closest_t = t;
    		closest_triangle = counter;
    		closest_barycentric = barycentric;
    	}
    }
    counter++;		
  }
  
	if(closest_triangle != -1){
		return intersectionPoint(r, closest_barycentric, closest_t, _triangles[closest_triangle], getMaterial());
	}
  
  return intersectionPoint();
}

 

/////////////////////
// Private Methods //
/////////////////////
void triangleMesh::_swap(triangleMesh& tm)
{
  std::swap(_material, tm._material);
  std::swap(_boundingBox, tm._boundingBox);
  std::swap(_triangles, tm._triangles);
}


void triangleMesh::_assign(const triangleMesh& tm)
{
  // check for trivial case: self-assignment
  if(&tm == this) return;

  // create copy & swap
  triangleMesh copy(tm);
  _swap(copy);

  // Done.
}


void triangleMesh::_importTriangles(const std::vector<triangle>& ts)
{
  // add triangles one by one
  for(std::vector<triangle>::const_iterator itr = ts.begin(); itr != ts.end(); itr++)
  {
    // add
    _triangles.push_back(*itr);

    // expand bounding box
    for(unsigned int i=0; i < 3; i++)
      _boundingBox.expand( itr->vertex(i), EPSILON );
  }

  // Done.
}


void triangleMesh::_importTriangles(const std::string& filename)
{
  // Read an OBJ file.
  obj o(filename);

  // Copy in triangle mesh
  vec3d vertex[3], normal[3];
  vec2d texCoord[2];

  for(unsigned int p=0; p < o.numberOfPolygons(); p++)
  {
    // Convert every polygon to a triangle collection
    // 1) get triangle determined by first three vertices
    for(unsigned int t=0; t < 3; t++)
    {
      vertex[t] = o.vertex(p, t);
      normal[t] = o.normal(p, t);
      texCoord[t] = o.textureCoord(p, t);
    }
    _triangles.push_back( triangle(vertex[0], vertex[1], vertex[2], normal[0], normal[1], normal[2], texCoord[0], texCoord[1], texCoord[2]) );

    // expand bounding box
    for(unsigned int i=0; i < 3; i++)
      _boundingBox.expand( vertex[i], EPSILON );

    // 2) get triangles determined by 0th, t-1, t vertex
    for(unsigned int t=3; t < o.numberOfPolygonVertices(p); t++)
    {
      vertex[1] = vertex[2];      vertex[2] = o.vertex(p,t);
      normal[1] = normal[2];      normal[2] = o.normal(p,t);
      texCoord[1] = texCoord[2];  texCoord[2] = o.textureCoord(p,t);
      _triangles.push_back( triangle(vertex[0], vertex[1], vertex[2], normal[0], normal[1], normal[2], texCoord[0], texCoord[1], texCoord[2]) );
      _boundingBox.expand( vertex[2], EPSILON );
    }
  }

  // Done.
}

