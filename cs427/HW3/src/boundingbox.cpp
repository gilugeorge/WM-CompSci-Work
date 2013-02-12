#include "interval.h"
#include "constants.h"
#include "boundingbox.h"


/////////////////
// Constructor //
/////////////////
boundingBox::boundingBox(void)
{
  _ltf = vec3d(-LARGE);
  _rbb = vec3d(+LARGE);
}


boundingBox::boundingBox(const vec3d& rbb, const vec3d& ltf) 
{
  _ltf = ltf; 
  _rbb = rbb;

  // Make sure _ltf is always smaller (i.e., left top front) than _rbb.
  for(unsigned int i=0; i < 3; i++)
    if(_rbb[i] < _ltf[i]) std::swap(_rbb[i], _ltf[i]);
  
  // Done.
}


boundingBox::boundingBox(const boundingBox& bb)
{
  _ltf = bb._ltf;
  _rbb = bb._rbb;
}
  


///////////////
// Operators //
///////////////
boundingBox& boundingBox::operator=(const boundingBox& src) 
{ 
  _assign(src); 
  return *this; 
}


boundingBox& boundingBox::operator+=(const boundingBox& bb)
{
  // compute the union of two bounding boxes.
  for(unsigned int i=0; i < 3; i++)
  {
    if(_ltf[i] < bb._ltf[i]) _ltf[i] = bb._ltf[i];
    if(_rbb[i] > bb._rbb[i]) _rbb[i] = bb._rbb[i];
  }

  return *this;
}


boundingBox boundingBox::operator+(const boundingBox& bb) const
{
  boundingBox res(*this);
  res += bb;
  return res;
}



////////////////
// Inspectors //
////////////////
const vec3d& boundingBox::leftTopFront(void) const
{ 
  return _ltf; 
}


const vec3d& boundingBox::rightBottomBack(void) const 
{ 
  return _rbb; 
}


vec3d boundingBox::size(void) const
{ 
  return _ltf - _rbb; 
}



/////////////
// Methods //
/////////////
void boundingBox::expand(const vec3d& p)
{
  // Move bounds if point lies outside.
  for(unsigned int i=0; i < 3; i++)
  {
    if(_ltf[i] < p[i]) _ltf[i] = p[i];
    if(_rbb[i] > p[i]) _rbb[i] = p[i];
  }
}


void boundingBox::expand(const vec3d& p, float border)
{
  // Move bounds if point lies outside. Move bounds to point + additional padding (border)
  for(unsigned int i=0; i < 3; i++)
  {
    if(_ltf[i] < p[i]+border) _ltf[i] = p[i]+border;
    if(_rbb[i] > p[i]-border) _rbb[i] = p[i]-border;
  }
}


void boundingBox::expand(float border)
{ 
  // expand the box by a border-margin.
  _ltf += vec3d(border); 
  _rbb -= vec3d(border); 
}


bool boundingBox::isIn(const vec3d& p) const
{
  return (_ltf.x > p.x && _ltf.y > p.y && _ltf.z > p.z &&
	  _rbb.x < p.x && _rbb.y < p.y && _rbb.z < p.z );
}


bool boundingBox::isHit(const ray& r) const
{
  // init
  interval boxInterval(0, +LARGE);

  // for every slab
  for(unsigned int i=0; i != 3; i++)
  {
    // compute the slab
    interval slab(_rbb[i], _ltf[i]);
    slab -= r.origin()[i];

    // check for the case where the ray is parallel to the slab
    if(fabs(r.direction()[i]) < EPSILON)
    {
      // if identical signs => no hit
      if((slab.lower() < 0.0f) == (slab.upper() < 0.0f))
	return false;

      // skip remainder to this iteration
      continue;
    }
    else
      slab /= r.direction()[i];

    // intersect
    boxInterval.intersect(slab);
    if(boxInterval.empty())
      return false;
  }

  // Done.
  return true;
}



/////////////////////
// Private Methods //
/////////////////////
void boundingBox::_swap(boundingBox& bb)
{
  std::swap(_ltf, bb._ltf);
  std::swap(_rbb, bb._rbb);
}


void boundingBox::_assign(const boundingBox& bb)
{
  // trivial case check
  if(this == &bb) return;

  // copy
  _ltf = bb._ltf;
  _rbb = bb._rbb;

  // Done.
}

 
