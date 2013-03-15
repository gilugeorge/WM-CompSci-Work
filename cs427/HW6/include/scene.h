#ifndef _SCENE_H_
#define _SCENE_H_

#include <string>
#include <vector>
#include <ostream>

#include "ray.h"
#include "color.h"
#include "vec3d.h"
#include "camera.h"
#include "material.h"
#include "brdf_base.h"
#include "albedo_base.h"
#include "triangleMesh.h"
#include "environmentMap.h"
#include "sceneGraph_base.h"
#include "transformation3d.h"
#include "lightsource_base.h"
#include "intersectionPoint.h"

class scene {
 public:
  /////////////////
  // Constructor //
  /////////////////
  scene(void);

  ////////////////
  // Destructor //
  ////////////////
  ~scene(void);

  //////////////
  // Mutators //
  //////////////
  void setEnvironmentMap(const std::string& textureName, const transformation3d& transformation=transformation3d());

  void addDirectionalLightSource(const vec3d& direction, const color& intensity);
  void addPointLightSource(const vec3d& position, const color& intensity, const vec3d& attenuation);
  void addSpotLightSource(const vec3d& position, const color& intensity, const vec3d& direction, float cutoffDegrees, float sharpness, const vec3d& attenuation);

  const brdf_base& addDiffuseBrdf(void);
  const brdf_base& addPhongBrdf(float sharpness);

  const albedo_base& addConstantAlbedo(const color& col);
  const albedo_base& addTexturedAlbedo(const std::string& textureName);
  const albedo_base& addBilinearTexturedAlbedo(const std::string& textureName);

  const material& addMaterial(const albedo_base& albedo, const brdf_base& brdf);
  const material& addMaterial(const albedo_base& albedo1, const brdf_base& brdf1, const albedo_base& albedo2, const brdf_base& brdf2);

  const sceneGraph_base& addSceneGraphObject(const std::vector<triangle>& triangles, const material& mat);
  const sceneGraph_base& addSceneGraphObject(const std::string& filename, const material& mat);
  const sceneGraph_base& addSceneGraphNode(const transformation3d& transformation, const sceneGraph_base& child);
  const sceneGraph_base& addSceneGraphNode(const transformation3d& transformation, const std::vector<const sceneGraph_base*>& children);
  void setSceneGraphRoot(const sceneGraph_base& root);

  void setCamera(const camera& cam);
  void autoSetCamera(unsigned int resx, unsigned int resy, float fov, float coverage=0.9f);

  /////////////
  // Methods //
  /////////////
  bool isHit(const ray& r) const;
  intersectionPoint intersect(const ray& r) const;

  unsigned int numberOfLightSources(void) const;
  const lightsource_base& lightSource(unsigned int index) const;

  bool hasEnvironmentMap(void) const;
  const environmentMap& getEnvironmentMap(void) const;

  const camera& getCamera(void) const;

  /////////////
  // Friends //
  /////////////
  friend std::ostream& operator<<(std::ostream& s, const scene& sc)
  {
    s << "Scene: " << sc.getCamera() << ". ";
    if(sc.numberOfLightSources() != 0) s << "No Light Sources. "; 
    else {
      s << sc.numberOfLightSources() << " lightsources: ";
      for(unsigned int i=0; i < sc.numberOfLightSources() - 1; i++)
	s << sc.lightSource(i) << ", ";
      s << sc.lightSource(sc.numberOfLightSources() - 1) << ". ";
    }

    if(sc.hasEnvironmentMap()) s << sc.getEnvironmentMap() << ". ";
    else s << "No Environment Map. ";

    s << "Scene Graph: " << *sc._root;

    // Done.
    return s;
  }

 private:
  //////////////////////////
  // Private Data Members //
  //////////////////////////
  environmentMap* _environmentMap;
  const sceneGraph_base* _root;
  camera _camera;
  std::vector<lightsource_base*> _lightsource;
  std::vector<material*> _material;
  std::vector<brdf_base*> _brdf;
  std::vector<albedo_base*> _albedo;
  std::vector<sceneGraph_base*> _nodes;
  std::vector<triangleMesh*> _mesh;
};

#endif /* _SCENE_H_ */

