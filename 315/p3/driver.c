#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define S2E_0 16
#define S2E_1 17
#define E2S_0 18
#define E2S_1 19
#define S2O_0 20
#define S2O_1 21
#define O2S_0 22
#define O2S_1 23

int main(int argc, char *argv[]){
	int file;
	int scannerFork, evenFork, oddFork;
	int s2e[2], e2s[2], s2o[2], o2s[2]; //the pipes between scanner-even and scanner-odd
	int check1, execlCheck;
//check arguments

	
	if(argc != 2){
		printf("Wrong Number of Arguments.\n");
		exit(1);
	}
	check1 = atoll(argv[1]);
	if(check1 == -1){
		printf("Improper test file.\n");
		exit(1);
	}

//***test open file***
	file = open(argv[1], O_RDONLY);
	if(file == -1){
		printf("File Unreadable\n");
		exit(1);
	}
	dup2(file, 0);

//create sub-processes and send info to scanner
pipe(s2e); pipe(e2s); pipe(s2o); pipe(o2s);  //creates all the pipes

	scannerFork = fork();	
	if(scannerFork == -1){ //check that fork is correct
		printf("Forking Error.\n");
		exit(1);
	}

	if (scannerFork == 0){ //scanner fork
		close(s2e[0]); 	//close unused pipe ends
		close(e2s[1]);
		close(s2o[0]);
		close(o2s[1]);
		
		dup2(s2e[1], S2E_1); //dup the necessary file descriptors
		dup2(e2s[0], E2S_0);
		dup2(s2o[1], S2O_1);
		dup2(o2s[0], O2S_0);

		close(s2e[1]);
		close(e2s[0]);
		close(s2o[1]);
		close(o2s[0]);

		//execl here
		execlCheck = execl("./scanner", "scanner", NULL);
		if(execlCheck == -1){
			printf("Execl error in creating scanner\n");
			exit(1);
		}

	}else{ //even fork
		evenFork = fork();
		if(evenFork == -1){ //check that fork is correct
			printf("Forking Error.\n");
			exit(1);
		}		
		if(evenFork == 0){
			close(s2e[1]);//close unused pipe ends
			close(e2s[0]);
			close(s2o[0]);
			close(s2o[1]);
			close(o2s[0]);
			close(o2s[1]);

			dup2(s2e[0], S2E_0); //dup the necessary file descriptors
			dup2(e2s[1], E2S_1);

			close(s2e[0]);
			close(e2s[1]);

			//execl here
			execlCheck = execl("./evenodd", "even", "0", NULL);
			if(execlCheck == -1){
				printf("Execl error in creating even\n");
				exit(1);
			}
		}else{			//odd fork
				oddFork = fork();
				if(oddFork == -1){ //check that fork is correct
					printf("Forking Error.\n");
					exit(1);
				}

				if(oddFork == 0){
					close(s2e[0]); //close unused pipe ends
					close(s2e[1]);
					close(e2s[0]);
					close(e2s[1]);
					close(s2o[1]);
					close(o2s[0]);

					dup2(s2o[0], S2O_0);	//dup the necessary file descriptors
					dup2(o2s[1], O2S_1);

					close(s2o[0]); //close remaining pipes
					close(o2s[1]);

					//execl here***
					execlCheck = execl("./evenodd", "odd", "1", NULL);
					if(execlCheck == -1){
						printf("Execl error in creating odd\n");
						exit(1);
					}
				}
		}//odd else
	}//even else

	//close all files and wait
	close(s2e[0]);
	close(s2e[1]);
	close(e2s[0]);
	close(e2s[1]);
	close(s2o[0]);
	close(s2o[1]);
	close(o2s[0]);
	close(o2s[1]);

	//wait until kids die then terminate
	waitpid(scannerFork, NULL, 0);
	
return 0;
}//main

