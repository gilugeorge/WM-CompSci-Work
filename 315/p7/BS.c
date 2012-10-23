/************************************************************************
 			     BS.c       			         
 Castrated BS server. Assumes completely well-behaved clients.
 The server is a glorified messenger boy. No real intelligence.

 Phil Kearns							         
 April 12, 1998						         
 								         
*************************************************************************/

#include "common.h"

int
main(argc,argv)
int argc; char **argv;
{
  int listener;  /* fd for socket on which we get connection requests */
  int fd0, fd1;  /* fds for sockets onto VCs to clients */
  struct sockaddr_in s1, addr0, addr1;
  socklen_t length;
  int lport, sfile, i;
  char hostid[128], handle0[32], handle1[32];
  struct bsmsg outmsg, inmsg;

  if (argc != 1) {
    fprintf(stderr,"BS:usage is BS\n");
    exit(1);
  }

  if ( (sfile = open(SFILE, O_RDWR|O_CREAT|O_TRUNC, 0644)) < 0) {
    perror("BS:sfile");
    exit(1);
  }

  if (gethostname(hostid,128) < 0){
    perror("BS:gethostname");
        exit(1);
  }

  i=0;
  while (hostid[i] != '\0')
    write(sfile,&hostid[i++], 1);
  write(sfile,"\0", 1);

  if ( (listener = socket( AF_INET, SOCK_STREAM, 0 )) < 0 ) {
    perror("BS:socket");
    exit(1);
  }

  bzero((char *) &s1, sizeof(s1));
  s1.sin_family = AF_INET;
  s1.sin_addr.s_addr = INADDR_ANY;  /* Any of this host's interfaces is OK. */
  s1.sin_port = 0;                  /* bind() will gimme unique port. */
  if (bind(listener, (struct sockaddr *) &s1, sizeof(s1)) < 0) {
    perror("BS:bind");
    exit(1);
  }

  length = sizeof(s1);
  if (getsockname(listener, (struct sockaddr *) &s1, &length) < 0) {
    perror("BS:getsockname");
    exit(1);
  }
  lport = s1.sin_port;
#ifdef DEBUG
  fprintf(stderr,"Assigned port is %d\n",lport);
#endif
  write(sfile, &lport, sizeof(int));
  close(sfile);

  listen(listener,5);

  length = sizeof(addr0);
  if ((fd0 = accept(listener, (struct sockaddr *) &addr0, &length)) < 0) {
    perror("BS:accept Player0");
    exit(1);
  }
#ifdef DEBUG
  fprintf(stderr,"BS: Player0 connected"); 
#endif

  /* Send WHO to Player0 */

  bzero((char *)&outmsg, sizeof(outmsg));
  outmsg.type = WHO;
  putmsg(fd0, &outmsg);

  /* Await HANDLE from Player0 */

  bzero((char *)&inmsg, sizeof(inmsg));
  getmsg(fd0, &inmsg);
  if (inmsg.type != HANDLE) {
    fprintf(stderr, "HANDLE expected, not received\n");
    exit(1);
  }
  strncpy(handle0, inmsg.data, 31);
  handle0[31] = '\0';
#ifdef DEBUG
  fprintf(stderr, "Player0 handle is %s\n", handle0);
#endif

  length = sizeof(addr1);
  if ((fd1 = accept(listener, (struct sockaddr *) &addr1, &length)) < 0) {
    perror("BS:accept Player1");
    exit(1);
  }
#ifdef DEBUG
  fprintf(stderr,"BS: Player1 connected"); 
#endif

  /* Send WHO to Player1 */

  bzero((char *)&outmsg, sizeof(outmsg));
  outmsg.type = WHO;
  putmsg(fd1, &outmsg);

  /* Await HANDLE from Player1 */

  bzero((char *)&inmsg, sizeof(inmsg));
  getmsg(fd1, &inmsg);
  if (inmsg.type != HANDLE) {
    fprintf(stderr, "HANDLE expected, not received\n");
    exit(1);
  }
  strncpy(handle1, inmsg.data, 31);
  handle1[31] = '\0';
#ifdef DEBUG
  fprintf(stderr, "Player1 handle is %s\n", handle1);
#endif


  /* Send MATCH to Player0 */

  bzero((char *)&outmsg, sizeof(outmsg));
  outmsg.type=MATCH;
  strncpy(outmsg.data, handle1, 31);
  outmsg.data[31] = '\0';
  putmsg(fd0, &outmsg);

  /* Send MATCH to Player1 */    

  bzero((char *)&outmsg, sizeof(outmsg));
  outmsg.type=MATCH;
  strncpy(outmsg.data, handle0, 31);
  outmsg.data[31] = '\0';
  putmsg(fd1, &outmsg);

  /* Everything is set up, play the game */

  while(1) {
    
    /* Send  WHATMOVE to Player0 */

    bzero((char *)&outmsg, sizeof(outmsg));
    outmsg.type=WHATMOVE;
    putmsg(fd0, &outmsg);

    /* Await MOVE from Player0 */

    bzero((char *)&inmsg, sizeof(inmsg));  
    getmsg(fd0, &inmsg);
    if (inmsg.type != MOVE) {
      fprintf(stderr, "MOVE expected, not received\n");
      exit(1);
    }
#ifdef DEBUG
    fprintf(stderr,"Player0 shoots at %s\n", inmsg.data);
#endif
    /* Forward the move to Player1 */
    
    bzero((char *)&outmsg, sizeof(outmsg));
    outmsg.type=OPPMOVE;
    bcopy((void *)inmsg.data, (void *)outmsg.data, 32);
    putmsg(fd1, &outmsg); 

    /* Await result from Player1 */

    bzero((char *)&inmsg, sizeof(inmsg));  
    getmsg(fd1, &inmsg);
    if (inmsg.type != HITMISS) {
      fprintf(stderr, "HITMISS expected, not received\n");
      exit(1);
    }    
#ifdef DEBUG
    fprintf(stderr,"Player0 shot was %c\n", inmsg.data[0]);
#endif

    /* Forward the result to Player0 */
    bzero((char *)&outmsg, sizeof(outmsg));
    outmsg.type=HITMISS;
    bcopy((void *)inmsg.data, (void *)outmsg.data, 32);
    putmsg(fd0, &outmsg); 

    /* At this point, Player0 has shot and gotten the result. */

    /* Await MOVEDONE from Player0 */
    bzero((char *)&inmsg, sizeof(inmsg));  
    getmsg(fd0, &inmsg);
    if (inmsg.type != MOVEDONE) {
      fprintf(stderr, "MOVEDONE expected, not received\n");
      exit(1);
    }        
    
    /* Did Player0 win? */
    if (inmsg.data[0]=='V') {
      bzero((char *)&outmsg, sizeof(outmsg));
      outmsg.type=SHUTDOWN;
      putmsg(fd0, &outmsg);
      putmsg(fd1, &outmsg);
      exit(0);
    }

    /* Send  WHATMOVE to Player1 */
    bzero((char *)&outmsg, sizeof(outmsg));
    outmsg.type=WHATMOVE;
    putmsg(fd1, &outmsg);

    /* Await MOVE from Player1 */
    bzero((char *)&inmsg, sizeof(inmsg));  
    getmsg(fd1, &inmsg);
    if (inmsg.type != MOVE) {
      fprintf(stderr, "MOVE expected, not received\n");
      exit(1);
    }
#ifdef DEBUG
    fprintf(stderr,"Player1 shoots at %s\n", inmsg.data);
#endif
    /* Forward the move to Player0 */
    
    bzero((char *)&outmsg, sizeof(outmsg));
    outmsg.type=OPPMOVE;
    bcopy((void *)inmsg.data, (void *)outmsg.data, 32);
    putmsg(fd0, &outmsg); 

    /* Await result from Player0 */

    bzero((char *)&inmsg, sizeof(inmsg));  
    getmsg(fd0, &inmsg);
    if (inmsg.type != HITMISS) {
      fprintf(stderr, "HITMISS expected, not received\n");
      exit(1);
    }    
#ifdef DEBUG
    fprintf(stderr,"Player1 shot was %c\n", inmsg.data[0]);
#endif

    /* Forward the result to Player1 */
    
    bzero((char *)&outmsg, sizeof(outmsg));
    outmsg.type=HITMISS;
    bcopy((void *)inmsg.data, (void *)outmsg.data, 32);
    putmsg(fd1, &outmsg);

    /* At this point, Player1 has shot and gotten the result. */

    /* Await MOVEDONE from Player1 */
    bzero((char *)&inmsg, sizeof(inmsg));  
    getmsg(fd1, &inmsg);
    if (inmsg.type != MOVEDONE) {
      fprintf(stderr, "MOVEDONE expected, not received\n");
      exit(1);
    }        
    
    /* Did Player1 win? */
    if (inmsg.data[0]=='V') {
      bzero((char *)&outmsg, sizeof(outmsg));
      outmsg.type=SHUTDOWN;
      putmsg(fd0, &outmsg);
      putmsg(fd1, &outmsg);
      exit(0);
    }

  } /* while */

  /* Match is over, last commo to shut down both clients */

  /* Send SHUTDOWN to Player0 */

  bzero((char *)&outmsg, sizeof(outmsg));
  outmsg.type = SHUTDOWN;
  putmsg(fd0, &outmsg);

  /* Send SHUTDOWN to Player1 */

  bzero((char *)&outmsg, sizeof(outmsg));
  outmsg.type = SHUTDOWN;
  putmsg(fd1, &outmsg);

  /* The game is finished */ 
  return(0);

}


