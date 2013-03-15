#include <cstdlib>
#include <iostream>

#include "scene.h"
#include "raytrace.h"
#include "geometry.h"
#include "translation3d.h"

///////////////////////////////////////////////////////////////////////////////

void renderScene1(void)
{
  std::cout << "Scene 1." << std::endl;
  
  //////////////// create simple scene ////////////////////
  //
  //  - single light source (directional, white)
  //  - sphere at the center (red diffuse, with white phong 32)
  //
  scene s;

  // create material
  const brdf_base& diff = s.addDiffuseBrdf();
  const brdf_base& ph32 = s.addPhongBrdf(32.0f);
  const albedo_base& red = s.addConstantAlbedo( color(1.0f, 0.0f, 0.0f) );
  const albedo_base& white = s.addConstantAlbedo( color(1.0f, 1.0f, 1.0f) );
  const material& mat = s.addMaterial(red, diff, white, ph32);

  // create geometry
  std::vector<triangle> sphere = createSphere( vec3d(0.0f, 0.0f, 0.0f), 1.0f, 16, 16 );
  const sceneGraph_base& obj = s.addSceneGraphObject(sphere, mat);
  s.setSceneGraphRoot(obj);
  
  // create light source
  s.addDirectionalLightSource( vec3d(0.0f, -1.0f, -1.0f), color(1.0f, 1.0f, 1.0f) );

  // create camnera
  s.setCamera( camera(vec3d(0.0f, 0.0f, 5.0f),
		      vec3d(0.0f, 0.0f, -1.0f),
		      vec3d(0.0f, 1.0f, 0.0f),
		      35.0f * M_PI / 180.0f,
		      512, 512 )
	       );

  ////////////// render & save ////////////////
  image result = raytrace(s, 1, 1);
  result.save("hw6-result1.ppm");

  // Done.
}

///////////////////////////////////////////////////////////////////////////////

void renderScene2(void)
{
  std::cout << "Scene 2." << std::endl;
  
  //////////////// create simple scene ////////////////////
  //
  //  - two light sources (directional, red & green)
  //  - sphere at the center (white diffuse, with white phong 32)
  //
  scene s;

  // create material
  const brdf_base& diff = s.addDiffuseBrdf();
  const brdf_base& ph32 = s.addPhongBrdf(32.0f);
  const albedo_base& white = s.addConstantAlbedo( color(1.0f, 1.0f, 1.0f) );
  const material& mat = s.addMaterial(white, diff, white, ph32);

  // create geometry
  std::vector<triangle> sphere = createSphere( vec3d(0.0f, 0.0f, 0.0f), 1.0f, 16, 16 );
  const sceneGraph_base& obj = s.addSceneGraphObject(sphere, mat);
  s.setSceneGraphRoot(obj);
  
  // create light source
  s.addDirectionalLightSource( vec3d(0.0f, -1.0f, -1.0f), color(1.0f, 0.0f, 0.0f) );
  s.addDirectionalLightSource( vec3d(0.0f, +1.0f, -1.0f), color(0.0f, 1.0f, 0.0f) );

  // create camnera
  s.setCamera( camera(vec3d(0.0f, 0.0f, 5.0f),
		      vec3d(0.0f, 0.0f, -1.0f),
		      vec3d(0.0f, 1.0f, 0.0f),
		      35.0f * M_PI / 180.0f,
		      512, 512 )
	       );

  ////////////// render & save ////////////////
  image result = raytrace(s, 1, 1);
  result.save("hw6-result2.ppm");

  // Done.
}

///////////////////////////////////////////////////////////////////////////////

void renderScene3(void)
{
  std::cout << "Scene 3." << std::endl;
  
  //////////////// create simple scene ////////////////////
  //
  //  - single light sources (frontal directional, white)
  //  - two planes translated left and right, one texture mapped, the other bilinearly texture mapped
  //
  scene s;

  // create material
  const brdf_base& diff = s.addDiffuseBrdf();
  const albedo_base& map = s.addTexturedAlbedo( "data/tiny_squares.ppm" );
  const albedo_base& bmap = s.addBilinearTexturedAlbedo( "data/tiny_squares.ppm" );
  const material& mat1 = s.addMaterial(map, diff);
  const material& mat2 = s.addMaterial(bmap, diff);

  // create geometry
  std::vector<triangle> plane = createPlane( vec3d(-1.0f, -1.0f, 0.0f), vec3d(0.0f, 2.0f, 0.0f), vec3d(2.0f, 0.0f, 0.0f) );
  const sceneGraph_base& obj1 = s.addSceneGraphObject(plane, mat1);
  const sceneGraph_base& obj2 = s.addSceneGraphObject(plane, mat2);
  const sceneGraph_base& left = s.addSceneGraphNode( translation3d( vec3d(-1.0f, 0.0f, 0.0f) ), obj1);
  const sceneGraph_base& right = s.addSceneGraphNode( translation3d( vec3d(+1.0f, 0.0f, 0.0f) ), obj2);

  std::vector<const sceneGraph_base*> nodes;
  nodes.push_back(&left);
  nodes.push_back(&right);
  const sceneGraph_base& root = s.addSceneGraphNode( transformation3d(), nodes );
  
  s.setSceneGraphRoot(root);
  
  // create light source
  s.addDirectionalLightSource( vec3d(0.0f, 0.0f, -1.0f), color(1.0f, 1.0f, 1.0f) );

  // create camnera
  s.setCamera( camera(vec3d(0.0f, 0.0f, 5.0f),
		      vec3d(0.0f, 0.0f, -1.0f),
		      vec3d(0.0f, 1.0f, 0.0f),
		      35.0f * M_PI / 180.0f,
		      512, 512 )
	       );

  ////////////// render & save ////////////////
  image result = raytrace(s, 1, 1);
  result.save("hw6-result3.ppm");

  // Done.
}

///////////////////////////////////////////////////////////////////////////////

void renderScene4(void)
{
  std::cout << "Scene 4." << std::endl;
  
  //////////////// create simple scene ////////////////////
  //
  //  - four light source (white, red, green, blue point light)
  //  - one planes (white diffuse, white phong 64);
  //
  scene s;

  // create material
  const brdf_base& diff = s.addDiffuseBrdf();
  const brdf_base& ph64 = s.addPhongBrdf(64.0f);
  const albedo_base& white = s.addConstantAlbedo( color(1.0f, 1.0f, 1.0f) );
  const albedo_base& grey = s.addConstantAlbedo( color(0.3f, 0.3f, 0.3f) );
  const material& mat = s.addMaterial(white, diff, grey, ph64);

  // create geometry
  std::vector<triangle> plane = createPlane( vec3d(-2.0f, -2.0f, 0.0f), vec3d(0.0f, 4.0f, 0.0f), vec3d(4.0f, 0.0f, 0.0f) );
  const sceneGraph_base& obj = s.addSceneGraphObject(plane, mat);
  s.setSceneGraphRoot(obj);
  
  // create light source
  s.addPointLightSource( vec3d(-2.0f, -2.0f, 2.0f), color(1.0f, 1.0f, 1.0f), vec3d(0.0f, 0.0f, 1.0f) );
  s.addPointLightSource( vec3d(+2.0f, -2.0f, 1.5f), color(0.0f, 0.0f, 1.0f), vec3d(0.0f, 0.0f, 1.0f) );
  s.addPointLightSource( vec3d(-2.0f, +2.0f, 1.0f), color(1.0f, 0.0f, 0.0f), vec3d(0.0f, 0.0f, 1.0f) );
  s.addPointLightSource( vec3d(+2.0f, +2.0f, 0.5f), color(0.0f, 1.0f, 0.0f), vec3d(0.0f, 0.0f, 1.0f) );

  // create camnera
  s.setCamera( camera(vec3d(0.0f, 0.0f, 5.0f),
		      vec3d(0.0f, 0.0f, -1.0f),
		      vec3d(0.0f, 1.0f, 0.0f),
		      35.0f * M_PI / 180.0f,
		      512, 512 )
	       );

  ////////////// render & save ////////////////
  image result = raytrace(s, 1, 1);
  result.save("hw6-result4.ppm");

  // Done.
}

///////////////////////////////////////////////////////////////////////////////

void renderScene5(void)
{
  std::cout << "Scene 5." << std::endl;
  
  //////////////// create simple scene ////////////////////
  //
  //  - three light source (white spot light)
  //  - one planes (blue diffuse, white phong 64);
  //
  scene s;

  // create material
  const brdf_base& diff = s.addDiffuseBrdf();
  const brdf_base& ph64 = s.addPhongBrdf(64.0f);
  const albedo_base& white = s.addConstantAlbedo( color(1.0f, 1.0f, 1.0f) );
  const albedo_base& blue = s.addConstantAlbedo( color(0.0f, 0.0f, 1.0f) );
  const material& mat = s.addMaterial(blue, diff, white, ph64);

  // create geometry
  std::vector<triangle> plane = createPlane( vec3d(-2.0f, -2.0f, 0.0f), vec3d(0.0f, 4.0f, 0.0f), vec3d(4.0f, 0.0f, 0.0f) );
  const sceneGraph_base& obj = s.addSceneGraphObject(plane, mat);
  s.setSceneGraphRoot(obj);
  
  // create light source
  s.addSpotLightSource( vec3d(-1.0f, 0.0f, 2.0f), color(3.0f, 3.0f, 3.0f), vec3d(0.0f, 0.0f, -1.0f), 30.0f, 1.0f, vec3d(0.0f, 0.0f, 1.0f) );
  s.addSpotLightSource( vec3d(+1.0f, +1.0f, 2.0f), color(3.0f, 3.0f, 3.0f), vec3d(0.0f, 0.0f, -1.0f), 15.0f, 1.0f, vec3d(0.0f, 0.0f, 1.0f) );
  s.addSpotLightSource( vec3d(+1.0f, -1.0f, 2.0f), color(3.0f, 3.0f, 3.0f), vec3d(0.0f, 0.0f, -1.0f), 15.0f, 100.0f, vec3d(0.0f, 0.0f, 1.0f) );

  // create camnera
  s.setCamera( camera(vec3d(0.0f, 0.0f, 5.0f),
		      vec3d(0.0f, 0.0f, -1.0f),
		      vec3d(0.0f, 1.0f, 0.0f),
		      35.0f * M_PI / 180.0f,
		      512, 512 )
	       );

  ////////////// render & save ////////////////
  image result = raytrace(s, 1, 1);
  result.save("hw6-result5.ppm");

  // Done.
}

///////////////////////////////////////////////////////////////////////////////

void renderScene6(void)
{
  std::cout << "Scene 6." << std::endl;
  
  //////////////// create simple scene ////////////////////
  //
  //  - single light source (directional, white)
  //  - plane at the center (red diffuse, with white phong 32)
  //  - 16 samples per pixel
  scene s;

  // create material
  const brdf_base& diff = s.addDiffuseBrdf();
  const brdf_base& ph32 = s.addPhongBrdf(32.0f);
  const albedo_base& red = s.addConstantAlbedo( color(1.0f, 0.0f, 0.0f) );
  const albedo_base& white = s.addConstantAlbedo( color(1.0f, 1.0f, 1.0f) );
  const material& mat = s.addMaterial(red, diff, white, ph32);

  // create geometry
  std::vector<triangle> plane = createPlane( vec3d(0.0f, -2.0f, 0.0f), vec3d(-4.0f, 4.0f, 0.0f), vec3d(4.0f, 4.0f, 0.0f) );
  const sceneGraph_base& obj = s.addSceneGraphObject(plane, mat);
  s.setSceneGraphRoot(obj);
  
  // create light source
  s.addDirectionalLightSource( vec3d(0.0f, 0.0f, -1.0f), color(1.0f, 1.0f, 1.0f) );

  // create camnera
  s.setCamera( camera(vec3d(0.0f, 0.0f, 5.0f),
		      vec3d(0.0f, 0.0f, -1.0f),
		      vec3d(0.0f, 1.0f, 0.0f),
		      35.0f * M_PI / 180.0f,
		      512, 512 )
	       );

  ////////////// render & save ////////////////
  image result = raytrace(s, 16, 1);
  result.save("hw6-result6.ppm");

  // Done.
}

///////////////////////////////////////////////////////////////////////////////

void renderScene7(void)
{
  std::cout << "Scene 7." << std::endl;
  
  //////////////// create simple scene ////////////////////
  //
  //  - two light source (red point, blue point)
  //  - two planes at above each other (white diffuse, with white phong 32)
  scene s;

  // create material
  const brdf_base& diff = s.addDiffuseBrdf();
  const brdf_base& ph32 = s.addPhongBrdf(32.0f);
  const albedo_base& white = s.addConstantAlbedo( color(1.0f, 1.0f, 1.0f) );
  const albedo_base& grey = s.addConstantAlbedo( color(0.2f, 0.2f, 0.2f) );
  const material& mat1 = s.addMaterial(white, diff, white, ph32);
  const material& mat2 = s.addMaterial(grey, diff, grey, ph32);

  // create geometry
  std::vector<triangle> plane1 = createTwoSidedPlane( vec3d(-2.0f, -2.0f, 0.0f), vec3d(0.0f, 4.0f, 0.0f), vec3d(4.0f, 0.0f, 0.0f) );
  std::vector<triangle> plane2 = createTwoSidedPlane( vec3d(-0.5f, -1.0f, 2.0f), vec3d(0.0f, 2.0f, 0.0f), vec3d(1.0f, 0.0f, 0.0f) );

  std::vector<const sceneGraph_base*> obj;
  obj.push_back(&s.addSceneGraphObject(plane1, mat1));
  obj.push_back(&s.addSceneGraphObject(plane2, mat2));
  const sceneGraph_base& root = s.addSceneGraphNode( transformation3d(), obj);

  s.setSceneGraphRoot(root);
  
  // create light source
  s.addPointLightSource( vec3d(-1.0f, 0.0f, 3.0f), color(1.0f, 0.0f, 0.0f), vec3d(0.0f, 0.0f, 0.2f) );
  s.addPointLightSource( vec3d(+1.0f, 0.0f, 3.0f), color(0.0f, 0.0f, 1.0f), vec3d(0.0f, 0.0f, 0.2f) );

  // create camnera
  s.setCamera( camera(vec3d(5.0f, 5.0f, 10.0f),
		      vec3d(-5.0f, -5.0f, -10.0f),
		      vec3d(0.0f, 0.0f, 1.0f),
		      35.0f * M_PI / 180.0f,
		      512, 512 )
	       );

  ////////////// render & save ////////////////
  image result = raytrace(s, 1, 1);
  result.save("hw6-result7.ppm");

  // Done.
}

///////////////////////////////////////////////////////////////////////////////

void renderScene8(void)
{
  std::cout << "Scene 8." << std::endl;
  
  //////////////// create simple scene ////////////////////
  //
  //  - two light source (red point, blue point)
  //  - two planes at above each other (white diffuse, with white phong 32)
  //  - 3 recusive depth
  scene s;

  // create material
  const brdf_base& diff = s.addDiffuseBrdf();
  const brdf_base& ph32 = s.addPhongBrdf(32.0f);
  const albedo_base& white = s.addConstantAlbedo( color(1.0f, 1.0f, 1.0f) );
  const albedo_base& grey = s.addConstantAlbedo( color(0.2f, 0.2f, 0.2f) );
  const material& mat1 = s.addMaterial(white, diff, white, ph32);
  const material& mat2 = s.addMaterial(grey, diff, grey, ph32);

  // create geometry
  std::vector<triangle> plane1 = createTwoSidedPlane( vec3d(-2.0f, -2.0f, 0.0f), vec3d(0.0f, 4.0f, 0.0f), vec3d(4.0f, 0.0f, 0.0f) );
  std::vector<triangle> plane2 = createTwoSidedPlane( vec3d(-0.5f, -1.0f, 2.0f), vec3d(0.0f, 2.0f, 0.0f), vec3d(1.0f, 0.0f, 0.0f) );

  std::vector<const sceneGraph_base*> obj;
  obj.push_back(&s.addSceneGraphObject(plane1, mat1));
  obj.push_back(&s.addSceneGraphObject(plane2, mat2));
  const sceneGraph_base& root = s.addSceneGraphNode( transformation3d(), obj);

  s.setSceneGraphRoot(root);
  
  // create light source
  s.addPointLightSource( vec3d(-1.0f, 0.0f, 3.0f), color(1.0f, 0.0f, 0.0f), vec3d(0.0f, 0.0f, 0.2f) );
  s.addPointLightSource( vec3d(+1.0f, 0.0f, 3.0f), color(0.0f, 0.0f, 1.0f), vec3d(0.0f, 0.0f, 0.2f) );

  // create camnera
  s.setCamera( camera(vec3d(5.0f, 5.0f, 10.0f),
		      vec3d(-5.0f, -5.0f, -10.0f),
		      vec3d(0.0f, 0.0f, 1.0f),
		      35.0f * M_PI / 180.0f,
		      512, 512 )
	       );

  ////////////// render & save ////////////////
  image result = raytrace(s, 1, 3);
  result.save("hw6-result8.ppm");

  // Done.
}

///////////////////////////////////////////////////////////////////////////////

void renderScene9(void)
{
  std::cout << "Scene 9." << std::endl;
  
  //////////////// create simple scene ////////////////////
  //
  //  - no lightsource
  //  - environment map
  //  - sphere at the center (with white phong 32)
  //
  scene s;

  // create material
  const brdf_base& ph32 = s.addPhongBrdf(32.0f);
  const albedo_base& white = s.addConstantAlbedo( color(0.8f, 0.8f, 0.8f) );
  const material& mat = s.addMaterial(white, ph32);

  // create geometry
  std::vector<triangle> sphere = createSphere( vec3d(0.0f, 0.0f, 0.0f), 1.0f, 16, 16 );
  const sceneGraph_base& obj = s.addSceneGraphObject(sphere, mat);
  s.setSceneGraphRoot(obj);
  
  // add environment map
  s.setEnvironmentMap("data/grace.ppm");

  // create camnera
  s.setCamera( camera(vec3d(0.0f, 3.0f, 0.0f),
		      vec3d(0.0f, -1.0f, 0.0f),
		      vec3d(0.0f, 0.0f, 1.0f),
		      35.0f * M_PI / 180.0f,
		      512, 512 )
	       );

  ////////////// render & save ////////////////
  image result = raytrace(s, 1, 2);
  result.save("hw6-result9.ppm");

  // Done.
}

///////////////////////////////////////////////////////////////////////////////

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
  if((mask & 2) != 0) renderScene1();
  if((mask & 4) != 0) renderScene2();
  if((mask & 8) != 0) renderScene3();
  if((mask & 16) != 0) renderScene4();
  if((mask & 32) != 0) renderScene5();
  if((mask & 64) != 0) renderScene6();
  if((mask & 128) != 0) renderScene7();
  if((mask & 256) != 0) renderScene8();
  if((mask & 512) != 0) renderScene9();

  ////////////////////////////////////////

  // Done.
  return 0;
}
