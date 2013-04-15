#include <iostream>
#include <fstream>

#include "obj.h"
#include "customException.h"


/////////////////
// Constructor //
/////////////////
obj::obj(const std::string& filename)
{
  _load(filename);
}


obj::obj(const obj& o)
{
  _vertexList = o._vertexList;
  _normalList = o._normalList;
  _textureCoordList = o._textureCoordList;
  _polygonList = o._polygonList;
}



//////////////
// Operator //
//////////////
obj obj::operator=(const obj& o)
{
  _assign(o);
  return *this;
}



/////////////
// Methods //
/////////////
unsigned int obj::numberOfPolygons(void) const
{
  return _polygonList.size();
}


unsigned int obj::numberOfPolygonVertices(unsigned int poly) const
{
  assert(poly < numberOfPolygons());
  return _polygonList[poly].size();
}


const vec3d& obj::vertex(unsigned int poly, unsigned int vert) const
{
  // sanity check
  assert(poly < numberOfPolygons());
  assert(vert < _polygonList[poly].size());

  // get vertex index
  unsigned int vertexIndex = _polygonList[poly].vertexIndex(vert);

  // sanity check
  assert(vertexIndex < _vertexList.size());
  
  // Done.
  return _vertexList[vertexIndex];
}


vec3d obj::normal(unsigned int poly, unsigned int vert) const
{
  // sanity check
  assert(poly < numberOfPolygons());
  assert(vert < _polygonList[poly].size());

  // check if polygon has normal information
  if(_polygonList[poly].hasNormals())
  {
    // get normal index
    unsigned int normalIndex = _polygonList[poly].normalIndex(vert);

    // sanity check
    assert(normalIndex < _normalList.size());

    // return poly normal
    return _normalList[normalIndex];
  }

  else {
    // no normal stored => compute polygon normal
    vec3d v0 = (vertex(poly, 0) - vertex(poly, 1)).normalize();
    vec3d v1 = (vertex(poly, 2) - vertex(poly, 1)).normalize();
    
    return v1.cross(v0);
  }

  // Done.
}


vec2d obj::textureCoord(unsigned int poly, unsigned int vert) const
{
  // sanity check
  assert(poly < numberOfPolygons());
  assert(vert < _polygonList[poly].size());

  // check if polygon has texture coordinate information
  if(_polygonList[poly].hasTextureCoordinates())
  {
    // get textureCoord index
    unsigned int textureIndex = _polygonList[poly].textureCoordIndex(vert);

    // sanity check
    assert(textureIndex < _textureCoordList.size());

    // return poly normal
    return _textureCoordList[textureIndex];
  }

  else {
    // no texture coordinate stored => return (0,0)
    return vec2d(0.0f, 0.0f);
  }

  // Done.
}



/////////////////////
// Private Methods //
/////////////////////
void obj::_assign(const obj& o)
{
  // sanity check
  if(&o == this) return;

  // copy
  obj temp(o);
  _swap(temp);

  // Done.
}


void obj::_swap(obj& o)
{
  std::swap(_polygonList, o._polygonList);
}


void obj::_load(const std::string& filename)
{
  // open obj file
  std::ifstream ifs(filename.c_str());
  if(!ifs.is_open()) throw customException(filename + ": unable to open for reading.");

  // read line by line
  unsigned char key;
  while(ifs.good())
  {
    // get key
    key = ifs.get();

    // COMMENTS:
    if(key == '#' || key == ' ') 
    {
      std::string comment;
      ifs >> comment;  // comment: skip line
    }

    // VERTEX DATA:
    else if(key == 'v')
    {
      // get vertex data
      key = ifs.get();

      // Vertex Coordinate
      if(key == ' ') 
      {
	vec3d v;
	ifs >> v.x >> v.y >> v.z;
	_vertexList.push_back(v);
      }

      // Texture Coordinate
      else if(key == 't')
      {
	vec2d t;
	ifs >> t.u >> t.v;
	_textureCoordList.push_back(t);
      }

      // Normal
      else if(key == 'n')  
      {
	vec3d n;
	ifs >> n.x >> n.y >> n.z;
	_normalList.push_back(n);
      }

      // Unknown => ERROR
      else 
      {
	char msg[256];
	sprintf(msg, "Unknown vertex key: v%c.", key);
	throw customException(msg);
      }
    }

    // POLYGON:
    else if(key == 'f')
    {
      detail::polygon poly;

      // get polygon data
      // can be either: 
      // 1)  v0 v1 .. vn
      // 2)  v0//n0 v1//n1 .. vn//nn
      // 3)  v0/t0 v1/t1 ... vn/tn
      // 4)  v0/t0/n0 ... vn/tn/nn
      bool done=false;
      while(!done)
      {
	// read entry
	signed int vi, vt=-1, vn=-1;
	ifs >> vi;
	unsigned char c = ifs.get();

	if(c == '/')
	{
	  c = ifs.get();
	  if(c != '/') { ifs.unget(); ifs >> vt; c = ifs.get(); }
	  if(c == '/') { ifs >> vn; }
	}

	// store in polygon
	if(vt != -1)
	  if(vn != -1) poly.addVNT(vi-1, vn-1, vt-1);
	  else poly.addVT(vi-1, vt-1);
	else if(vn != -1)
	  poly.addVN(vi-1, vn-1);
	else
	  poly.addV(vi-1);

	// check if we did not eat the end-of-line chararters
	ifs.unget();
	c = ifs.get();
	if(c == '\r' || c == '\n') done = true;

	// eat remaining spaces
	c  = ifs.get();
	while(c == ' ')
	  c = ifs.get();

	// check again for end
	if(c == '\r' || c == '\n') done = true;
	ifs.unget();
      }

      // store full polygon
      _polygonList.push_back(poly);
    }
  }

  // output statistics
  /*
  std::cout << filename << " contains:" << std::endl;
  std::cout << " - " << _polygonList.size() << " polygons" << std::endl;
  std::cout << " - " << _vertexList.size() << " vertices" << std::endl;
  std::cout << " - " << _normalList.size() << " normals" << std::endl;
  std::cout << " - " << _textureCoordList.size() << " texture coordinates" << std::endl;
  */

  // Done.
}

