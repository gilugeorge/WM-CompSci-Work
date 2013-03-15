#include <cassert>

#include "scene.h"
#include "phong.h"
#include "diffuse.h"
#include "sceneGraphNode.h"
#include "constantAlbedo.h"
#include "texturedAlbedo.h"
#include "spotLightsource.h"
#include "pointLightsource.h"
#include "sceneGraphObject.h"
#include "bilinearTexturedAlbedo.h"
#include "directionalLightsource.h"

/////////////////
// Constructor //
/////////////////
scene::scene(void)
{
  _environmentMap = NULL;
  _root = NULL;
}



////////////////
// Destructor //
////////////////
scene::~scene(void)
{
  if(_environmentMap) delete _environmentMap;
  for(unsigned int i=0; i < _lightsource.size(); i++) if(_lightsource[i]) delete _lightsource[i];
  for(unsigned int i=0; i < _material.size(); i++)    if(_material[i])    delete _material[i];
  for(unsigned int i=0; i < _brdf.size(); i++)        if(_brdf[i])        delete _brdf[i];
  for(unsigned int i=0; i < _albedo.size(); i++)      if(_albedo[i])      delete _albedo[i];
  for(unsigned int i=0; i < _nodes.size(); i++)       if(_nodes[i])       delete _nodes[i];
  for(unsigned int i=0; i < _mesh.size(); i++)        if(_mesh[i])        delete _mesh[i];
}


//////////////
// Mutators //
//////////////
void scene::setEnvironmentMap(const std::string& textureName, const transformation3d& transformation)
{
  if(_environmentMap) delete _environmentMap;
  _environmentMap = new environmentMap(textureName, transformation);
}


void scene::addDirectionalLightSource(const vec3d& direction, const color& intensity)
{
  _lightsource.push_back(new directionalLightsource(intensity, direction));
}


void scene::addPointLightSource(const vec3d& position, const color& intensity, const vec3d& attenuation)
{
  _lightsource.push_back(new pointLightsource(position, intensity, attenuation));
}


void scene::addSpotLightSource(const vec3d& position, const color& intensity, const vec3d& direction, float cutoffDegrees, float sharpness, const vec3d& attenuation)
{
  _lightsource.push_back(new spotLightsource(position, intensity, direction, cutoffDegrees, sharpness, attenuation));
}


const brdf_base& scene::addDiffuseBrdf(void)
{
  _brdf.push_back(new diffuse());
  return *(_brdf.back());
}


const brdf_base& scene::addPhongBrdf(float sharpness)
{
  _brdf.push_back(new phong(sharpness));
  return *(_brdf.back());
}


const albedo_base& scene::addConstantAlbedo(const color& col)
{
  _albedo.push_back(new constantAlbedo(col));
  return *(_albedo.back());
}


const albedo_base& scene::addTexturedAlbedo(const std::string& textureName)
{
  _albedo.push_back(new texturedAlbedo(textureName));
  return *(_albedo.back());
}


const albedo_base& scene::addBilinearTexturedAlbedo(const std::string& textureName)
{
  _albedo.push_back(new bilinearTexturedAlbedo(textureName));
  return *(_albedo.back());
}


const material& scene::addMaterial(const albedo_base& albedo, const brdf_base& brdf)
{
  _material.push_back(new material());
  _material.back()->addComponent( reflectanceComponent(&albedo, &brdf) );
  return *(_material.back());
}


const material& scene::addMaterial(const albedo_base& albedo1, const brdf_base& brdf1, const albedo_base& albedo2, const brdf_base& brdf2)
{
  _material.push_back(new material());
  _material.back()->addComponent( reflectanceComponent(&albedo1, &brdf1) );
  _material.back()->addComponent( reflectanceComponent(&albedo2, &brdf2) );
  return *(_material.back());
}


const sceneGraph_base& scene::addSceneGraphObject(const std::vector<triangle>& triangles, const material& mat)
{
  // create mesh
  _mesh.push_back(new triangleMesh(triangles, mat));

  // add to node
  _nodes.push_back(new sceneGraphObject(*(_mesh.back())));
  return *(_nodes.back());
}


const sceneGraph_base& scene::addSceneGraphObject(const std::string& filename, const material& mat)
{
  // create mesh
  _mesh.push_back(new triangleMesh(filename, mat));

  // add to node
  _nodes.push_back(new sceneGraphObject(*(_mesh.back())));
  return *(_nodes.back());
}


const sceneGraph_base& scene::addSceneGraphNode(const transformation3d& transformation, const sceneGraph_base& child)
{
  // create
  sceneGraphNode *node = new sceneGraphNode(transformation);

  // add child
  node->addChildNode(child);

  // store
  _nodes.push_back(node);

  return *node;
}


const sceneGraph_base& scene::addSceneGraphNode(const transformation3d& transformation, const std::vector<const sceneGraph_base*>& children)
{
  // create
  sceneGraphNode *node = new sceneGraphNode(transformation);

  // add children
  for(unsigned int i=0; i < children.size(); i++)
    node->addChildNode(*(children[i]));

  // store
  _nodes.push_back(node);

  return *node;
}


void scene::setSceneGraphRoot(const sceneGraph_base& root)
{
  _root = &root;
}


void scene::setCamera(const camera& cam)
{
  _camera = cam;
}


void scene::autoSetCamera(unsigned int resx, unsigned int resy, float fov, float coverage)
{
  // sanity check: scene graph is present
  assert(_root != NULL);

  // 1) get bounding box
  boundingBox bb = _root->returnBoundingBox();

  // 2) compute center, eye, and up
  vec3d center = 0.5f * (bb.leftTopFront() + bb.rightBottomBack());

  vec3d size = bb.size();
  unsigned long maxAxis=0, minAxis = 1;
  for(unsigned int i=0; i < 3; i++)
  {
    if(size[maxAxis] < size[i]) maxAxis = i;
    if(size[minAxis] > size[i]) minAxis = i;
  }

  vec3d up; up[maxAxis] = 1.0f;

  vec3d eye(center);
  eye[minAxis] += coverage * size[maxAxis] / tan(fov);

  vec3d viewDir; viewDir[minAxis] = -1.0f;

  // 3) create camera
  _camera = camera(eye, viewDir, up, fov, resx, resy);

  // Done.
}



/////////////
// Methods //
/////////////
bool scene::isHit(const ray& r) const
{
  // sanity check
  if(_root == NULL) return false;
  
  // check for hit
  return _root->isHit(r);
}


intersectionPoint scene::intersect(const ray& r) const
{
  // sanity check
  if(_root == NULL) return intersectionPoint();

  // intersect
  return _root->intersect(r);
}


unsigned int scene::numberOfLightSources(void) const
{
  return _lightsource.size();
}


const lightsource_base& scene::lightSource(unsigned int index) const
{
  // sanity check
  assert(index < numberOfLightSources());
  
  // Done.
  return *(_lightsource[index]);
}


bool scene::hasEnvironmentMap(void) const
{
  return _environmentMap != NULL;
}


const environmentMap& scene::getEnvironmentMap(void) const
{
  // sanity check
  assert(hasEnvironmentMap());

  // Done.
  return *_environmentMap;
}


const camera& scene::getCamera(void) const
{
  return _camera;
}
