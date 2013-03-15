#ifndef _RAYTRACE_H_
#define _RAYTRACE_H_

#include "scene.h"
#include "image.h"

image raytrace(const scene& scene, unsigned int samplesPerPixel=1, unsigned int maxBounce=3); 

#endif /* _RAYTRACE_H_ */
