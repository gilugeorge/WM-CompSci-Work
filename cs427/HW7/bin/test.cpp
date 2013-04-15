#include <iostream>

#include "material.h"
#include "triangleMesh.h"



int main(int argc, char** argv)
{
  material m;
  triangleMesh tm("geometry.obj", m);
  return 0;
}
