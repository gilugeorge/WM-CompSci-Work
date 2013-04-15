#ifndef _TIMER_H_
#define _TIMER_H_

#include <ctime>

class timer {
 public:
  /////////////////
  // Constructor //
  /////////////////
  timer(void);

  /////////////
  // Methods //
  /////////////
  void restart(void);
  double seconds(void) const;
  double miliseconds(void) const;

 private:
  //////////////////////////
  // Private Data Members //
  //////////////////////////
  clock_t _start;
};

#endif /* _TIMER_H_ */
