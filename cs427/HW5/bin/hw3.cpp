#include <vector>
#include <iostream>

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

  // Scene 1
  std::cout << "Generating Image 1." << std::endl;

  material m1;
  m1.addComponent( reflectanceComponent(&red, &d) );
  m1.addComponent( reflectanceComponent(&white, &p32) );

  directionalLightsource d1( color(1.0f, 1.0f, 1.0f), vec3d(0.0f, 1.0f, -1.0f) );
 
  triangleMesh scene1(sphere, m1);

  image result1 = generateImage(cam, scene1, d1);
  result1.save("hw3-result1.ppm");


  // Scene 2
  std::cout << "Generating Image 2." << std::endl;

  directionalLightsource d2( color(1.0f, 0.5f, 0.25f), vec3d(0.0f, 1.0f, 0.0f) );
  image result2 = generateImage(cam, scene1, d2);
  result2.save("hw3-result2.ppm");

  
  // Scene 3
  std::cout << "Generating Image 3." << std::endl;

  directionalLightsource d3( color(0.0f, 1.0f, 0.0f), vec3d(0.0f, 1.0f, 1.0f) );
  image result3 = generateImage(cam, scene1, d3);
  result3.save("hw3-result3.ppm");  


  // Scene 4
  std::cout << "Generating Image 4." << std::endl;

  material m4;
  m4.addComponent( reflectanceComponent(&white, &p16) );
  
  triangleMesh scene4(sphere, m4);

  directionalLightsource d4( color(1.0f, 1.0f, 1.0f), vec3d(0.0f, -1.0f, 0.0f) );

  image result4 = generateImage(cam, scene4, d4);
  result4.save("hw3-result4.ppm");


  // Scene 5
  std::cout << "Generating Image 5." << std::endl;

  image result5 = generateImage(cam, scene4, d1);
  result5.save("hw3-result5.ppm");

  
  // Scene 6
  std::cout << "Generating Image 6." << std::endl;

  material m6;
  m6.addComponent( reflectanceComponent(&green, &d) );
  m6.addComponent( reflectanceComponent(&white, &p64) );

  triangleMesh scene6(sphere, m6);

  image result6 = generateImage(cam, scene6, d1);
  result6.save("hw3-result6.ppm");


  // Scene 7
  std::cout << "Generating Image 7." << std::endl;

  directionalLightsource d7( color(1.0f, 1.0f, 1.0f), vec3d(-1.0f, 1.0f, 1.0f) );
  image result7 = generateImage(cam, scene6, d7);
  result7.save("hw3-result7.ppm");


  return 0;
}
