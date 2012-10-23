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

struct node {
	char word[1023]; 
	int frequency;
	struct node *next;
};

int main(int argc, char *argv[]){
	struct node *head = NULL;
	struct node *tail = NULL;
	struct node *ptr = NULL;
//	struct node *p = NULL;
	struct node *new = NULL;
	struct node *head2 = NULL;
	struct node *tail2 = NULL;
	struct node *ptr2 = NULL;
	struct node *new2 = NULL;
//	struct node *p2 = NULL;
	char readInEven[1023], readInOdd[1023];//, output[100];// output2[100];
	char temp[1023], temp2[1023];
	//int listCountE = 0;
	//int listCountO = 0;
	//int i,j;
	int swap, count;

	//***standalone mode***
	if(argv[1] == 0){
		if(strcmp(argv[0], "even") == 0){ //EVEN SECTION
			//printf("in even\n");
			while(read(0, readInEven, sizeof(readInEven)) != 0){
				if(getenv("EODELAY") != NULL){
					if(atoll(getenv("EODELAY")) > 0){
						sleep(atoll(getenv("EODELAY")));
					}
				}
				
				//check for repeats, if yes, then just add to count
				ptr = head;
				while(ptr != NULL){				
					if(strcmp(readInEven, ptr -> word) == 0){
						ptr -> frequency++;
						break;
					}else{
						ptr = ptr -> next;
					}
				}//for
						
				//place into linked lists
					new = (struct node *)malloc(sizeof(struct node));
					strcpy(new -> word, readInEven);
					new -> frequency += 1;
				//calls for first node
					if(head == NULL){
						new -> next = NULL;
						head = new;
						tail = new;
						ptr = new;
					}else{ //calls for every node after
						tail -> next = new;
						new -> next = NULL;
						ptr = tail;
						tail = new;
					}//else	
			}//end read section


			//arrange linked list in lexicological order (size then alpha)
			
			swap = 1;
			while(swap != 0){
				ptr = head;
				swap = 0;
				while( ptr != NULL){
					swap = 0;

					memset(&temp[0], 0, sizeof(temp));
					if(ptr -> next != NULL){
						if(strcmp(ptr -> word, ptr -> next -> word) > 0){
							//***check if this swaps correctly***
							//write(1, "Within swap section ln 97\n", sizeof("Within swap section ln 97"));
							swap = 1;
							
							strcpy(temp, ptr -> word);
							memset(&ptr -> word[0], 0, sizeof(ptr -> word));
							strcpy(ptr -> word, ptr -> next -> word);
							memset(&ptr -> next -> word[0], 0, sizeof(ptr -> next -> word));
							strcpy(ptr -> next -> word, temp);
							
							count =ptr -> frequency;
							ptr -> frequency = ptr -> next -> frequency;
							ptr -> next ->frequency = count;
						}else{
							ptr = ptr -> next;
						}
					}else
						break;
				}//inner-while
			}//outer-while
			//word - count write back to scanner
			ptr = head;
			while(ptr != NULL){
				write(1, &ptr -> word, sizeof(ptr -> word));
				sprintf(temp, "%d", ptr -> frequency);
				write(1, temp, sizeof(temp));
				ptr = ptr -> next;
			}
			close(E2S_1);
			sleep(10);
			kill(atoll(argv[1]), 15); //signal back to scanner
			exit(0);
		}else if(strcmp(argv[0], "odd") == 0){ //ODD SECTION

			//printf("in odd\n");
			while(read(0, readInOdd, sizeof(readInOdd)) != 0){
							if(getenv("EODELAY") != NULL){
								if(atoll(getenv("EODELAY")) > 0){
									sleep(atoll(getenv("EODELAY")));
								}
							}

							//check for repeats, if yes, then just add to count
							ptr2 = head2;
							while(ptr2 != NULL){				
								if(strcmp(readInOdd, ptr2 -> word) == 0){
									ptr2 -> frequency += 1;
									break;
								}else{
									ptr2 = ptr2 -> next;
								}
							}//for
						
							//place into linked lists
								new2 = (struct node *)malloc(sizeof(struct node));
								strcpy(new2 -> word, readInOdd);
								new2 -> frequency = 1;

							//calls for first node
								if(head2 == NULL){
									new2 -> next = NULL;
									head2 = new2;
									tail2 = new2;
									ptr2 = new2;
								}else{ //calls for every node after
									tail2 -> next = new2;
									new2 -> next = NULL;
									ptr2 = tail2;
									tail2 = new2;
								}//else	

							//printf("Even node %s\n", new -> word);
						}//end read section

			//arrange linked list in lexicological order (size then alpha)
			ptr2 = head2;
			swap = 1;
			while(swap != 0){
				swap = 0;
				while( ptr2 != NULL){
					swap = 0;
					if(ptr2 -> next != NULL){
						if(strcmp(ptr2 -> word, ptr2 -> next -> word) > 0){
							//***check if this swaps correctly***
							swap = 1;
							strcpy(temp2, ptr2 -> word);
							memset(&ptr2 -> word[0], 0, sizeof(ptr2 -> word));
							strcpy(ptr2 -> word, ptr2 -> next -> word);
							memset(&ptr2 -> next -> word[0], 0, sizeof(ptr2 -> next -> word));
							strcpy(ptr2 -> next -> word, temp2);
							
							count = ptr2 -> frequency;
							ptr2 -> frequency = ptr2 -> next -> frequency;
							ptr2 -> next ->frequency = count;

						}else{
							ptr2 = ptr2 -> next;
						}
					}else
						break;
				}//inner-while
			}//outer-while			

			//word - count write back to scanner
			ptr2 = head2;
			while(ptr2 != NULL){
				write(1, &ptr2 -> word, sizeof(ptr2 -> word));
				sprintf(temp2, "%d", ptr2 -> frequency);
				write(1, temp2, sizeof(temp));
				ptr2 = ptr2 -> next;
			}
			close(O2S_1);
			exit(0);

 
			}//end odd
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}else{//end standalone mode
		//***not standalone mode***
		if(strcmp(argv[0], "even") == 0){ //EVEN SECTION
			//printf("in even\n");
			while(read(S2E_0, readInEven, sizeof(readInEven)) != 0){
				if(getenv("EODELAY") != NULL){
					if(atoll(getenv("EODELAY")) > 0){
						sleep(atoll(getenv("EODELAY")));
					}
				}
				
				//check for repeats, if yes, then just add to count
				ptr = head;
				while(ptr != NULL){				
					if(strcmp(readInEven, ptr -> word) == 0){
						ptr -> frequency++;
						break;
					}else{
						ptr = ptr -> next;
					}
				}//for
						
				//place into linked lists
					new = (struct node *)malloc(sizeof(struct node));
					strcpy(new -> word, readInEven);
					new -> frequency += 1;
				//calls for first node
					if(head == NULL){
						new -> next = NULL;
						head = new;
						tail = new;
						ptr = new;
					}else{ //calls for every node after
						tail -> next = new;
						new -> next = NULL;
						ptr = tail;
						tail = new;
					}//else	
			}//end read section


			//arrange linked list in lexicological order (size then alpha)
			
			swap = 1;
			while(swap != 0){
				ptr = head;
				swap = 0;
				while( ptr != NULL){
					swap = 0;

					memset(&temp[0], 0, sizeof(temp));
					if(ptr -> next != NULL){
						if(strcmp(ptr -> word, ptr -> next -> word) > 0){
							//***check if this swaps correctly***
							//write(1, "Within swap section ln 97\n", sizeof("Within swap section ln 97"));
							swap = 1;
							
							strcpy(temp, ptr -> word);
							memset(&ptr -> word[0], 0, sizeof(ptr -> word));
							strcpy(ptr -> word, ptr -> next -> word);
							memset(&ptr -> next -> word[0], 0, sizeof(ptr -> next -> word));
							strcpy(ptr -> next -> word, temp);
							
							count =ptr -> frequency;
							ptr -> frequency = ptr -> next -> frequency;
							ptr -> next ->frequency = count;
						}else{
							ptr = ptr -> next;
						}
					}else
						break;
				}//inner-while
			}//outer-while
			//word - count write back to scanner
			ptr = head;
			while(ptr != NULL){
				write(E2S_1, &ptr -> word, sizeof(ptr -> word));
				sprintf(temp, "%d", ptr -> frequency);
				write(E2S_1, temp, sizeof(temp));
				ptr = ptr -> next;
			}
			close(E2S_1);
			sleep(10);
			kill(atoll(argv[1]), 15); //signal back to scanner
			exit(0);
		}else if(strcmp(argv[0], "odd") == 0){ //ODD SECTION

			//printf("in odd\n");
			while(read(S2O_0, readInOdd, sizeof(readInOdd)) != 0){
							if(getenv("EODELAY") != NULL){
								if(atoll(getenv("EODELAY")) > 0){
									sleep(atoll(getenv("EODELAY")));
								}
							}

							//check for repeats, if yes, then just add to count
							ptr2 = head2;
							while(ptr2 != NULL){				
								if(strcmp(readInOdd, ptr2 -> word) == 0){
									ptr2 -> frequency += 1;
									break;
								}else{
									ptr2 = ptr2 -> next;
								}
							}//for
						
							//place into linked lists
								new2 = (struct node *)malloc(sizeof(struct node));
								strcpy(new2 -> word, readInOdd);
								new2 -> frequency = 1;

							//calls for first node
								if(head2 == NULL){
									new2 -> next = NULL;
									head2 = new2;
									tail2 = new2;
									ptr2 = new2;
								}else{ //calls for every node after
									tail2 -> next = new2;
									new2 -> next = NULL;
									ptr2 = tail2;
									tail2 = new2;
								}//else	

							//printf("Even node %s\n", new -> word);
						}//end read section

			//arrange linked list in lexicological order (size then alpha)
			ptr2 = head2;
			swap = 1;
			while(swap != 0){
				swap = 0;
				while( ptr2 != NULL){
					swap = 0;
					if(ptr2 -> next != NULL){
						if(strcmp(ptr2 -> word, ptr2 -> next -> word) > 0){
							//***check if this swaps correctly***
							swap = 1;
							strcpy(temp2, ptr2 -> word);
							memset(&ptr2 -> word[0], 0, sizeof(ptr2 -> word));
							strcpy(ptr2 -> word, ptr2 -> next -> word);
							memset(&ptr2 -> next -> word[0], 0, sizeof(ptr2 -> next -> word));
							strcpy(ptr2 -> next -> word, temp2);
							
							count = ptr2 -> frequency;
							ptr2 -> frequency = ptr2 -> next -> frequency;
							ptr2 -> next ->frequency = count;

						}else{
							ptr2 = ptr2 -> next;
						}
					}else
						break;
				}//inner-while
			}//outer-while			

			//word - count write back to scanner
			ptr2 = head2;
			while(ptr2 != NULL){
				write(O2S_1, &ptr2 -> word, sizeof(ptr2 -> word));
				sprintf(temp2, "%d", ptr2 -> frequency);
				write(O2S_1, temp2, sizeof(temp));
				ptr2 = ptr2 -> next;
			}
			close(O2S_1);
			exit(0);

 
			}//end odd
	}//end piped mode

return 0;
}//main


/** Test code for Pipes
		char readIn, sendout, readIn2, sendout2;
		read(S2E_0, &readIn, sizeof(char));
		printf("From even: %c\n", readIn);
		sendout = 'A';
		write(E2S_1, &sendout, sizeof(char));

		read(S2O_0, &readIn2, sizeof(char));
		printf("From odd: %c\n", readIn2);
		sendout2 = 'B';
		write(O2S_1, &sendout2, sizeof(char));
*/

/* linked list print for even
				//test print of the linked list
					ptr = head;
					while(ptr != NULL){
						memset(output, 0, sizeof(output));
						strcpy(output, ptr -> word);
						printf("Scanner LL: %s\n", output);
						ptr = ptr -> next;
					}			
*/

/* linked list print for odd
		//test print of the linked list
			ptr2 = head2;
			while(ptr2 != NULL){
				memset(output2, 0, sizeof(output2));
				strcpy(output2, ptr2 -> word);
				printf("Scanner LL: %s\n", output2);
				ptr2 = ptr2 -> next;
			}
*/
