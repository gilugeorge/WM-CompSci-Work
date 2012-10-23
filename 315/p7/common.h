#ifndef COMMON_H

#define COMMON_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <fcntl.h>

/************************************************************
 All "messages" sent between server and clients in the
 distributed battleship system are in the format defined
 by struct bsmsg. The structure of the message is determined
 by the type field:

 type=A   WHO              - no other fields used
                           - sent from server to query for handle

 type=B   HANDLE           - data is the string handle for bs
			   - sent from client to convey handle)

 type=C   MATCH            - data is string handle of opponent
                           - sent from server to provide handle of opponent

 type=D   WHATMOVE         - server requests a move from a client

 type=E   MOVE             - data is int string indicating square into which
                             client is shooting

 type=F   OPPMOVE          - data is int string indicating square into which
                             opponent is shooting

 type=G   HITMISS          - data[0]=='H' -> last move was a hit
                             data[0]=='M' -> last move was a miss

 type=H   MOVEDONE         - client to server in response to HITMISS
                             data[0]=='V" -> I won on the last move

 type=I   SHUTDOWN         - server telling client that the game is over

************************************************************/

#define WHO      'A'
#define HANDLE   'B'
#define MATCH    'C'
#define WHATMOVE 'D'
#define MOVE     'E'
#define OPPMOVE  'F'
#define HITMISS  'G'
#define MOVEDONE 'H'
#define SHUTDOWN 'I'

struct bsmsg{
  char type;         /* Message type */
  char data[32];     /* depends on msg type */
};

#define SFILE "./serverloc"

void putmsg(int, struct bsmsg*);
void getmsg(int, struct bsmsg*);
#endif

