#include <cmath>

#include "geometry.h"

vec3d sphericalToCartesian(float theta, float phi)
{
  return vec3d( cos(theta)*sin(phi), 
		sin(theta)*sin(phi),
		cos(phi) );
}


std::vector<triangle> createSphere(const vec3d& origin, float radius, unsigned int thetaSubdiv, unsigned int phiSubdiv)
{
  std::vector<triangle> geometry;

  // create top
  vec3d top(origin.x, origin.y, origin.z + radius);

  float phi = 1.0f / (float)(phiSubdiv);
  for(unsigned int thetaIdx=0; thetaIdx < thetaSubdiv; thetaIdx++)
  {
    float theta0 = (float)(thetaIdx) / (float)(thetaSubdiv);
    float theta1 = (float)(thetaIdx+1) / (float)(thetaSubdiv);
    vec3d v0 = sphericalToCartesian(theta0 * 2.0f * M_PI, phi * M_PI); 
    vec3d v1 = sphericalToCartesian(theta1 * 2.0f * M_PI, phi * M_PI); 

    geometry.push_back( triangle( top,                      origin + radius * v0, origin + radius * v1,   // vertices
				  vec3d(0.0f, 0.0f, +1.0f), v0,                   v1,                     // normals
				  vec2d(theta0, 0.0f),      vec2d(theta0, phi),   vec2d(theta1, phi) ));  // texture coordinates
  }


  // create middle
  for(unsigned int phiIdx=1; phiIdx < phiSubdiv-1; phiIdx++) 
    for(unsigned int thetaIdx=0; thetaIdx < thetaSubdiv; thetaIdx++)
    {
      float theta0 = (float)(thetaIdx) / (float)(thetaSubdiv);
      float theta1 = (float)(thetaIdx+1) / (float)(thetaSubdiv);
      float phi0 = (float)(phiIdx) / (float)(phiSubdiv);
      float phi1 = (float)(phiIdx+1) / (float)(phiSubdiv);

      vec3d v0 = sphericalToCartesian(theta0 * 2.0f * M_PI, phi0 * M_PI); 
      vec3d v1 = sphericalToCartesian(theta1 * 2.0f * M_PI, phi0 * M_PI); 
      vec3d v2 = sphericalToCartesian(theta0 * 2.0f * M_PI, phi1 * M_PI); 
      vec3d v3 = sphericalToCartesian(theta1 * 2.0f * M_PI, phi1 * M_PI); 

      geometry.push_back( triangle( origin + radius * v0, origin + radius * v2, origin + radius * v1,    // vertices
				    v0,                   v2,                   v1,                      // normals
				    vec2d(theta0, phi0),  vec2d(theta0, phi1),  vec2d(theta1, phi0) ));  // texture coordinates
			  
      geometry.push_back( triangle( origin + radius * v1, origin + radius * v2, origin + radius * v3,    // vertices
				    v1,                   v2,                   v3,                      // normals
				    vec2d(theta1, phi0),  vec2d(theta0, phi1),  vec2d(theta1, phi1) ));  // texture coordinates
      
  }


  // create bottom
  vec3d bottom(origin.x, origin.y, origin.z - radius);

  phi = 1.0f - phi;
  for(unsigned int thetaIdx=0; thetaIdx < thetaSubdiv; thetaIdx++)
  {
    float theta0 = (float)(thetaIdx) / (float)(thetaSubdiv);
    float theta1 = (float)(thetaIdx+1) / (float)(thetaSubdiv);
    vec3d v0 = sphericalToCartesian(theta0 * 2.0f * M_PI, phi * M_PI); 
    vec3d v1 = sphericalToCartesian(theta1 * 2.0f * M_PI, phi * M_PI); 

    geometry.push_back( triangle( bottom,                   origin + radius * v1, origin + radius * v0,   // vertices
				  vec3d(0.0f, 0.0f, -1.0f), v1,                   v0,                     // normals
				  vec2d(theta1, 1.0f),      vec2d(theta1, phi),   vec2d(theta0, phi) ));  // texture coordinates
  } 

  // Done.
  return geometry;
}


std::vector<triangle> createPlane(const vec3d& origin, const vec3d& U, const vec3d& V)
{
  std::vector<triangle> geometry;
  vec3d normal = V.cross(U);

  geometry.push_back( triangle( origin,            origin + V,        origin + U,
				normal,            normal,            normal,
				vec2d(0.0f, 0.0f), vec2d(0.0f, 1.0f), vec2d(1.0f, 0.0f) ));

  geometry.push_back( triangle( origin + U + V,    origin + U,        origin + V,
				normal,            normal,            normal,
				vec2d(1.0f, 1.0f), vec2d(1.0f, 0.0f), vec2d(0.0f, 1.0f) ));

  // Done.
  return geometry;
}


std::vector<triangle> createTwoSidedPlane(const vec3d& origin, const vec3d& U, const vec3d& V)
{
  std::vector<triangle> geometry;
  vec3d normal = V.cross(U);

  geometry.push_back( triangle( origin,            origin + V,        origin + U,
				normal,            normal,            normal,
				vec2d(0.0f, 0.0f), vec2d(0.0f, 1.0f), vec2d(1.0f, 0.0f) ));

  geometry.push_back( triangle( origin + U + V,    origin + U,        origin + V,
				normal,            normal,            normal,
				vec2d(1.0f, 1.0f), vec2d(1.0f, 0.0f), vec2d(0.0f, 1.0f) ));

  geometry.push_back( triangle( origin,            origin + U,        origin + V,
				normal * -1.0f,    normal * -1.0f,    normal * -1.0f,
				vec2d(0.0f, 0.0f), vec2d(0.0f, 1.0f), vec2d(1.0f, 0.0f) ));

  geometry.push_back( triangle( origin + U + V,    origin + V,        origin + U,
				normal * -1.0f,    normal * -1.0f,    normal * -1.0f,
				vec2d(1.0f, 1.0f), vec2d(1.0f, 0.0f), vec2d(0.0f, 1.0f) ));

  // Done.
  return geometry;
}
