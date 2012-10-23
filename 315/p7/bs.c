/************************************************************************
 			         bs.c
 Simple (simplistic?) battleship client. Relies on server to
 set up game and provide all client-to-client commo.

 Phil Kearns
 April 12, 1999

************************************************************************/

#include "common.h"
#include "child.h"

void printgame();

char board[25]; /* Very small 5x5 game board. */
char shots[25]; /* Shots at the opponent. */
int childpid, bell = 0;
FILE *read_from, *write_to;

int main(argc,argv)
int argc; char **argv;
{
  char hostid[128], handle[32], opphandle[32];
  int rport;
  int sock, sfile;
  struct sockaddr_in remote;
  struct hostent *h;
  int loc1, loc2, num, i, shot, oppshot, sunk, notfinished;
  struct bsmsg inmsg, outmsg;

  if (argc != 1) {
    fprintf(stderr,"bs:usage is bs\n");
    exit(1);
  }

  /* Get host,port of server from file. */

  if ( (sfile = open(SFILE, O_RDONLY)) < 0) {
    perror("bs:sfile");
    exit(1);
  }
  i=0;
  while (1) {
    num = read(sfile, &hostid[i], 1);
    if (num == 1) {
      if (hostid[i] == '\0') break;
      else i++;
    }
    else {
      fprintf(stderr, "bs:error reading hostname\n");
      exit(1);
    }
  }
  if (read(sfile, &rport, sizeof(int)) != sizeof(int)) {
    fprintf(stderr, "bs:error reading port\n");
      exit(1);
  }
  close(sfile);
#ifdef DEBUG
  fprintf(stderr,"Server host=%s, port=%d\n", hostid, rport);
#endif

  /* Got the info. Connect. */

  if ( (sock = socket( AF_INET, SOCK_STREAM, 0 )) < 0 ) {
    perror("bs:socket");
    exit(1);
  }

  bzero((void *) &remote, sizeof(remote));
  remote.sin_family = AF_INET;
  if ((h = gethostbyname(hostid)) == NULL) {
    perror("bs:gethostbyname");
    exit(1);
  }
  bcopy((void *)h->h_addr, (void *)&remote.sin_addr, h->h_length);
  remote.sin_port = rport;
  if ( connect(sock, (struct sockaddr *)&remote, sizeof(remote)) < 0) {
    perror("bs:connect");
    exit(1);
  }

#ifdef DEBUG
  fprintf(stderr,"Connected to Server host=%s, port=%d\n", hostid, rport);
#endif

  /* We're connected to the server. Engage in the prescribed dialog */

  /* Await WHO */

  bzero((char *)&inmsg, sizeof(inmsg));  
  getmsg(sock, &inmsg);
  if (inmsg.type != WHO) {
    fprintf(stderr, "WHO expected, not received\n");
    exit(1);
  }
  
  /* Send HANDLE */

  printf("Enter handle (31 char max):");
  fgets(handle, 31, stdin);

	childpid = start_child("wish",&read_from,&write_to);	
	/* Tell wish to read the init script */
	fprintf (write_to, "source bs.tcl\n");
	fprintf(write_to, ".c itemconfigure handle -text Handle:%s\n", handle);

  bzero((void *)&outmsg, sizeof(outmsg));
  outmsg.type = HANDLE;
  strncpy(outmsg.data, handle, 31); outmsg.data[31] = '\0';
  putmsg(sock, &outmsg);

  /* Await MATCH */
	fprintf(write_to, ".s itemconfigure status -text AwaitingMatch\n");
  bzero((char *)&inmsg, sizeof(inmsg));
  getmsg(sock, &inmsg);
  if (inmsg.type != MATCH) {
    fprintf(stderr, "MATCH expected, not received\n");
    exit(1);
  }
  strncpy(opphandle, inmsg.data, 31); opphandle[31] = '\0';


	

	fprintf(write_to, ".y itemconfigure opphandle -text OppenentHandle:%s\n", opphandle);
#ifdef DEBUG
  fprintf(stderr,"Opponent's handle is %s\n", opphandle);
#endif
  //fprintf(write_to, ".c itemconfigure opphandle -text %s", opphandle);
  /* Got a match, set up board/shots */

/************************************************************
Board codes: (the board tracks your ships and your opponent's shots)
  board[i] (0<=i<=24) is a ' ' (blank character) if user has
    not placed a ship in that square and the opponent has not
    fired a shot into that square.
  board[i] (0<=i<=24) is an 'S' if user has placed a ship in
    square i and the opponent has not fired into that square.
  board[i] (0<=i<=24) is an 's' if user has placed a ship in
    square i and the opponent has fired into that square.
    The ship in this square has been sunk.
  board[i] (0<=i<=24) is an '@' if user has not placed a ship
    in square i and the opponent has fired a shot into that
    square. This was a miss by the opponent.

Shots codes: (shots tracks the result of our shots)
  shots[i] (0<=i<=24) is a ' ' (blank) if you have not fired
    into this square.
  shots[i] (0<=i<=24) is an '@' if you have fired into this
    square and have missed.
  shots[i] (0<=i<=24) is an 's' if you have fired into this
    square and have sunk an opponent's ship in this square.
************************************************************/
 
  sunk = 0; notfinished = 1;
	//if(childpid < 0) exit(1);

  for(i=0; i<25; i++) {
		board[i]=shots[i]=' ';
	}

  printf("Enter 1st ship location:");
	while(1){
		fprintf(write_to, ".s itemconfigure status -text PlaceShip1\n");
		fscanf(read_from, "%d", &loc1);
		board[loc1] = 'S';
		fprintf(write_to, ".s itemconfigure status -text PlaceShip2\n");
		fscanf(read_from, "%d", &loc2);
		board[loc2] = 'S';
		break;
	}//retrieve ship locations


/*  while (1) {
    scanf("%d", &loc1);
    if ((loc1 < 0) || (loc1 > 24)) {
      printf("Invalid location (%d). Try again.\n", loc1);
    }
    else {
      board[loc1]='S';
      break;
    }
  }
*/
#ifdef DEBUG
  fprintf(stderr,"First ship at %d\n", loc1);
#endif
    
  printf("Enter 2nd ship location:\n");
  /*while (1) {
    scanf("%d", &loc2);
    if ((loc2 < 0) || (loc2 > 24)) {
      printf("Invalid location (%d). Try again.\n", loc2);
      continue;
    }
    if (loc1 == loc2) {
      printf("Cannot have 2 ships at same location (%d). Try again.\n", loc2);
      continue;
    }
    board[loc2]='S';
    break;
  }*/
#ifdef DEBUG
  fprintf(stderr,"Second ship at %d\n", loc2);
#endif   
  printgame();
  while(notfinished) {

    /* Await WHATMOVE or OPPMOVE */
    bzero((char *)&inmsg, sizeof(inmsg));  
    getmsg(sock, &inmsg);
		fprintf(write_to, ".s itemconfigure status -text AwaitingOpponentMove\n");

    switch (inmsg.type) {
    case WHATMOVE:
      //printf("Shoot into square -->");
			fprintf(write_to, "if {$silence == 0} {bell}\n");
			fprintf(write_to, "set turn 1\n");
			fprintf(write_to, ".s itemconfigure status -text YourMove\n");
      while(1) {
				fscanf(read_from, "%d", &shot);
				printf("%d", shot);
				shots[shot] = '*';
				printgame();
				break;
      }
/*
        if ((shot < 0) || (shot > 24)) {
          printf("Invalid location (%d). Try again.\n", shot);
	  continue;
        }
	if (shots[shot] != ' ') {
	  printf("Already shot square (%d). Try again.\n", shot);
	  continue;
	}
	shots[shot] = '*';
	// printgame();
	break;
*/
char gB[10];
	switch(shot){
		  case 0: strcpy(gB, "mBZero"); break;
		  case 1: strcpy(gB, "mBOne"); break;
		  case 2: strcpy(gB, "mBTwo"); break;
		  case 3: strcpy(gB, "mBThree"); break;
		  case 4: strcpy(gB, "mBFour"); break;
		  case 5: strcpy(gB, "mBFive"); break;
		  case 6: strcpy(gB, "mBSix"); break;
		  case 7: strcpy(gB, "mBSeven"); break;
		  case 8: strcpy(gB, "mBEight"); break;
		  case 9: strcpy(gB, "mBNine"); break;
		  case 10: strcpy(gB, "mBTen"); break;
		  case 11: strcpy(gB, "mBEleven"); break;
		  case 12: strcpy(gB, "mBTwelve"); break;
		  case 13: strcpy(gB, "mBThirteen"); break;
		  case 14: strcpy(gB, "mBFourteen"); break;
		  case 15: strcpy(gB, "mBFifteen"); break;
		  case 16: strcpy(gB, "mBSixteen"); break;
		  case 17: strcpy(gB, "mBSeventeen"); break;
		  case 18: strcpy(gB, "mBEighteen"); break;
		  case 19: strcpy(gB, "mBNineteen"); break;
		  case 20: strcpy(gB, "mBTwenty"); break;
		  case 21: strcpy(gB, "mBTOne"); break;
		  case 22: strcpy(gB, "mBTTwo"); break;
		  case 23: strcpy(gB, "mBTThree"); break;
		  case 24: strcpy(gB, "mBTFour"); break;
	}

      /* Send details of shot to server */

      bzero((void *)&outmsg, sizeof(outmsg));
      outmsg.type = MOVE;
      snprintf(outmsg.data, 32, "%d", shot);
      putmsg(sock, &outmsg);

      /* Await result (hit/miss) of shot */

      bzero((char *)&inmsg, sizeof(inmsg));  
      getmsg(sock, &inmsg);      
      if (inmsg.type != HITMISS) {
        fprintf(stderr, "HITMISS expected, not received\n");
        exit(1);
      }
    
      if (inmsg.data[0] == 'H') {
				shots[shot] = 's';
				sunk++;
				fprintf(write_to, ".y itemconfigure %s -fill red\n", gB);
				fprintf(write_to, ".s itemconfigure waiting -text Hit!\n");
				fprintf(write_to, ".s itemconfigure status -text AwaitingOpponentMove\n");
				fprintf(write_to, ".s itemconfigure opp -text ~\n");
				printf("Sank a ship\n");
      } else {
				shots[shot] = '@';
				fprintf(write_to, ".s itemconfigure waiting -text Miss!\n");
				fprintf(write_to, ".s itemconfigure status -text AwaitingOpponentMove\n");
				fprintf(write_to, ".s itemconfigure opp -text ~\n");
				fprintf(write_to, ".y itemconfigure %s -fill blue\n", gB);
				printf("Missed\n");
      }
      printgame();

      /* Let server know if the last move won the game for me. */

      bzero((void *)&outmsg, sizeof(outmsg));
      outmsg.type = MOVEDONE;
      if (sunk == 2) outmsg.data[0]='V';
      else           outmsg.data[0]='N';
      putmsg(sock, &outmsg);
      break;

    case OPPMOVE:
			//fprintf(write_to, ".s itemconfigure status -text AwaitingOpponentMove\n");
      bzero((void *)&outmsg, sizeof(outmsg));
      outmsg.type = HITMISS;
      sscanf(inmsg.data,"%d",&oppshot);

			char mB[10];
				switch(oppshot){
						case 0: strcpy(mB, "mBZero"); break;
						case 1: strcpy(mB, "mBOne"); break;
						case 2: strcpy(mB, "mBTwo"); break;
						case 3: strcpy(mB, "mBThree"); break;
						case 4: strcpy(mB, "mBFour"); break;
						case 5: strcpy(mB, "mBFive"); break;
						case 6: strcpy(mB, "mBSix"); break;
						case 7: strcpy(mB, "mBSeven"); break;
						case 8: strcpy(mB, "mBEight"); break;
						case 9: strcpy(mB, "mBNine"); break;
						case 10: strcpy(mB, "mBTen"); break;
						case 11: strcpy(mB, "mBEleven"); break;
						case 12: strcpy(mB, "mBTwelve"); break;
						case 13: strcpy(mB, "mBThirteen"); break;
						case 14: strcpy(mB, "mBFourteen"); break;
						case 15: strcpy(mB, "mBFifteen"); break;
						case 16: strcpy(mB, "mBSixteen"); break;
						case 17: strcpy(mB, "mBSeventeen"); break;
						case 18: strcpy(mB, "mBEighteen"); break;
						case 19: strcpy(mB, "mBNineteen"); break;
						case 20: strcpy(mB, "mBTwenty"); break;
						case 21: strcpy(mB, "mBTOne"); break;
						case 22: strcpy(mB, "mBTTwo"); break;
						case 23: strcpy(mB, "mBTThree"); break;
						case 24: strcpy(mB, "mBTFour"); break;
				}



      if (board[oppshot] == 'S') {
				/* He hit my ship, dammit */
				board[oppshot]='s';
				outmsg.data[0]='H';
				fprintf(write_to, ".s itemconfigure opp -text OpponentSunkAShip\n");
				fprintf(write_to, ".c itemconfigure %s -fill red\n", mB);
				printf("HIT!\n");
      } else {
				board[oppshot]='@';
				outmsg.data[0]='M';
				fprintf(write_to, ".s itemconfigure opp -text OpponentMissed\n");
				fprintf(write_to, ".c itemconfigure %s -fill blue\n", mB);
				printf("miss\n");
      }
			memset(&oppshot, 0, sizeof(oppshot));
			
//			fprintf(write_to, "bell\n");

      printgame();
      putmsg(sock, &outmsg);
      break;

    case SHUTDOWN:
      notfinished = 0;
			//fprintf(write_to, "exit");
      break;

    default:
      fprintf(stderr, "Expected WHATMOVE/OPPMOVE/SHUTDOWN\n");
      break;

    } /* switch */

  } /* while */

  if (sunk == 2){
    printf("<HOMER>Woohoo</HOMER>\n");
		fprintf(write_to, ".s itemconfigure status -text YouWin!\n");
	}
  else{
    printf("Loser!\n");
		char l[] = "Loser";
		fprintf(write_to, ".s itemconfigure status -text YouLose!\n");
		fprintf(write_to, ".s itemconfigure text -text %s\n", l);
		//fprintf(write_to, "exit\n");
	}
	fprintf(write_to, "set done 1\n");

  return(0);
}

void printgame()
{
  int i,j;
  
  printf("   BOARD         SHOTS \n");
  printf("+-+-+-+-+-+   +-+-+-+-+-+\n");
    for (j=0; j<5; j++) {
      for (i=0; i<5; i++){
        printf("|%c",board[i+5*j]);
      }
      printf("|   ");
      for (i=0; i<5; i++){
        printf("|%c",shots[i+5*j]);
      }
      printf("|\n");
      printf("+-+-+-+-+-+   +-+-+-+-+-+\n");
    }
}
