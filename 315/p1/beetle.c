/* Eric Shih
 * This program calculates the average number of steps for a beetle
 * to commit drunken suicide. It takes in number of beetles and board size.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double getXDirection();
double getYDirection();
double computeTime(int time, int beetles);
int sLength(char string[]);

int main(int argc, char *argv[]){
	//check for correct number of Args
	if(argc != 3){
		printf("Incorrect Number of Inputs\n");
		exit(1);
	}
	
	//creating the variables and filling the board and beetles
	int board = atoll(argv[1]);
	int beetles = atoll(argv[2]);
	double beetlesCount = beetles;
	float time = 0;
	double totalTime = 0;
	double xdir, ydir;
	double xpos, ypos;

	//printf("Board Size: %d\n", board);
	//printf("Beetle Number: %d\n", beetles);

	//check that the args are positive nonzero integers
	if(board <= 0 || beetles <= 0){
		printf("Illegal Inputs\n");		
		exit(1);
	}
	
	//check that the two inputs are correct lengths. This accounts for
	//the case where there is a number, then a letter
	 const char base[] = "";
   char filename [ FILENAME_MAX ];
   sprintf(filename, "%s%d", base, board);
 	 const char base2[] = "";
   char filename2 [ FILENAME_MAX ];
   sprintf(filename2, "%s%d", base2, beetles);
   //printf("filename = \"%s\"\n", filename);
   //printf("filename2 = \"%s\"\n", filename2);

	//printf("Num 1 %s\n", argv[1]);
	//printf("Num 2 %s\n", argv[2]);
	if(sLength(filename) != sLength(argv[1]) || sLength(filename2) != sLength(argv[2])){
		printf("Illegal Inputs\n");
		exit(1);
	}

	//starting position
	xpos = board/2;
	ypos = board/2;

	while(beetles > 0){
		//printf("Beetles %d\n", beetles);
		//starting position
		xpos = board/2;
		ypos = board/2;
		
	while(xpos >= 0 && xpos <= board && ypos >= 0 && ypos <= board){	
			//printf("xPos %.1f\n", xpos);
			//printf("yPos %.1f\n", ypos);

			xdir = getXDirection();
			ydir = getYDirection();

			xpos = xpos + xdir;
			ypos = ypos + ydir;

			totalTime += 2;
		}//inner while
		
		beetles--;
	}//outer while

	//printf("Total Time %f\n", totalTime);
	//printf("Beetles %f\n", beetlesCount);
	time = totalTime/beetlesCount;

	int b = beetlesCount;
	printf("%d by %d square, %d beetles, mean beetle lifetime is %.1f\n", board, board, b, time);

return 0;
}//main

//Calculate the x direction using Cos
double getXDirection(){
	double r = random();
	r = r/(2 * M_PI);
	double dir = cos(r);
	return dir;
}//getXDirection

//Calculate the y direction using Sin
double getYDirection(){
	double r = random();
	r = r/(2 * M_PI);
	double dir = sin(r);
	return dir;
}//getYDirection

/*
 *This function finds the length of a string
 */
int sLength(char string[]){
    int index = 0;

    while(string[index] != '\0'){
      index++;
    }//while

    return index;
}//sLength
