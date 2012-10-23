#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/wait.h>

#define S2E_0 16
#define S2E_1 17
#define E2S_0 18
#define E2S_1 19
#define S2O_0 20
#define S2O_1 21
#define O2S_0 22
#define O2S_1 23

int h;

struct node {
	char word[1023]; 
	int letterCount;
	struct node *next;
	struct node *prev;
};

void doHandle(){
	h++;
}

int main(int argc, char *argv[]){
	//printf("in scanner\n");
	
	int y= 0;
	int i = 0;
	h = 0;
	char wtemp[1023];
	char fixedWord[1023];
	char rIn1[1023], rIn2[1023];

	//scan in file and take in individual words into a linked list
	while(scanf("%s", wtemp) != EOF){
		//create a new node and scan in word
		//printf("scanned a word ln 40\n");
		//numLetters = 0;
		y = 0;
		memset(&fixedWord[0], 0, sizeof(fixedWord));
		//remove punctuation and shift to all lowercase letters
		for(i = 0; i < strlen(wtemp); i++){ //**is this how the word ends? strcmp(wtemp[x], "\0") != 0
			//printf("Line 49 NumLetters: %d\n", y);
			

			if(ispunct(wtemp[i])){ //** does 0 mean that it is a punct?
				continue;
			}else if(isupper(wtemp[i]) ){
				fixedWord[y] = tolower(wtemp[i]);
				y++;
				continue;
			}else{
				fixedWord[y] = wtemp[i];
				y++;
			}
		}//while-edit
		//printf("Scanned String %s\n", wtemp);
		//printf("Editted String %s\n", fixedWord);

		if(y <= 0){
			printf("Input does not have letters\n");
			exit(1);
		}

		if(y % 2 == 0){ //send to even
			//printf("fixedWord to even is: %s , %d\n", fixedWord, y);
			write(S2E_1, &fixedWord, sizeof(fixedWord));

		}else{ //send to odd
			//printf("fixedWord to odd is: %s , %d\n", fixedWord, y);
			write(S2O_1, &fixedWord, sizeof(fixedWord));
		}

	}//while-scan
		//close pipes
		if (close(S2E_1) == -1){
			printf("close pipe fail: S2E_1");
			exit(1);
		}
		if (close(S2O_1) == -1){
			printf("close pipe fail: S2E_1");
			exit(1);
		}


	//set scanner to sleep and then wait for Sigterm and print
	signal(SIGTERM, doHandle);	
	while(h == 0){
		sleep(1);
		write(1, "*", sizeof("*"));
	}//infinate loop

	printf("\nWords with even letters:\n");
	while(read(E2S_0, &rIn1, sizeof(rIn1)) != 0){
		read(E2S_0, &rIn2, sizeof(rIn2));
		printf("\t%s\t\t%s\n", rIn1, rIn2);
	}

	printf("\nWords with odd letters:\n");
	while(read(O2S_0, &rIn1, sizeof(rIn1)) != 0){
		read(O2S_0, &rIn2, sizeof(rIn2));
		printf("\t%s\t\t%s\n", rIn1, rIn2);
	}

exit(0);
return 0;
}//main

/** test code for pipes
	char a = 'a';
	char rIn;
	write(S2E_1, &a, sizeof(char));
	read(E2S_0, &rIn, sizeof(char));
	printf("From scanner: %c\n", rIn);

	char b = 'b';
	char rIn2;
	write(S2O_1, &b, sizeof(char));
	read(O2S_0, &rIn2, sizeof(char));
	printf("From scanner: %c\n", rIn2);
*/

/*	
	new = (struct node *)malloc(sizeof(struct node));
	//calls for first node
		if(head == NULL){
			strcpy(new -> word, wtemp);
			new -> prev = NULL;
			new -> next = NULL;
			head = new;
			tail = new;
			ptr = new;
		}else{ //calls for every node after
			strcpy(new -> word, wtemp);
			tail -> next = new;
			new -> prev = tail;
			new -> next = NULL;
			ptr = tail;
			tail = new;
			tail -> next = NULL;
			tail -> prev = ptr;
		}//else
*/

/*
//test print of the linked list
	ptr = head;
	while(ptr != NULL){
		memset(output, 0, sizeof(output));
		strcpy(output, ptr -> word);

		printf("Scanner LL: %s\n", output);
		ptr = ptr -> next;
	}
*/
