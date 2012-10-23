/* Eric Shih
 * This program looks through a set of sayings and extracts the sayings
 * that contain the specified term input by the user.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
	char fileName[1023];
	char lineNumber[1023];
	char lineSaying[1023];
	int flag;
	struct node *next;
	struct node *prev;
};


int main(int argc, char *argv[]){
	//linked list for holding the file and line information	
	struct node *current;
	struct node *head = NULL;
	struct node *ptr = NULL;
	struct node *tail = NULL;
	//linked for holding the lines to be outputted
	struct node *finalSet;
	struct node *head2 = NULL;
	struct node *ptr2 = NULL;
	struct node *tail2 = NULL;
	struct node *temp;
	struct node *line;

	//other needed variables
	int sayings = 0;
	int nodeNum = 0;
	int currentLine = 0;
	int i, j;
	char linePtr[1023];
	char buffer[1023];
	FILE *myFile;


//check input



//////////////////////store line location and line file
while(fgets(linePtr, 1023, stdin) != NULL){
	current = (struct node *)malloc(sizeof(struct node));
	i = 0;
	j = 0;

	//store line Name
	while( linePtr[i] != ':'){
		current -> fileName[i] = linePtr[i];
		i++;
	}
	//printf("File Name: %s\n", current -> fileName);	

	i++; //used to skip past the colon
	//store Line Number
	while( linePtr[i] != ':'){
		current -> lineNumber[j] = linePtr[i];
		i++;
		j++;
	}
	//printf("Line Number: %s\n", current -> lineNumber);

	if(nodeNum == 0){
		head = current;
		tail = current;
		ptr = current;
	}else{
		tail -> next = current;
		ptr = tail;	
		tail = current;
		tail -> prev = ptr;
	}

nodeNum++;
}//storage while loop

////////////////look for saying and add to final linked list
ptr = head;
while(ptr != NULL){
	currentLine = 0;

	myFile = fopen(ptr -> fileName, "r");
	while(fgets(buffer, 1023, myFile) != NULL){
		//printf("line 97");
		finalSet = (struct node *)malloc(sizeof(struct node));
		
		strcpy(finalSet -> lineSaying, buffer); //copy into node
	
		//connect points
		if(sayings == 0){
			head2 = finalSet;
			ptr2 = finalSet;
			tail2 = finalSet;
		}
		tail2 -> next = finalSet;
		finalSet -> prev = tail2;
		finalSet -> next = NULL;
		tail2 = finalSet;

		//found correct line and add flag node
/*		if(currentLine >= atoll(ptr -> lineNumber)){
			printf("line numbers match, Sayings: %d\n", sayings);
		} */
		if(currentLine >= atoll(ptr -> lineNumber) && strcmp(buffer, "%\n") == 0){
			//printf("line 112\n");
			//cut out % node
			temp = tail2;
			tail2 =	tail2 -> prev;
			tail2 -> next = NULL;
			temp -> prev = NULL;
			
			//add in line node
			line = (struct node *)malloc(sizeof(struct node));
			strcpy(line -> lineSaying, "------------------------------------");
			tail2 -> next = line;
			line -> prev = tail2;
			line -> next = NULL;
			line -> flag = 1;
			tail2 = line;
			ptr2 = line;
			sayings++;
			break;
		}//if


		//trim until flag
		if(strcmp(buffer, "%\n") == 0 && sayings != 0){
			while(tail2 -> flag != 1 && finalSet -> prev != NULL){
				//printf("trim section\n");
				finalSet = finalSet -> prev;
				finalSet -> next = NULL;
				tail2 -> prev = NULL;
				tail2 = finalSet;
			}//while 
		}//if

	//printf("Current Line %d\n", currentLine);
	currentLine++;

	}//while



	fclose(myFile);
	//printf("closed file\n");
	ptr = ptr -> next;
}//while

/////////////////output sayings with or without banner//
if(strcmp(argv[1],"-b") == 0){
	printf("\n%d witty sayings contain the string %s\n", sayings-1, argv[2]);
}

/*if(ptr2 == NULL){
	printf("ptr2 is null");
}else{
	printf("ptr2 is not null\n");
}
*/

//remove percent sign
ptr2 = head2 -> next;
while(ptr2 != NULL){
	printf("%s\n", ptr2 -> lineSaying);
	ptr2 = ptr2 -> next;
}

return 0;
}//main
