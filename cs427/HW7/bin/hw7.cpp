#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "timer.h"
#include "scene.h"
#include "raytrace.h"
#include "geometry.h"

void renderSphere(unsigned int sceneNumber, unsigned int segments)
{
  std::cout << "Scene " << sceneNumber << ": sphere with " << segments << " segments." << std::endl;

  // create a simple scene
  // - single light source
  // - sphere at center (grey diffuse, with white phong 32)
  timer t;
  scene s;

  // create material
  const brdf_base& diff = s.addDiffuseBrdf();
  const brdf_base& ph32 = s.addPhongBrdf(32.0f);
  const albedo_base& white = s.addConstantAlbedo( color(1.0f, 1.0f, 1.0f) );
  const material& mat = s.addMaterial(white, diff, white, ph32);

  // create geometry
  std::vector<triangle> sphere = createSphere( vec3d(0.0f, 0.0f, 0.0f), 1.0f, segments, segments );
  const sceneGraph_base& obj = s.addSceneGraphObject(sphere, mat, true);
  s.setSceneGraphRoot(obj);

  // create camnera
  s.autoSetCamera(512, 512, 35.0f * M_PI / 180.0f);

  // create light source
  s.addDirectionalLightSource( s.getCamera().view() - s.getCamera().up(), color(1.0f, 1.0f, 1.0f) );


  std::cout << " - Construction time: " << t.seconds() << " seconds." << std::endl;

  t.restart();
  image result = raytrace(s, 1, 1);

  std::cout << " - Rendering time: " << t.seconds() <<  " seconds." << std::endl;

  // Done.
  char filename[255];
  sprintf(filename, "hw7-result%d.ppm", sceneNumber);
  result.save(filename);
}


void renderObj(unsigned int sceneNumber, const std::string& objname)
{
  std::cout << "Scene " << sceneNumber << ": OBJ file: " << objname << std::endl;

  // create a simple scene
  // - single light source
  // - sphere at center (grey diffuse, with white phong 32)
  timer t;
  scene s;

  // create material
  const brdf_base& diff = s.addDiffuseBrdf();
  const brdf_base& ph32 = s.addPhongBrdf(32.0f);
  const albedo_base& white = s.addConstantAlbedo( color(1.0f, 1.0f, 1.0f) );
  const material& mat = s.addMaterial(white, diff, white, ph32);

  // create geometry
  const sceneGraph_base& obj = s.addSceneGraphObject(objname, mat, true);
  s.setSceneGraphRoot(obj);

  // create camnera
  s.autoSetCamera(512, 512, 35.0f * M_PI / 180.0f);

  // create light source
  s.addDirectionalLightSource( s.getCamera().view() - s.getCamera().up(), color(1.0f, 1.0f, 1.0f) );

  std::cout << " - Construction time: " << t.seconds() << " seconds." << std::endl;

  t.restart();
  image result = raytrace(s, 1, 1);

  std::cout << " - Rendering time: " << t.seconds() <<  " seconds." << std::endl;

  // Done.
  char filename[255];
  sprintf(filename, "hw7-result%d.ppm", sceneNumber);
  result.save(filename);
}


int main(int argc, char** argv)
{
  // parse command
  unsigned int pos = 1;
  unsigned int mask = (argc >= 2) ? 0 : 0xFFFF;
  while(pos < argc)
  {
    unsigned int sceneNumber = atoi(argv[pos++]);
    mask |= 1 << sceneNumber;
  }

  ////////////////////////////////////////

  if((mask & 2) != 0) renderObj(1, "data/cube.obj");
  if((mask & 4) != 0) renderSphere(2, 16);
  if((mask & 8) != 0) renderSphere(3, 32);
  if((mask & 16) != 0) renderObj(4, "data/teapot.obj");
  if((mask & 32) != 0) renderObj(5, "data/bunny.obj");
  if((mask & 64) != 0) renderObj(6, "data/dragon.obj");
  if((mask & 128) != 0) renderObj(7, "data/buddha.obj");
  if((mask & 256) != 0) renderObj(8, "data/angel.obj");


  ////////////////////////////////////////

  // Done.
  return 0;
}
