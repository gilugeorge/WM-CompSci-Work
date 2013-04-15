#include "timer.h"

/////////////////
// Constructor //
/////////////////
timer::timer(void)
{
  restart();
}



/////////////
// Methods //
/////////////
void timer::restart(void) 
{
  _start = clock();
}


double timer::seconds(void) const
{
  return (double)(clock() - _start) / (double)(CLOCKS_PER_SEC);
}


double timer::miliseconds(void) const
{
  return seconds() * 1000.0;
}
