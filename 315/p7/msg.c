/************************************************************************

 Functions for reading and writing "messages" of a given size
 over a TCP/IP virtual circuit.

 Specialized to use "battleship messages" (struct bsmsg).

 Phil Kearns							         
 April 12, 1999						         
 								         
*************************************************************************/

#include "common.h"

void
putmsg(s, m)
int s;              /* socket on which sending */
struct bsmsg *m;    /* pointer to the message to be sent */
{
  int bytes_sofar, to_go, num;
  char *addr;

  bytes_sofar = 0;
  to_go = sizeof(struct bsmsg);

  addr = (char *) m;   /* Isn't C wonderful? Let's pretend that
                          the struct bsmsg is a char array. */  
  while (to_go > 0) {
    num = write(s, &(addr[bytes_sofar]), to_go);
    if (num < 0) {
      perror("putmsg");
      exit(1);
    }
  to_go -= num; bytes_sofar += num;  
  }
}

void
getmsg(s, m)
int s;              /* socket on which receiving */
struct bsmsg *m;    /* container for the message */
{
  int bytes_sofar, to_go, num;
  char *addr;

  bytes_sofar = 0;
  to_go = sizeof(struct bsmsg);

  addr = (char *) m;   /* Isn't C wonderful? Let's pretend that
                          the struct bsmsg is a char array. */
  while (to_go > 0) {
    num = read(s, &(addr[bytes_sofar]), to_go);
    if (num < 0) {
      perror("getmsg");
          exit(1);
    }
    if (num == 0) {
      fprintf(stderr, "Unexpected EOF\n");
      exit(1);
    }
    to_go -= num; bytes_sofar += num;
  }
}
