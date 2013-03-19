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

	for(image::size_type y=0; y < result.height(); y++) {
    for(image::size_type x=0; x < result.width(); x++) {
    	//create view ray
	  	ray r = scene.getCamera().generateViewRay(x,y);
			
			
	  	intersectionPoint ip = scene.intersect(r);
			color accumLight;
      // if hit
      if(ip.isHit()){
      	//result(x,y) = ip.evaluate(scene.lightSource(0));
				for(unsigned int i=0; i <= scene.numberOfLightSources()-1; i++){				
					accumLight += ip.evaluate(scene.lightSource(i));
				}				
				result(x,y) = accumLight;	 
				
  		}
 		}
 	}
 	
 	return result;
/*
Trace(ray)
	Foreach object in scene
		Intersect(ray, object)
	If no intersections
		return BackgroundColor
	For each light
		Foreach object in scene
			Intersect(ShadowRay, object)
		Accumulate local illumination
	Trace(ReflectionRay)
	Trace(TransmissionRay)
	Accumulate global illumination
	Return illumination
*/

}
