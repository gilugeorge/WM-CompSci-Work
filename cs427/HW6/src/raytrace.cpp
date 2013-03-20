#include <cstdlib>
#include <iostream>
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
	color accumLight; //accumulated local illumination
	ray r;
	int bounceNum = maxBounce;
	
	for(image::size_type y=0; y < result.height(); y++) {
    for(image::size_type x=0; x < result.width(); x++) {
			accumLight *= 0; //reset color value
	  	for(int i = samplesPerPixel; i > 0; i--){
	  		//create view ray(s)
	  		if(i == 1)
	  			r = scene.getCamera().generateViewRay(x+.5,y+.5);
	  		else{//generate random rays
	  			float xPlus = rand() / float(RAND_MAX);
	  			float yPlus = rand() / float(RAND_MAX);
	  			r = scene.getCamera().generateViewRay(x+xPlus,y+yPlus);
	  		}
	  		
	  		intersectionPoint ip = scene.intersect(r);
		    // if hit
		    if(ip.isHit() && scene.numberOfLightSources() >= 1 ){
					for(unsigned int i=0; i <= scene.numberOfLightSources()-1; i++){				
						ray sRay(ip.point(),(-1 * scene.lightSource(i).getDirection(ip.point())));
						intersectionPoint s_ip = scene.intersect(sRay);
						if(!s_ip.isHit()){
							accumLight += ip.evaluate(scene.lightSource(i));
						}
						
					//specular reflection	
					ray reflectionRay;
					intersectionPoint ref_ip;
					bool check = true;
					bounceNum = maxBounce;
					while(bounceNum > 0){
						//std::cout<<"bounces: " << bounceNum << std::endl;
						if(check){
							reflectionRay = (ray) (ip.point(), 2*(ip.normal().dot(r.direction()))*ip.normal() - r.direction());
							check = false;
						}else{
							reflectionRay = (ray) (ref_ip.point(),2*(ref_ip.normal().dot(reflectionRay.direction()))*ref_ip.normal()- reflectionRay.direction());
							//std::cout<<"reflectionRay"<<reflectionRay << std::endl;
						}
						ref_ip = scene.intersect(reflectionRay);
						//std::cout<<"ref_ip "<<ref_ip << std::endl;
						if(ref_ip.isHit()){
							accumLight += ref_ip.evaluate(scene.lightSource(i));
						}
						bounceNum--;
						}//compute specular reflection
					}//compute shadow
					
					
					
				}
			}//for samplesPerPixel
			result(x,y) = accumLight/samplesPerPixel; 	
  		
 		}//for x
 	}//for y
 	
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
