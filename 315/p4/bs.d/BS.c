#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>

	void usrhandler (){
		printf("SIGHUP Issue\n");
		exit(1);
	}

int main(int argc, char *argv[]){
signal(SIGHUP, usrhandler);
int request, bcheck, p1 = -1, p2 = -1;

int qflag = 0, tflag = 0, pflag = 0;
char *pvalue = NULL;
char *tvalue = NULL;
int index;
int c;
     
opterr = 0;
     
while ((c = getopt (argc, argv, "qt:p:")) != -1)
 switch (c)
   {
   case 'q':
     qflag = 1;
     break;
   case 't':
     tflag = 1;
     tvalue = optarg;
     break;
   case 'p':
     pflag = 1;
     pvalue = optarg;
     break;
   case '?':
     if (isprint (optopt))
       fprintf (stderr, "Unknown option `-%c'.\n", optopt);
     else
       fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
     return 1;
   default: break;
   }

// printf ("qflag = %d,  tvalue = %s, pvalue = %s\n", qflag, tvalue, pvalue);
 for (index = optind; index < argc; index++)
   printf ("Non-option argument %s\n", argv[index]);






if(argc==1){
	struct sockaddr_in *localaddr;
	struct addrinfo hints, *res;
	struct sockaddr_storage p1_addr, p2_addr;
	socklen_t p1_addr_size, p2_addr_size, length;
	struct timeval tv;
	char p1ship1[2], p1ship2[2], p2ship1[2], p2ship2[2];
	char p1Move[2], p2Move[2];
	char p1Name[10], p2Name[10];
//	char gameStart[]= "-1";
//	char trans[2];
	char handReq[]= "Please enter a handle (up to 10 charecters taken)";
	char boardReq[]= "Where would you like to place your ship (0-24): ";
//	char endMsgW[] = "You have Won!";
//	char endMsgL[] = "You have Lost!";
	int gameFlag = 0, turn = 1;
	char hostname[25];


	tv.tv_sec= 2;
	fd_set readfds;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family= AF_INET;
	hints.ai_socktype= SOCK_STREAM;

	gethostname(hostname, sizeof(hostname));
	getaddrinfo(hostname, NULL, &hints, &res);
	localaddr = (struct sockaddr_in *) res->ai_addr;

	request = socket(res->ai_family, res->ai_socktype, 0);
	if ( request < 0 ) { //check that the socket is created correctly
		perror("inet_rstream:socket");
		exit(1);
	}

	bcheck = bind(request, (struct sockaddr *)localaddr, sizeof(struct sockaddr_in));
	if (bcheck < 0) { //check that it binds correctly
		perror("inet_rstream:bind");
		exit(1);
	}

	length = sizeof(struct sockaddr_in);
	if(getsockname(request, (struct sockaddr *) localaddr, &length) < 0){
		perror("inet_rstream getsockname");
		exit(1);
	}

	FILE *file = fopen("hostInfo.txt", "w");
	gethostname(hostname, sizeof(hostname));
	fprintf(file, "%s\n", hostname);
	fprintf(file, "%d\n", ntohs(localaddr->sin_port));
	fclose(file);

	listen(request, 8);
	FD_SET(request, &readfds);

	printf("Made a connection!!!\n");

	while(p1 == -1 || p2 == -1){
		if(select(request+1, &readfds, NULL, NULL, NULL) > 0){
			if(p1 == -1){
				p1_addr_size = sizeof p1_addr;
				p1 = accept(request, (struct sockaddr *)&p1_addr, &p1_addr_size);
			}else{
				p2_addr_size = sizeof p2_addr;
				p2 = accept(request, (struct sockaddr *)&p2_addr, &p2_addr_size);
			}
		}//end select
	}//end while

	//ask for handles and send to other player
	send(p1, &handReq, sizeof(handReq), 0);
	send(p2, &handReq, sizeof(handReq), 0);
	recv(p1, &p1Name, sizeof(p1Name), 0);
	recv(p2, &p2Name, sizeof(p2Name), 0);
	send(p1, &p2Name, sizeof(p2Name), 0);
	send(p2, &p1Name, sizeof(p1Name), 0);
	
	//Ask for ship position
	send(p1, &boardReq, sizeof(boardReq), 0);

	//read in ship positions
	recv(p1, &p1ship1, sizeof(p1ship1), 0);
	recv(p1, &p1ship2, sizeof(p1ship2), 0);
	//printf("P 1 Position 1: %s\n", p1ship1);
	//printf("P 1 Position 2: %s\n", p1ship2);


	send(p2, &boardReq, sizeof(boardReq), 0);
	recv(p2, &p2ship1, sizeof(p2ship1), 0);
	recv(p2, &p2ship2, sizeof(p2ship2), 0);
	//printf("P 2 Position 1: %s\n", p2ship1);
	//printf("P 2 Position 2: %s\n", p2ship2);

	//send ship positions to opponent
	send(p1, &p2ship1, sizeof(p1ship1), 0);
	send(p2, &p1ship1, sizeof(p2ship1), 0);
	send(p1, &p2ship2, sizeof(p1ship2), 0);
	send(p2, &p1ship2, sizeof(p2ship2), 0);

	//first set of moves	
	recv(p1, &p1Move, sizeof(p1Move), 0);
	recv(p2, &p2Move, sizeof(p2Move), 0);
	//printf("p1 move 1: %s\n", p1Move);	
	//printf("p2 move 1: %s\n", p2Move);

	while(gameFlag == 0){

		if(turn == 1){
			send(p1, &p2Move, sizeof(p2Move), 0);
			recv(p1, &p1Move, sizeof(p1Move), 0);
			turn = 0;

			if(strcmp(p1Move, "Q") == 0){
				gameFlag = -1;
			}else if(strcmp(p1Move, "-3") == 0){
				send(p2, "-4", sizeof("-4"), 0);
				break;
			}

		}else{ //when its 2nd players turn
			send(p2, &p1Move, sizeof(p1Move), 0);
			recv(p2, &p2Move, sizeof(p2Move), 0);
			turn = 1;

			if(strcmp(p2Move, "Q") == 0){
				gameFlag = -1;
			}else if(strcmp(p2Move, "-3") == 0){
				send(p1, "-4", sizeof("-4"), 0);
				break;
			}
		}
	}//end gameFlag while

	memset(&p1_addr_size, 0, sizeof(p1_addr_size));
	memset(&p2_addr_size, 0, sizeof(p2_addr_size));
	memset(&p1_addr, 0, sizeof(p1_addr));
	memset(&p2_addr, 0, sizeof(p2_addr));
	p1 = -1;
	p2 = -1;
}else if(argc == 2){//write code to take care of password mode/query mode



}


return 0;
}//main
