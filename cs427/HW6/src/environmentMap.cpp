#include "environmentMap.h"

//////////////////
// Constructors //
//////////////////
environmentMap::environmentMap(const std::string& textureName, const transformation3d& transformation)
{
  _texture.load(textureName);
  _transformation = transformation;
}


environmentMap::environmentMap(const environmentMap& em)
{
  _texture = em._texture;
  _transformation = em._transformation;
}


  
//////////////
// Operator //
//////////////
environmentMap& environmentMap::operator=(const environmentMap& em)
{
  _assign(em);
  return *this;
}



/////////////
// Methods //
/////////////
color environmentMap::evaluate(const ray& r) const
{
  // HW6: implement this
  //      returns: the color in the environment in direction r.  You can see the environment as an infinitely 
  //               large sphere that sits around the scene (and which reflects light inwards).  You should use
  //               the normal theta-phi encoding of direction to texture coordinate.
  //      modifies: nothing
  
    // normalize
  vec3d n = r.direction().normalize();

  // compute (theta,phi)
  float theta = atan2(r.direction().y, r.direction().x);
  float phi = acos(r.direction().z);

  // map to [0,1]
	if(theta < 0.0f ) theta += (2.0f * M_PI);
	theta /= 2.0f * M_PI;
	phi /= M_PI;

	//bilinear interpolation
	float degree = M_PI/180;
	int thetaTimes = (int) theta/degree;
	int phiTimes = (int) phi/degree;
	float floor_theta = thetaTimes * degree;
	float floor_phi = phiTimes * degree;
	
	double u_ratio = theta - floor_theta;
	double v_ratio = phi - floor_phi;
	double u_opposite = 1 - u_ratio;
	double v_opposite = 1 - v_ratio;
	color result = (color) (_texture(floor_theta,floor_phi) * u_opposite  + _texture(floor_theta+1,floor_phi)   * u_ratio) * v_opposite + (_texture(floor_theta,floor_phi+1) * u_opposite  + _texture(floor_theta+1,floor_phi+1) * u_ratio) * v_ratio;

  // Done.
	return result;
//  return _texture(thetaPhi.x, thetaPhi.y);
  return color(0.0f, 0.0f, 0.0f);
}



/////////////////////
// Private Methods //
/////////////////////
void environmentMap::_swap(environmentMap& em)
{
  std::swap(_texture, em._texture);
  std::swap(_transformation, em._transformation);
}


void environmentMap::_assign(const environmentMap& em)
{
  // sanity check
  if(this == &em) return;

  // copy
  environmentMap temp(em);
  _swap(temp);

  // Done.
}
