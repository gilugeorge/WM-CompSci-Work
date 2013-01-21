// CSCI427-527 Spring 2012
// Homework 1: Vectors
////////////////////////////
//
// Assignment: implement the following methods in src/vec3d.cpp
//
// operator-  : vector - vector
// operator*  : vector * vector
// operator*  : vector * scalar
// operator/  : vector / vector
// operator/  : vector / scalar
// operator-= : *this = *this - vector
// operator*= : *this = *this * vector
// operator*= : *this = *this * scalar
// operator/= : *this = *this / vector
// operator/= : *this = *this / scalar
// dot        : dot product between vectors
// normalize  : returns a normalized version of a vector
// cross      : cross product between vectors
//

#include <iostream>
#include "vec3d.h"

int main(int argc, char** argv)
{
  vec3d u(1.0f, 2.0f, 3.0f);
  vec3d v(1.0f, 0.0f, 0.0f);
  vec3d w(0.0f, 1.0f, 0.0f);

  std::cout << "Vector u = " << u << std::endl;
  std::cout << "Vector v = " << v << std::endl;
  std::cout << "Vector w = " << w << std::endl;

  // basis operators
  std::cout << "u + v    = " << (u+v)    << " should be: [2,2,3]" << std::endl;
  std::cout << "u - w    = " << (u-w)    << " should be: [1,1,3]" << std::endl;
  std::cout << "u * w    = " << (u*w)    << " should be: [0,2,0]" << std::endl;  
  std::cout << "u * 0.5f = " << (u*0.5f) << " should be: [0.5,1,1.5]" << std::endl;  
  std::cout << "2.0f * ((v+w) / u)) = " << (2.0f * ((v+w) / u)) << std::endl;

  v += w;
  std::cout << "v += w,   v = " << v << " should be: [1,1,0]" << std::endl;

  v *= u;
  std::cout << "v *= u,   v = " << v << " should be: [1,2,0]" << std::endl;

  v /= u;
  std::cout << "v /= u,   v = " << v << " should be: [1,1,0]" << std::endl;

  v -= w;
  std::cout << "v -= w,   v = " << v << " should be: [1,0,0]" << std::endl;

  
  // methods
  std::cout << "u.squared_length() = " << u.squared_length() << " should be: 14" << std::endl;
  std::cout << "v.dot(u) = " << v.dot(u) << std::endl;
  std::cout << "v.dot(w) = " << v.dot(w) << std::endl;
  std::cout << "w.dot(v) = " << w.dot(v) << std::endl;
  std::cout << "v.normalize() = " << v.normalize() << " should be: [1,0,0]" << std::endl;
  std::cout << "u.normalize() = " << u.normalize() << std::endl;
  std::cout << "v.cross(w) = " << v.cross(w) << " should be: [0,0,1]" << std::endl;
  std::cout << "u.cross(w) = " << u.cross(w) << std::endl;
  std::cout << "u.cross(u) = " << u.cross(u) << std::endl;

  // Done.
  return 0;
}
