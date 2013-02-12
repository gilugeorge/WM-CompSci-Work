#include <vector>
#include <iostream>
#include <cstdlib>

#include "phong.h"
#include "image.h"
#include "camera.h"
#include "diffuse.h"
#include "geometry.h"
#include "material.h"
#include "triangleMesh.h"
#include "constantAlbedo.h"
#include "directionalLightsource.h"


image generateImage(const camera& cam, const triangleMesh& scene, const lightsource_base& ls)
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
      intersectionPoint ip = scene.intersect(r);

      // if hit
      if(ip.isHit())
	result(x,y)  = ip.evaluate(ls);
    }

  // Done.
  return result;
}


int main(int argc, char** argv)
{
  ////////////////////////
  // parse command line //
  ////////////////////////
  unsigned int pos = 1;
  unsigned int mask = (argc >= 2) ? 0 : 0xFFFF;
  while(pos < argc)
  {
    unsigned int sceneNumber = atoi(argv[pos++]);
    mask |= 1 << sceneNumber;
  }

  //////////
  // Init //
  //////////
  phong p32(32.0f);
  phong p64(64.0f);
  phong p16(16.0f);
  diffuse d;
  constantAlbedo red(color(1.0f, 0.0f, 0.0f));
  constantAlbedo green(color(0.0f, 1.0f, 0.0f));
  constantAlbedo blue(color(0.0f, 0.0f, 1.0f));
  constantAlbedo white(color(1.0f, 1.0f, 1.0f));

  std::vector<triangle> sphere = createSphere( vec3d(0.0f, 0.0f, 0.0f), 1.0f, 16, 16 );

  camera cam( vec3d(0.0f, -3.0f, 0.0f),
	      vec3d(0.0f, 1.0f, 0.0f),
	      vec3d(0.0f, 0.0f, 1.0f),
	      60.0f * M_PI / 180.0f,
	      512, 512 );

  /////////////
  // Scene 1 //
  /////////////
  if((mask & 2) != 0)
  {
    std::cout << "Generating Image 1." << std::endl;

    // material
    material m1;
    m1.addComponent( reflectanceComponent(&red, &d) );
    m1.addComponent( reflectanceComponent(&white, &p32) );

    // geometry
    triangleMesh scene1(sphere, m1);

    // lighting
    directionalLightsource d1( color(1.0f, 1.0f, 1.0f), vec3d(0.0f, 1.0f, -1.0f) );
    
    image result1 = generateImage(cam, scene1, d1);
    result1.save("hw3-result1.ppm");
  }


  /////////////
  // Scene 2 //
  /////////////
  if((mask & 4) != 0)
  {
    std::cout << "Generating Image 2." << std::endl;

    // material
    material m2;
    m2.addComponent( reflectanceComponent(&red, &d) );
    m2.addComponent( reflectanceComponent(&white, &p32) );

    // geometry
    triangleMesh scene2(sphere, m2);

    // lighting
    directionalLightsource d2( color(1.0f, 0.5f, 0.25f), vec3d(0.0f, 1.0f, 0.0f) );

    image result2 = generateImage(cam, scene2, d2);
    result2.save("hw3-result2.ppm");
  }
  

  /////////////
  // Scene 3 //
  /////////////
  if((mask & 8) != 0)
  {
    std::cout << "Generating Image 3." << std::endl;

    // material
    material m3;
    m3.addComponent( reflectanceComponent(&red, &d) );
    m3.addComponent( reflectanceComponent(&white, &p32) );

    // geometry
    triangleMesh scene3(sphere, m3);

    // lighting
    directionalLightsource d3( color(0.0f, 1.0f, 0.0f), vec3d(0.0f, 1.0f, 1.0f) );

    image result3 = generateImage(cam, scene3, d3);
    result3.save("hw3-result3.ppm");  
  }


  /////////////
  // Scene 4 //
  /////////////
  if((mask & 16) != 0)
  {
    std::cout << "Generating Image 4." << std::endl;

    // material
    material m4;
    m4.addComponent( reflectanceComponent(&white, &p16) );
  
    // geometry
    triangleMesh scene4(sphere, m4);
    
    // lighting
    directionalLightsource d4( color(1.0f, 1.0f, 1.0f), vec3d(0.0f, -1.0f, 0.0f) );

    image result4 = generateImage(cam, scene4, d4);
    result4.save("hw3-result4.ppm");
  }


  /////////////
  // Scene 5 //
  /////////////
  if((mask & 32) != 0)
  {
    std::cout << "Generating Image 5." << std::endl;

    // material
    material m5;
    m5.addComponent( reflectanceComponent(&white, &p16) );
  
    // geometry
    triangleMesh scene5(sphere, m5);

    // lighting
    directionalLightsource d5( color(1.0f, 1.0f, 1.0f), vec3d(0.0f, 1.0f, -1.0f) );

    image result5 = generateImage(cam, scene5, d5);
    result5.save("hw3-result5.ppm");
  }
  

  /////////////
  // Scene 6 //
  /////////////
  if((mask & 64) != 0)
  {
    std::cout << "Generating Image 6." << std::endl;

    // material
    material m6;
    m6.addComponent( reflectanceComponent(&green, &d) );
    m6.addComponent( reflectanceComponent(&white, &p64) );

    // geometry
    triangleMesh scene6(sphere, m6);

    // lighting
    directionalLightsource d6( color(1.0f, 1.0f, 1.0f), vec3d(0.0f, 1.0f, -1.0f) );

    image result6 = generateImage(cam, scene6, d6);
    result6.save("hw3-result6.ppm");
  }


  /////////////
  // Scene 7 //
  /////////////
  if((mask & 128) != 0)
  {
    std::cout << "Generating Image 7." << std::endl;

    // material
    material m7;
    m7.addComponent( reflectanceComponent(&green, &d) );
    m7.addComponent( reflectanceComponent(&white, &p64) );

    // geometry
    triangleMesh scene7(sphere, m7);

    // lighting
    directionalLightsource d7( color(1.0f, 1.0f, 1.0f), vec3d(-1.0f, 1.0f, 1.0f) );

    image result7 = generateImage(cam, scene7, d7);
    result7.save("hw3-result7.ppm");
  }

  return 0;
}
