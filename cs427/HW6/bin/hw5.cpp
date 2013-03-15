#include <vector>
#include <iostream>
#include <cstdlib>

#include "phong.h"
#include "image.h"
#include "camera.h"
#include "scale3d.h"
#include "diffuse.h"
#include "geometry.h"
#include "material.h"
#include "rotation3d.h"
#include "rotationX3d.h"
#include "rotationY3d.h"
#include "rotationZ3d.h"
#include "triangleMesh.h"
#include "translation3d.h"
#include "texturedAlbedo.h"
#include "constantAlbedo.h"
#include "sceneGraphNode.h"
#include "sceneGraphObject.h"
#include "directionalLightsource.h"
#include "parallelTextureProjection.h"
#include "sphericalTextureProjection.h"

image generateImage(const camera& cam, const sceneGraphNode& sceneGraph, const lightsource_base& ls)
{
  image result(cam.width(), cam.height());
  result.clear();

  // for every pixel
  for(image::size_type y=0; y < result.height(); y++)
    for(image::size_type x=0; x < result.width(); x++)
  {
      // create view ray
      ray r = cam.generateViewRay(x, y);

      // intersect
      intersectionPoint ip = sceneGraph.intersect(r);

      // if hit
      if(ip.isHit())
      {
	result(x,y) = ip.evaluate(ls);
	//
	// Uncomment the 3 lines of code below to help with debugging.  
	// The image will now display the texture coordinates instead of the texture values.
	//
	//result(x,y).r = ip.textureCoordinate().u;
	//result(x,y).g = ip.textureCoordinate().v;
	//result(x,y).b = 1.0f;
      }
    }

  // Done.
  return result;
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


  // Initialize
  phong p32(32.0f);
  phong p64(64.0f);
  phong p16(16.0f);
  diffuse d;
  constantAlbedo white(color(1.0f, 1.0f, 1.0f));
  texturedAlbedo worldmap("data/world_map.ppm");
  texturedAlbedo squares("data/squares.ppm");

  std::vector<triangle> sphere = createSphere( vec3d(0.0f, 0.0f, 0.0f), 1.0f, 16, 16 );
  std::vector<triangle> plane = createPlane( vec3d(-1.0f, -1.0f, 0.0f), vec3d(0.0f, 2.0f, 0.0f), vec3d(2.0f, 0.0f, 0.0f) );

  material worldMaterial;
  worldMaterial.addComponent( reflectanceComponent(&worldmap, &d) );
  worldMaterial.addComponent( reflectanceComponent(&white, &p32) );

  material squaresMaterial;
  squaresMaterial.addComponent( reflectanceComponent(&squares, &d) );

  triangleMesh worldSphere(sphere, worldMaterial);
  triangleMesh squaresSphere(sphere, squaresMaterial);
  triangleMesh squaresPlane(plane, squaresMaterial);

  sceneGraphObject worldSphereObject(worldSphere);
  sceneGraphObject squaresSphereObject(squaresSphere);
  sceneGraphObject squaresPlaneObject(squaresPlane);

  camera cam( vec3d(0.0f, 0.0f, 5.0f),
	      vec3d(0.0f, 0.0f, -1.0f),
	      vec3d(0.0f, 1.0f, 0.0f),
	      35.0f * M_PI / 180.0f,
	      512, 512 );

  directionalLightsource frontal( color(1.0f, 1.0f, 1.0f), vec3d(0.0f, 0.0f, -1.0f) );


  /////////////////////////////////////////////////////

  sceneGraphNode sg1;
  sg1.addChildNode(worldSphereObject);
  
  if((mask & 2) != 0)
  {
    std::cout << "Generating Image 1." << std::endl;
    image result1 = generateImage(cam, sg1, frontal);
    result1.save("hw5-result1.ppm");
  }


  /////////////////////////////////////////////////////

  sceneGraphNode cubeside( translation3d(vec3d(0.0f, 0.0f, 1.0f)) );
  cubeside.addChildNode(squaresPlaneObject);

  sceneGraphNode cubeNode1( rotationY3d(0.0f / 2.0f * M_PI) );
  cubeNode1.addChildNode(cubeside);
  sceneGraphNode cubeNode2( rotationY3d(1.0f / 2.0f * M_PI) );
  cubeNode2.addChildNode(cubeside);
  sceneGraphNode cubeNode3( rotationY3d(2.0f / 2.0f * M_PI) );
  cubeNode3.addChildNode(cubeside);
  sceneGraphNode cubeNode4( rotationY3d(3.0f / 2.0f * M_PI) );
  cubeNode4.addChildNode(cubeside);
  sceneGraphNode cubeNode5( rotationX3d(0.5f * M_PI) );
  cubeNode5.addChildNode(cubeside);
  sceneGraphNode cubeNode6( rotationX3d(-0.5f * M_PI) );
  cubeNode6.addChildNode(cubeside);

  sceneGraphNode cube;
  cube.addChildNode(cubeNode1);
  cube.addChildNode(cubeNode2);
  cube.addChildNode(cubeNode3);
  cube.addChildNode(cubeNode4);
  cube.addChildNode(cubeNode5);
  cube.addChildNode(cubeNode6);

  sceneGraphNode sg2( rotation3d(0.25*M_PI, vec3d(1.0f, 0.75f, 0.5f)) );
  sg2.addChildNode(cube);
  

  if((mask & 4) != 0)
  {
    std::cout << "Generating Image 2." << std::endl;
    image result6 = generateImage(cam, sg2, frontal);
    result6.save("hw5-result2.ppm");
  }


  /////////////////////////////////////////////////////

  sphericalTextureProjection projection1(rotation3d(0.7*M_PI, vec3d(0.7f, 0.75f, 0.4f)) );
  worldSphere.applyTextureProjection(projection1);

  if((mask & 8) != 0)
  {
    std::cout << "Generating Image 3." << std::endl;
    image result3 = generateImage(cam, sg1, frontal);
    result3.save("hw5-result3.ppm");
  }


  /////////////////////////////////////////////////////

  sceneGraphNode sg4( rotationY3d(0.33*M_PI));
  sg4.addChildNode(squaresSphereObject);

  if((mask & 16) != 0)
  {
    std::cout << "Generating Image 4." << std::endl;
    image result4 = generateImage(cam, sg4, frontal);
    result4.save("hw5-result4.ppm");
  }


  /////////////////////////////////////////////////////

  parallelTextureProjection projection2(translation3d(vec3d(1.0f, 1.0f, 0.0f)));
  squaresSphere.applyTextureProjection(projection2);

  if((mask & 32) != 0)
  {
    std::cout << "Generating Image 5." << std::endl;
    image result5 = generateImage(cam, sg4, frontal);
    result5.save("hw5-result5.ppm");
  }

  /////////////////////////////////////////////////////

  // Done.
  return 0;
}
