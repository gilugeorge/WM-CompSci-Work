#include <cstdlib>

#include "raytrace.h"

#include "ray.h"
#include "vec3d.h"
#include "image.h"
#include "constants.h"
#include "intersectionPoint.h"


/***************************************************************************************************/
/************************************* Helper Methods **********************************************/
/***************************************************************************************************/

vec3d reflect(const vec3d& dir, const vec3d& normal)
{
  return 2.0f * (normal.dot(dir)) * normal - dir;
}


ray createRay(const intersectionPoint& ip, const vec3d& dir)
{
  return ray( ip.point() + dir*EPSILON, dir);
}


color traceRay(const scene& scene, const ray& r, unsigned int maxBounce, unsigned int currentBounce)
{
  // intersect
  intersectionPoint ip = scene.intersect(r);
  
  // if hit
  color rayColor(0.0f, 0.0f, 0.0f);
  if(ip.isHit())
  {
    // shade point
    for(unsigned int l = 0; l < scene.numberOfLightSources(); l++)
    {
      // check if light source is occluded (shadows) or not (shade)
      vec3d lightSourceDir = scene.lightSource(l).getDirection(ip.point()) * -1.0f;
      if(!scene.isHit( createRay(ip, lightSourceDir) ))
	rayColor += ip.evaluate( scene.lightSource(l) );
    }

    // recurse
    if(currentBounce < maxBounce)
    {
      ray reflectedRay = createRay(ip, reflect(r.direction() * -1.0f, ip.normal()));
      rayColor += ip.evaluate(reflectedRay.direction()) * traceRay(scene, 
								   reflectedRay,
								   maxBounce, 
								   currentBounce + 1);
    }
  }

  // if not hit, check environment map
  else if(scene.hasEnvironmentMap())
  {
    rayColor = scene.getEnvironmentMap().evaluate(r);
  }

  // Done.
  return rayColor;
}

/***************************************************************************************************/
/****************************************** End Helper Methods *************************************/
/***************************************************************************************************/
image raytrace(const scene& scene, unsigned int samplesPerPixel, unsigned int maxBounce)
{
  image result(scene.getCamera().width(), scene.getCamera().height());
  result.clear();

  // for every pixel
  for(image::size_type y=0; y < result.height(); y++)
    for(image::size_type x=0; x < result.width(); x++)
    {
      color pixelColor(0.0f, 0.0f, 0.0f);

      // for every sample per pixel
      for(unsigned int sample = 0; sample < samplesPerPixel; sample++)
      {
	// create view ray
	float px = (samplesPerPixel == 1) ? (float)(x) + 0.5f : (float)(x) + drand48();
	float py = (samplesPerPixel == 1) ? (float)(y) + 0.5f : (float)(y) + drand48();
	ray r = scene.getCamera().generateViewRay(px, py);

	// intersect scene
	pixelColor += traceRay(scene, r, maxBounce, 1);
      }

      // store in image
      result(x,y) = pixelColor / (float)(samplesPerPixel);
    }

  // Done.
  return result;
}


