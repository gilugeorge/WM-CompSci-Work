#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>

pthread_mutex_t crit;
pthread_mutex_t fqCrit;
pthread_mutex_t linkedList;


struct node {
  char lineNumber [20];
  char lineFile [100];
  int hitRatio;
  struct node *next;
  struct node *prev;
};

FILE *file;
struct timespec threadDelay, tim2, filedelay, tim4;
int cache =0, readFlag = 0, hit = 0, searches = 0;
int counts, capValue, cacheSize = 0;
char **output_buffer;
int global_count = 0, internal_count = 0;
struct node *head, *tail, *current, *new, *temp;

static void *lookup (void *arg);
static void *reader (void *arg);


int main(int argc, char *argv[]){
   	//argument checking variables created here
    int bflag = 0, nCapflag = 0, dflag = 0, dCapflag =0;
    char *bval = NULL;
    char *nCapvalue = NULL;
    char *dvalue = NULL;
    char *dCapvalue = NULL;
    int index, c, threadCheck, bvalueint, i;

    opterr = 0;
		//deal with input arguments
    while ((c = getopt (argc, argv, "b:N:d:D:")) != -1)
        switch (c)
				{
				case 'b':
				    bflag = 1;
				    bval = optarg;
				    break;
				case 'N':
				    nCapflag = 1;
				    nCapvalue = optarg;
						capValue = atoi(nCapvalue);
				    break;
				case 'd':
				    dflag = 1;
				    dvalue = optarg;
				    break;
				case 'D':
				    dCapflag = 1;
				    dCapvalue = optarg;
				    break;
				case '?':
				    if (isprint (optopt))
				        fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				    else
				        fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				    return 1;
				default: break;
				}
   
		//-b flag for NumLines
    if(bflag == 0 || atoll(bval)==0){
        bvalueint = 1000;
    }else{
        bvalueint = atoll(bval);
		//printf("bvalue: %d\n", bvalueint);
				bvalueint = 1000;
    }

		//-d flag for filedelay
    filedelay.tv_sec = 0;
    if(dflag==1){
        filedelay.tv_nsec = atoll(dvalue);
		//printf("filedelay: %d\n", atoll(dvalue));
    }else{
        filedelay.tv_nsec = 0;
    } 

   	//-D flag for threaddelay
    threadDelay.tv_sec = 0;
    if(dCapflag==1){
        threadDelay.tv_nsec = atoll(dCapvalue);
		//printf("threadDelay value: %d\n", atoll(dCapvalue));
    }else{
        threadDelay.tv_nsec = 0;
    }

    output_buffer = (char **)malloc(bvalueint * sizeof(char *));
    for(i = 0; i < bvalueint; i++){
        output_buffer[i] = (char *) malloc(20 * sizeof(char));
        //strcpy(output_buffer[i], "123.123.123.123");       
    }

   
   	//Create threads and do the threads while there are arguments in the file.//
    index = optind;
    while((argc - index) > 0){
        index++;
        pthread_t th_a, th_b, th_c; void *retval;
        counts = 0;
        file = NULL;
        readFlag = 0;
        internal_count = 0;
        global_count = 0;
        if((file = fopen(argv[index-1], "r")) == NULL)
            continue;

				//create lookup thread 1
        threadCheck = pthread_create(&th_a, NULL, lookup, (void *) "a");
        if (threadCheck != 0) fprintf (stderr, "create a failed %d\n", threadCheck);
				//create lookup thread 2       
        threadCheck = pthread_create(&th_b, NULL, lookup, (void *) "a");
        if (threadCheck != 0) fprintf (stderr, "create a failed %d\n", threadCheck);
				//create reader thread       
        threadCheck = pthread_create(&th_c, NULL, reader, (void *) "a");
        if (threadCheck != 0) fprintf (stderr, "create a failed %d\n", threadCheck);
       
       	//join threads back together
        threadCheck = pthread_join (th_a, &retval);
        if (threadCheck != 0) 
					fprintf (stderr, "join a failed %d\n", threadCheck);  
       
 				threadCheck = pthread_join (th_b, &retval);
        if (threadCheck != 0) 
					fprintf (stderr, "join b failed %d\n", threadCheck);
       
        threadCheck = pthread_join (th_c, &retval);
        if (threadCheck != 0) 
					fprintf (stderr, "join b failed %d\n", threadCheck);
       
    }//thread while
		
		//output
		current = head;
		while(current != NULL){
			printf("Ip: %s \t	FQDN: %s\n", current -> lineNumber, current -> lineFile);
			current = current -> prev;
		}
			
    return 0;   
}

/**Reader Thread
*/
static void *reader (void *arg){
    char line[100];
    internal_count = 0;
    int countii=0;
    while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
    {   
        //printf("tests\n");
        if(strcmp(line, "\n") == 0)
            continue;
        if( line[strlen(line)-1] == '\n' )
            line[strlen(line)-1] = 0;
        countii++;
        pthread_mutex_lock(&crit);
        strcpy(output_buffer[internal_count], line);
        internal_count++;
        pthread_mutex_unlock(&crit);
       
        if(nanosleep(&filedelay, &tim4) < 0 )  
        {
            printf("Nano sleep system call failed \n");
            exit(1);
        }
    }
    pthread_mutex_lock(&crit);
    readFlag = 1;
    pthread_mutex_unlock(&crit);
    return NULL;   
}


/**Lookup Thread.
*/
static void *lookup (void *arg)
{
    char array[1000];
    while(readFlag == 0){
    while(global_count < internal_count ){
        pthread_mutex_lock(&crit);
        if(!sscanf(output_buffer[global_count], "%s", array)){ //error checking
            printf("Not good!\n");
            //global_count++;
            continue;
        }
        global_count++;
				searches++;
        pthread_mutex_unlock(&crit);

		//sleep
        if(nanosleep(&threadDelay , &tim2) < 0 )  
        {
            printf("Nano sleep system call failed \n");
            exit(1);
        }
		
		//find IP
        int count = 0;
        int countDot = 0;
        int i;
        int flag = 0;
        for( i = 0; i < strlen(array); i++){
            if(array[i] >= 48 && array[i] <= 57 ){//check for proper IP
                count++;
                if( count > 3 ){
                    flag = 1;
                    break;
                }
            }
            else if(array[i] == 46){ //check for proper IP
                countDot++;
                if( countDot > 3 || count ==0){
                    flag = 2;
                    break;
                }
                count = 0;
            }
            else{
                flag = 3;
                break;
            }           
        }
        if(countDot != 3 || count == 0){
            flag = 4;
        }

				//check in cache and store
        if(flag == 0 ){             
					//retrieve a FQDN
						pthread_mutex_lock(&fqCrit);
						struct hostent *hp;
						in_addr_t adr_clnt;
						adr_clnt = inet_addr(array);
						hp = gethostbyaddr((char *)&adr_clnt, sizeof(adr_clnt), AF_INET);
						pthread_mutex_unlock(&fqCrit);
           
            pthread_mutex_lock(&linkedList);
						//cache lookup section here           
						//check for # of entries in cache
						//need a case for initial cache input
						//then check to see if IP is within the cache
						//if yes, then retrieve that info
						//otherwise, add info into the cache
						//reorder the linked list
						new = (struct node*)malloc(sizeof(struct node));
						new -> next = NULL;
						new -> prev = NULL;
						cacheSize++;
						if(head == NULL){
						head = new;
						tail = new;
						//current = new;
						}
						else{
							new->prev = head;
							head->next = new;
							head = new;
						}
						current = head;
						while(current != NULL){
							if(current -> lineNumber != NULL && strcmp(current->lineNumber, array) == 0){
								//printf("if: %s\n", array);
								current->prev->next = current->next;
								current->next->prev = current->prev;
								hit++;
								current -> hitRatio = hit/searches;
							}
							current = current -> prev;
						}//while

						//check for FQDN and put in node
						if(hp != NULL){
							strcpy(head->lineFile, hp->h_name);
							strcpy(head->lineNumber, array);
						}else{
							strcpy(head->lineNumber, array);
							//printf("%s\n", array);
						}
						/*
						//check cacheSize and cut accordingly
						if(cacheSize > capValue){
							current = head;
							for(i = 0; i <= cacheSize; i++){
								current = current -> next;
							}
							current -> next -> prev = NULL;
							current -> next = NULL;							
						}
       			*/
            pthread_mutex_unlock(&linkedList);
        }//flag if ends
       
    }//global count while
    }//major flag while
    return NULL;
}//lookup thread
