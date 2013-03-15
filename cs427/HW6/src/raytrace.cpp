#include <cstdlib>

#include "raytrace.h"

#include "ray.h"
#include "vec3d.h"
#include "image.h"
#include "constants.h"
#include "intersectionPoint.h"


image raytrace(const scene& scene, unsigned int samplesPerPixel, unsigned int maxBounce)
{
  // HW 6: implement this
  //       returns: the image of the 'scene', by shooting 'samplesPerPixel' randomly selected 
  //                rays through every pixel, and following specular reflections for 'maxBounce'
  //                bounces (eye->1st intersection == 1 bounce).
  //       modifes: nothing

  image result(scene.getCamera().width(), scene.getCamera().height());
  result.clear();
  return result;
}
