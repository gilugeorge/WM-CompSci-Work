#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void printBoard();
char mySpaces[25], oppSpaces[25];

int main(int argc, char *argv[]){

struct addrinfo hints, *res;
struct sockaddr_in *server;
int sockFD, ships = 0, oppShips = 0, place = 0;
char handReq[100], getShip[100], name[10], oppHand[10];
char sendShip[2], oppShip1[2], oppShip2[2], oppMove[2], input[2], temp[2];
//char moveFlag[2];//-1 first move, 0 normal gameplay, 1 you won, 2 opp has won
int OppShipLocations[2], myShips[2];
int i, checkScan, cTemp, move, gameFlag = 0, firstMove = -1;
int oppship1Flag = 0, oppship2Flag = 0;
char l1[25], l2[25];


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



	//basic setup memset, family, socktype
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	//get address info
	FILE *file = fopen("hostInfo.txt", "r");
	fscanf(file, "%s", l1);
	fscanf(file, "%s", l2);
	fclose(file);
	getaddrinfo(l1, l2, &hints, &res);
	server = (struct sockaddr_in *) res->ai_addr;

	//socket() and connect()
	sockFD = socket( res -> ai_family, res -> ai_socktype, 0 );
	if( sockFD == -1){
		perror("client: socket");
		exit(1);
	}

	if(connect(sockFD, (struct sockaddr *)server, sizeof(struct sockaddr_in)) == -1){
		close(sockFD);
		perror("client: connect");
		exit(1);
	}
	//check that 

if( tflag == 1){
	struct timeval tv;
  tv.tv_sec = atoll(tvalue);
	tv.tv_usec = 0;
  if (setsockopt(sockFD, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,  sizeof tv))
  {
    perror("setsockopt");
    return -1;
  }
}

	printf("Made it through the connect\n");

	//get handle **need to make sure that its max 10 letters**
	if(recv(sockFD, &handReq, sizeof(handReq), 0) <0 && tflag == 1){
		printf("Timeout, client closing\n");
		exit(0);
	}
	while(1){	
		printf("%s: ", handReq);
		fgets(name, 10, stdin);
		if(strlen(name) <= 0 || strlen(name) > 10){
			printf("Invalid Handle. Please Re-enter\n");
			do{
				cTemp = getchar();
			}while(cTemp != '\n' && cTemp!= EOF);
			continue;
		}else{
			printf("Your name is %s", name);
			send(sockFD, &name, sizeof(name), 0);
			break;
		}
	}//end get handle

	recv(sockFD, &oppHand, sizeof(oppHand), 0);
	printf("Your Opponent is: %s", oppHand);

	//populate spaces with empty space initially
	for(i = 0; i < 25; i++){
		mySpaces[i] = ' ';
		oppSpaces[i] = ' ';
	}


	recv(sockFD, &getShip, sizeof(getShip), 0);
////////////////////////////////Place Ships///////////////////////////////////////
	//home ship placement
	while(ships != 2){

		if(ships == 0){
			printf("%s", getShip);
			checkScan = scanf("%d", &place);
		}else if(ships == 1){
			printf("%s", getShip);
			checkScan = scanf("%d", &place);
		}//input section

		sprintf(temp, "%d", place);
		//ecape key and check for valid move
		if(strcmp(temp, "Q") == 0){
			gameFlag = -1;
			break;
		}else if(checkScan == 0){ //empty out the buffer and prompmt them to select again
			printf("Invalid Input. Press Enter and Select Another Space\n");
			do{
				cTemp = getchar();
			}while(cTemp != '\n' && cTemp!= EOF);
			continue;
		}else if(place < 0 || place > 24){
			printf("Invalid Position. Press Enter and Select Another Space\n");
			do{
				cTemp = getchar();
			}while(cTemp != '\n' && cTemp!= EOF);
			continue;
		}//checks section

		//place ship into board 
		if(ships == 0) {
			mySpaces[place] = 'S';
			myShips[0] = place;
			ships++;
			sprintf(sendShip, "%d", place);
			send(sockFD, sendShip, strlen(sendShip)+1, 0); /// *<<<<<<<<<<<added ships here
		}else{
			if(mySpaces[place] == 'S'){
				printf("You already have a ship there. Select another Spot\n");
			}else{
				mySpaces[place] = 'S';
				myShips[1] = place;
				ships++;
				sprintf(sendShip, "%d", place);
				send(sockFD, sendShip, strlen(sendShip)+1, 0); /// *<<<<<<<<<<<added ships here
			}
		}//add ship section
	}//ship placement end

//	printBoard();

	//receive ships and store in an int array
	recv(sockFD, &oppShip1, sizeof(oppShip1), 0);
	OppShipLocations[0] = atoi(oppShip1);
	recv(sockFD, &oppShip2, sizeof(oppShip2), 0);
	OppShipLocations[1] = atoi(oppShip2);
	//printf("Opp Ship Location 1: %s\n", oppShip1);
	//printf("Opp Ship Location 2: %s\n", oppShip2);
	//printf("Opp Ship Locations: %d, %d\n", OppShipLocations[0], OppShipLocations[1]);


//////////////////////////End Setup - Begin Game///////////////////////////////////////
while(gameFlag == 0){
	if(firstMove == -1){//during first move
		firstMove = 0;
	}else{
		//recv information, check if there is a quit or end game section here
		recv(sockFD, &oppMove, sizeof(oppMove), 0);
		if(strcmp(oppMove, "Q") == 0){//if the opponent has quit
			gameFlag = -1;
		}else if(atoi(oppMove) == myShips[0] || atoi(oppMove) == myShips[1]){
			ships--;
			printf("Opponent has Hit your Ship!\n");
			mySpaces[atoi(oppMove)] = '*';
		}else if(strcmp(oppMove, "-4") == 0){
			printf("Oh No! All your ships have sunk! You Lose!\n");
			gameFlag = -5;
			break;
		}else{
			printf("Opponent has Missed your Ship!\n");
			mySpaces[atoi(oppMove)] = '@';
		}

		//check ships number
		if(ships == 0){
			gameFlag = -4;
		}
	}//end recv section

//print board
printBoard();

//do attack and check statements
	while(gameFlag == 0){
		printf("Where would you like to attack (choose from square 0-24): ");
		checkScan = scanf("%s", input);
		//check for valid input
		if(strcmp(input, "Q") == 0){
			break;
		}else if(strcmp(input, "0") == 0){
			move = 0;
		}else if(atoi(input) > 0 && atoi(input) < 25){
			move = atoi(input);
		}else{
			printf("Invalid Input, Choose Again!\n");
			continue;
		}

		//ecape key and check for valid move
		if(move < 0 || move > 24){
			printf("Invalid attack. Select Another Space\n");
			continue;
		}if(checkScan == 0){ //empty out the buffer and prompmt them to select again
			printf("Not A Number. Select Another Space\n");
			continue;
		}

		//check if attack hit anything
		if(move == OppShipLocations[0]){
			if(oppship1Flag == 0){
				printf("HIT!\n");
				oppSpaces[move] = '*';
				oppShips--;
				oppship1Flag = -1;
				break;
			}else{
				printf("Already shot here! Select another space\n");
				continue;
			}
		}else if(move == OppShipLocations[1]){
			if(oppship2Flag == 0){
				printf("HIT!\n");
				oppSpaces[move] = '*';
				oppShips--;
				oppship2Flag = -1;
				break;
			}else{
				printf("Already shot here! Select another space\n");
				continue;
			}
		}else{
			printf("Miss!\n");
			oppSpaces[move] =  '@';
			break;
		}
		if(oppShips == 0){
			gameFlag = -3;
		}
	}//while() attack statements

//send attacks or statements to server
	if(strcmp(input, "Q") == 0){
		//end game here
		gameFlag = -2;
		send(sockFD, &input, sizeof(input), 0);
		break;
	}else if(gameFlag == -3){//you've won the game
		send(sockFD, &input, sizeof(input), 0);
		break;
	}

send(sockFD, &input, sizeof(input), 0);

}//while(1)

//////////////////end game statements here////////////////////////



if(gameFlag == -1){
	printf("The Opponent has Quit and you have Won!\n");
}else if(gameFlag == -2){
	printf("You have Quit and Lost the Game!\n");
}else if(gameFlag == -3){
	printf("\nCongratulations! You have Won!\n");
	send(sockFD, "-3", sizeof("-3"), 0);
}else if(gameFlag == -4){
	printf("Oh No! All your ships have sunk! You Lose!\n");
	send(sockFD, "-4", sizeof("-4"), 0);
}


return 0;
}//bs


/*Print Board function
*
**/
void printBoard(){
	//code to print home board
	int i, x = 0;

	printf("\n HOME		\n");
	for(i = 0; i < 11; i++){
		if(i % 2 == 0){
			printf("+-+-+-+-+-+\n");
		}else{
			printf("|%c|%c|%c|%c|%c|\n",mySpaces[x],mySpaces[x+1],mySpaces[x+2],mySpaces[x+3],mySpaces[x+4]);
			x += 5;
		}
	}//for

	//code to print shots board
	printf("\n Shots	\n");
	x = 0;
	for(i = 0; i < 11; i++){
		if(i % 2 == 0){
			printf("+-+-+-+-+-+\n");
		}else{
			printf("|%c|%c|%c|%c|%c|\n",oppSpaces[x],oppSpaces[x+1],oppSpaces[x+2],oppSpaces[x+3],oppSpaces[x+4]);
			x += 5;
		}
	}//for
}//printBoard






/*
	*char name[10];
	char mySpaces[25], oppSpaces[25], input[2];
	int i, move, checkScan, cTemp;
	int x = 0;
	int ships = 0;
	int oppShips = 0;
	int place = 0;

*	//get handle **need to make sure that its max 10 letters**
*	while(1){	
*		printf("What is your Player Name (max 10 letters): ");
*		scanf("%s", name);
*		if(strlen(name) <= 0 || strlen(name) > 10){
*			printf("Invalid Handle. Please Re-enter\n");
*			continue;
*		}else{
*			printf("Your name is %s\n\n", name);
*			break;
*		}
*	}//end get handle

	//populate spaces with empty space initially
	for(i = 0; i < 25; i++){
		mySpaces[i] = ' ';
		oppSpaces[i] = ' ';
	}

////////////////////////////////Place Ships///////////////////////////////////////
	//home ship placement
	while(ships != 2){
		//clear buffer
		do{
			cTemp = getchar();
		}while(cTemp != '\n' && cTemp!= EOF);


		if(ships == 0){
			printf("Where would you like to place your first ship (0-24): ");
			checkScan = scanf("%d", &place);
		}else if(ships == 1){
			printf("Where would you like to place your second ship (0-24): ");
			checkScan = scanf("%d", &place);
		}//input section

		//ecape key and check for valid move
		if(place == -1){
			break;
		}else if(checkScan == 0){ //empty out the buffer and prompmt them to select again
			printf("Invalid Input. Press Enter and Select Another Space\n");
			do{
				cTemp = getchar();
			}while(cTemp != '\n' && cTemp!= EOF);
			continue;
		}else if(place < 0 || place > 24){
			printf("Invalid Position. Press Enter and Select Another Space\n");
			do{
				cTemp = getchar();
			}while(cTemp != '\n' && cTemp!= EOF);
			continue;
		}//checks section

		//place ship into board 
		if(ships == 0) {
			mySpaces[place] = 'S';
			ships++;
		}else{
			if(mySpaces[place] == 'S'){
				printf("You already have a ship there. Select another Spot\n");
			}else{
				mySpaces[place] = 'S';
				ships++;
			}
		}//add ship section
	}//ship placement end

	// *clear out the buffer
		do{
			cTemp = getchar();
		}while(cTemp != '\n' && cTemp!= EOF);

	//Opp ship placement ****this section is for this test only
	while(oppShips != 2){

		if(oppShips == 0){
			printf("Where would you like to place your first ship (0-24): ");
		}else if(oppShips == 1){
			printf("Where would you like to place your second ship (0-24): ");
		}//input section

		checkScan = scanf("%d", &place);
		//ecape key and check for valid move
		if(place == -1){
			break;
		}else if(checkScan == 0){ //empty out the buffer and prompmt them to select again
			printf("Invalid Input. Select Another Space\n");
			do{
				cTemp = getchar();
			}while(cTemp != '\n' && cTemp!= EOF);
			continue;
		}else if(place < 0 || place > 24){
			printf("Invalid Position. Select Another Space\n");
			continue;
		}//checks section

		//place ship into board 
		if(oppShips == 0) {
			oppSpaces[place] = 'S';
			oppShips++;
		}else{
			if(oppSpaces[place] == 'S'){
				printf("You already have a ship there. Select another Spot\n");
			}else{
				oppSpaces[place] = 'S';
				oppShips++;
			}
		}//add ship section
	}//ship placement end

////////////////////////////////Print Boards///////////////////////////////////////
	//code to print home board
	printf("\n HOME		\n");
	for(i = 0; i < 11; i++){
		if(i % 2 == 0){
			printf("+-+-+-+-+-+\n");
		}else{
			printf("|%c|%c|%c|%c|%c|\n",mySpaces[x],mySpaces[x+1],mySpaces[x+2],mySpaces[x+3],mySpaces[x+4]);
			x += 5;
		}
	}//for
	
	//code to print shots board
	printf("\n Shots	\n");
	x = 0;
	for(i = 0; i < 11; i++){
		if(i % 2 == 0){
			printf("+-+-+-+-+-+\n");
		}else{
			printf("|%c|%c|%c|%c|%c|\n",oppSpaces[x],oppSpaces[x+1],oppSpaces[x+2],oppSpaces[x+3],oppSpaces[x+4]);
			x += 5;
		}
	}//for


////////////////////////////////Deal With Moves///////////////////////////////////////
	while(oppShips > 0 && ships > 0){
		printf("Where would you like to attack (choose from square 0-24): ");
		checkScan = scanf("%s", input);
		//printf("move: %d\n", move);
		
		if(strcmp(input, "Q") == 0){
			break;
		}else if(strcmp(input, "0") == 0){
			move = 0;
		}else if(atoi(input) > 0 && atoi(input) < 25){
			move = atoi(input);
		}else{
			printf("Invalid Input, Choose Again!\n");
			continue;
		}

		//ecape key and check for valid move
		if(move == -1){
			break;
		}else if(move < 0 || move > 24){
			printf("Invalid attack. Select Another Space\n");
			continue;
		}if(checkScan == 0){ //empty out the buffer and prompmt them to select again
			printf("Not A Number. Select Another Space\n");
			do{
				cTemp = getchar();
			}while(cTemp != '\n' && cTemp!= EOF);
			continue;
		}
*/
/*
		//check that this space hasn't been attacked
		if(oppSpaces[move] == '@'){
			printf("Already shot here! Select another space\n");
			continue;
		}else if(oppSpaces[move] == 'S'){ //this part will have to be taken out ****
			printf("HIT!\n");
			oppSpaces[move] = '*';
			oppShips--;
		}else if(oppSpaces[move] == '*'){
			printf("Ship Already Destroyed!\n");
			continue;
		}else{
			printf("Miss!\n");
			oppSpaces[move] =  '@';
		}

		//code to print home board
		x = 0;
		printf("\n HOME		\n");
		for(i = 0; i < 11; i++){
			if(i % 2 == 0){
				printf("+-+-+-+-+-+\n");
			}else{
				printf("|%c|%c|%c|%c|%c|\n",mySpaces[x],mySpaces[x+1],mySpaces[x+2],mySpaces[x+3],mySpaces[x+4]);
				x += 5;
			}
		}//for
	
		//code to print shots board
		printf("\n Shots	\n");
		x = 0;
		for(i = 0; i < 11; i++){
			if(i % 2 == 0){
				printf("+-+-+-+-+-+\n");
			}else{
				printf("|%c|%c|%c|%c|%c|\n",oppSpaces[x],oppSpaces[x+1],oppSpaces[x+2],oppSpaces[x+3],oppSpaces[x+4]);
				x += 5;
			}
		}//for
	}// *end deal with moves section*


//end statement prints
if(oppShips == 0){
	printf("\nCongratulations! You have Won!\n");
}else{
	printf("\nSorry! You have Lost!\n");
}

*/
