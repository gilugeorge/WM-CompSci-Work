#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <vector>

#include "vec3d.h"
#include "triangle.h"

std::vector<triangle> createSphere(const vec3d& origin, float radius, unsigned int thetaSubdiv, unsigned int phiSubdiv);
std::vector<triangle> createPlane(const vec3d& origin, const vec3d& U, const vec3d& V);
std::vector<triangle> createTwoSidedPlane(const vec3d& origin, const vec3d& U, const vec3d& V);

#endif /* _GEOMETRY_H_ */
