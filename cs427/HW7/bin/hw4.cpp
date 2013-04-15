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
#include "constantAlbedo.h"
#include "sceneGraphNode.h"
#include "sceneGraphObject.h"
#include "directionalLightsource.h"


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
	result(x,y)  = ip.evaluate(ls);
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
  constantAlbedo red(color(1.0f, 0.0f, 0.0f));
  constantAlbedo green(color(0.0f, 1.0f, 0.0f));
  constantAlbedo blue(color(0.0f, 0.0f, 1.0f));
  constantAlbedo white(color(1.0f, 1.0f, 1.0f));

  std::vector<triangle> sphere = createSphere( vec3d(0.0f, 0.0f, 0.0f), 1.0f, 16, 16 );
  std::vector<triangle> plane = createPlane( vec3d(-1.0f, -1.0f, 0.0f), vec3d(0.0f, 2.0f, 0.0f), vec3d(2.0f, 0.0f, 0.0f) );

  material redMaterial;
  redMaterial.addComponent( reflectanceComponent(&red, &d) );
  redMaterial.addComponent( reflectanceComponent(&white, &p32) );

  material greenMaterial;
  greenMaterial.addComponent( reflectanceComponent(&green, &d) );
  greenMaterial.addComponent( reflectanceComponent(&white, &p64) );

  material blueMaterial;
  blueMaterial.addComponent( reflectanceComponent(&blue, &d) );
  blueMaterial.addComponent( reflectanceComponent(&white, &p16) );

  material whiteMaterial;
  whiteMaterial.addComponent( reflectanceComponent(&white, &d) );

  triangleMesh redSphere(sphere, redMaterial);
  triangleMesh greenSphere(sphere, greenMaterial);
  triangleMesh blueSphere(sphere, blueMaterial);
  triangleMesh whitePlane(plane, whiteMaterial);

  sceneGraphObject redSphereObject(redSphere);
  sceneGraphObject greenSphereObject(greenSphere);
  sceneGraphObject blueSphereObject(blueSphere);
  sceneGraphObject whitePlaneObject(whitePlane);

  camera cam( vec3d(0.0f, 0.0f, 5.0f),
	      vec3d(0.0f, 0.0f, -1.0f),
	      vec3d(0.0f, 1.0f, 0.0f),
	      35.0f * M_PI / 180.0f,
	      512, 512 );

  directionalLightsource ls( color(1.0f, 1.0f, 1.0f), vec3d(0.0f, -1.0f, -1.0f) );
  directionalLightsource frontal( color(1.0f, 1.0f, 1.0f), vec3d(0.0f, 0.0f, -1.0f) );


  /////////////////////////////////////////////////////

  if((mask & 2) != 0)
  {
    sceneGraphNode sg1;
    sg1.addChildNode(redSphereObject);
  
    std::cout << "Generating Image 1." << std::endl;
    image result1 = generateImage(cam, sg1, ls);
    result1.save("hw4-result1.ppm");
  }


  /////////////////////////////////////////////////////

  if((mask & 4) != 0)
  {
    sceneGraphNode sg2node1(translation3d(vec3d(+1.0f, 0.0f, 0.0f)));
    sg2node1.addChildNode(redSphereObject);

    sceneGraphNode sg2node2(translation3d(vec3d(-1.0f, 0.0f, 0.0f)));
    sg2node2.addChildNode(blueSphereObject);

    sceneGraphNode sg2;
    sg2.addChildNode(sg2node1);
    sg2.addChildNode(sg2node2);

    std::cout << "Generating Image 2." << std::endl;
    image result2 = generateImage(cam, sg2, ls);
    result2.save("hw4-result2.ppm");
  }


  /////////////////////////////////////////////////////

  if((mask & 8) != 0)
  {
    sceneGraphNode sg3node1(scale3d(2.0f, 0.5f, 0.5f));
    sg3node1.addChildNode(greenSphereObject);

    sceneGraphNode sg3;
    sg3.addChildNode(sg3node1);
  
    std::cout << "Generating Image 3." << std::endl;
    image result3 = generateImage(cam, sg3, ls);
    result3.save("hw4-result3.ppm");
  }


  /////////////////////////////////////////////////////

  if((mask & 16) != 0)
  {
    sceneGraphNode sg2node1(translation3d(vec3d(+1.0f, 0.0f, 0.0f)));
    sg2node1.addChildNode(redSphereObject);

    sceneGraphNode sg2node2(translation3d(vec3d(-1.0f, 0.0f, 0.0f)));
    sg2node2.addChildNode(blueSphereObject);

    sceneGraphNode sg2;
    sg2.addChildNode(sg2node1);
    sg2.addChildNode(sg2node2);

    sceneGraphNode sg4node1(rotationY3d(M_PI));
    sg4node1.addChildNode(sg2);

    sceneGraphNode sg4;
    sg4.addChildNode(sg4node1);
  
    std::cout << "Generating Image 4." << std::endl;
    image result4 = generateImage(cam, sg4, ls);
    result4.save("hw4-result4.ppm");
  }


  /////////////////////////////////////////////////////

  if((mask & 32) != 0)
  {
    sceneGraphNode sg5node0(scale3d(0.5f, 0.5f, 0.5f));
    sceneGraphNode sg5node1(rotationY3d(0.5 * M_PI));
    sceneGraphNode sg5node2(rotationX3d(0.5 * M_PI));
    sceneGraphNode sg5node3(translation3d(vec3d(0.0f, 2.0f, 0.0f)));
    sceneGraphNode sg5node4(rotationX3d(0.5 * M_PI));
    sceneGraphNode sg5node5(translation3d(vec3d(0.0f, 2.0f, 0.0f)));
    sceneGraphNode sg5node6(rotationX3d(0.5 * M_PI));
    sceneGraphNode sg5node7(translation3d(vec3d(0.0f, 2.0f, 0.0f)));
    sceneGraphNode sg5node8(rotationX3d(0.5 * M_PI));
    sceneGraphNode sg5node9(translation3d(vec3d(0.0f, 2.0f, 0.0f)));

    sceneGraphNode sg5;
    sg5.addChildNode(sg5node0);
    sg5node0.addChildNode(sg5node1);
    sg5node1.addChildNode(sg5node2);
    sg5node2.addChildNode(sg5node3);
    sg5node3.addChildNode(redSphereObject);
    sg5node3.addChildNode(sg5node4);
    sg5node4.addChildNode(sg5node5);
    sg5node5.addChildNode(greenSphereObject);
    sg5node5.addChildNode(sg5node6);
    sg5node6.addChildNode(sg5node7);
    sg5node7.addChildNode(blueSphereObject);
    sg5node7.addChildNode(sg5node8);
    sg5node8.addChildNode(sg5node9);
    sg5node9.addChildNode(blueSphereObject);
    
    std::cout << "Generating Image 5." << std::endl;
    image result5 = generateImage(cam, sg5, ls);
    result5.save("hw4-result5.ppm");
  }


  /////////////////////////////////////////////////////

  if((mask & 64) != 0)
  {
    sceneGraphNode cubeside( translation3d(vec3d(0.0f, 0.0f, 1.0f)) );
    cubeside.addChildNode(whitePlaneObject);

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
    
    sceneGraphNode sg6( rotation3d(0.25*M_PI, vec3d(1.0f, 0.75f, 0.5f)) );
    sg6.addChildNode(cube);
  
    std::cout << "Generating Image 6." << std::endl;
    image result6 = generateImage(cam, sg6, frontal);
    result6.save("hw4-result6.ppm");
  }

  // Done.
  return 0;
}
