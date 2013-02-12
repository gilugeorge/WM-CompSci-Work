#include <iostream>

#include "ray.h"
#include "image.h"
#include "camera.h"
#include "triangle.h"

image generateImage(const camera& cam, const triangle& t)
{
  image result(cam.width(), cam.height());
  result.clear();

  // for every pixel
  for(image::size_type y=0; y < result.height(); y++)
    for(image::size_type x=0; x < result.width(); x++)
    {
      // create a view ray
      ray r = cam.generateViewRay(x,y);

      // intersect
      float p;
      vec3d bc;
      bool hit = t.intersect(r, bc, p);

      // if hit
      if(hit)
      {
				// set the pixel color to the barycentric coordinate
				result(x,y) = color(bc[0], bc[1], bc[2]);
      }
    }

  // Done.
  return result;
}


int main(int argc, char** argv)
{
  // Image 1
  std::cout << "Generating Image 1." << std::endl;

  triangle t1( vec3d(1.0f, -1.0f, -3.0f),
	       vec3d(0.0f, 1.0f, -3.0f),
	       vec3d(-1.0f, -1.0f, -3.0f) );

  camera c1( vec3d(0.0f, 0.0f, 0.0f),    // eye
	     vec3d(0.0f, 0.0f, -1.0f),   // view
	     vec3d(0.0f, 1.0f, 0.0f),    // up
	     60.0f / 180.0f * M_PI,      // field of view
	     512, 512 );                 // resolution

  image result1 = generateImage(c1, t1);
  result1.save("hw2-result1.ppm");


  // Image 2
  std::cout << "Generating Image 2." << std::endl;

  triangle t2( vec3d(1.0f, -1.0f, 3.0f),
	       vec3d(0.0f, 1.0f, 3.0f),
	       vec3d(-1.0f, -1.0f, 3.0f) );

  camera c2( vec3d(0.0f, 0.0f, 0.0f),    // eye
	     vec3d(0.0f, 0.0f, 1.0f),    // view
	     vec3d(0.0f, 1.0f, 0.0f),    // up
	     60.0f / 180.0f * M_PI,      // field of view
	     512, 512 );                 // resolution

  image result2 = generateImage(c2, t2);
  result2.save("hw2-result2.ppm");


  // Image 3
  std::cout << "Generating Image 3." << std::endl;
  image result3 = generateImage(c1, t2);
  result3.save("hw2-result3.ppm");


  // Image 4
  std::cout << "Generating Image 4." << std::endl;

  triangle t4( vec3d(0.0f, 1.0f, 3.0f),
	       vec3d(-1.0f, -1.0f, 3.0f),
	       vec3d(1.0f, -1.0f, 3.0f) );

  image result4 = generateImage(c2, t4);
  result4.save("hw2-result4.ppm");


  // Image 5
  std::cout << "Generating Image 5." << std::endl;

  camera c5( vec3d(0.0f, 0.0f, 2.0f),    // eye
	     vec3d(0.0f, 0.0f, 1.0f),    // view
	     vec3d(0.0f, 1.0f, 0.0f),    // up
	     60.0f / 180.0f * M_PI,      // field of view
	     512, 512 );                 // resolution

  image result5 = generateImage(c5, t4);
  result5.save("hw2-result5.ppm");


  // Image 6
  std::cout << "Generating Image 6." << std::endl;

  camera c6( vec3d(0.0f, -1.0f, 2.0f),   // eye
	     vec3d(0.0f, 1.0f, 1.0f),    // view
	     vec3d(1.0f, 0.0f, 0.0f),    // up
	     60.0f / 180.0f * M_PI,      // field of view
	     512, 512 );                 // resolution

  image result6 = generateImage(c6, t4);
  result6.save("hw2-result6.ppm");


  // Image 7
  std::cout << "Generating Image 7." << std::endl;

  camera c7( vec3d(-2.0f, 0.0f, -2.9f),   // eye
	     vec3d(1.0f, 0.0f, -0.1f),    // view
	     vec3d(0.0f, 1.0f, 0.0f),     // up
	     60.0f / 180.0f * M_PI,       // field of view
	     512, 512 );                  // resolution

  image result7 = generateImage(c7, t1);
  result7.save("hw2-result7.ppm");


  // Image 8
  std::cout << "Generating Image 8." << std::endl;

  camera c8( vec3d(-2.0f, 0.0f, -3.0f),   // eye
	     vec3d(1.0f, 0.0f, 0.0f),     // view
	     vec3d(0.0f, 1.0f, 0.0f),     // up
	     60.0f / 180.0f * M_PI,       // field of view
	     512, 512 );                  // resolution

  image result8 = generateImage(c8, t1);
  result8.save("hw2-result8.ppm");


  // Done.
  return 0;
}
