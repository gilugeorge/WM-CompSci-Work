#include <string>
#include <iostream>

#include "image.h"
#include "constants.h"

int main(int argc, char** argv)
{
  // parse command line
  if(argc != 3)
  {
    std::cout << "Usage: " << argv[0] << " <image A> <image B>" << std::endl;
    return -1;
  }

  std::string nameA(argv[1]);
  std::string nameB(argv[2]);

  // load images
  image imgA(nameA);
  image imgB(nameB);

  // check if both have the same dimension
  if(imgA.width() != imgB.width() || imgA.height() != imgB.height())
  {
    std::cout << " => Images differ in size: A=" << imgA << ", B=" << imgB << std::endl;
    return 0;
  }

  // compute the difference image
  image diff(imgA.width(), imgB.height());
  color avgDiff, maxDiff;
  unsigned long diffCount = 0;

  for(image::size_type y=0; y < diff.height(); y++)
    for(image::size_type x=0; x < diff.width(); x++)
    {
      // per pixel difference (absolute value)
      color diffColor = imgA(x,y) - imgB(x,y);
      diffColor.abs();
      
      // if different => update average and max
      if(diffColor.r > EPSILON || diffColor.g > EPSILON || diffColor.b > EPSILON)
      {
	diffCount++;
	avgDiff += diffColor;
	maxDiff = color(std::max(maxDiff.r, diffColor.r), std::max(maxDiff.g, diffColor.g), std::max(maxDiff.b, diffColor.b));
      }

      // store
      diff(x,y) = diffColor;
    }

  // output results if different
  if(diffCount != 0)
  {
    avgDiff /= diffCount;
    std::cout << " => There are " << diffCount << " pixels that differ." << std::endl;
    std::cout << "    Average difference: " << avgDiff << " [base 256: " << (avgDiff * 256.0f) << "]" << std::endl;
    std::cout << "    Maximum difference: " << maxDiff << " [base 256: " << (maxDiff * 256.0f) << "]" << std::endl;

    // write out difference image
    diff.save("diff.ppm");
  }

  // if equal, let the user know
  else {
    std::cout << " => Both images are equal.\r\n";
  }

  // Done.
  return 0;
}
