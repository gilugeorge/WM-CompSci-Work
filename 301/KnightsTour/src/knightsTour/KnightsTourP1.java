/**
 * 
 */
package knightsTour;


import java.util.Arrays;
/**
 * This class implements the Knights' tour for the Tour interface for Project 1.
 * The code skeleton was generated in Eclipse with the new class feature and requesting that interface Tour should be implemented.
 * The code is for Java 1.6 or higher.
 * 
 * @author Mark Pfluger
 * @author Eric Shih
 *
 */

public class KnightsTourP1 implements Tour {

	int boardSize;
	int[][] array;
	int moveCount=1;
	/* (non-Javadoc)
	 * @see knightsTour.Tour#setDimension(int)
	 */
	public void setDimension(int n) {
		boardSize = n;
			
	}//boardSize

	/* (non-Javadoc)
	 * @see knightsTour.Tour#getDimension()
	 */
	public int getDimension() {
		return boardSize;
	}//getDimension

	/* 
	 * This method will set up the board and call the recursive function doTour.
	 */
	public int[][] getTour(int startRow, int startCol) {
		array= new int[boardSize][boardSize];
		
		for (int y = 0; y<boardSize; y++){
			for ( int x=0; x<boardSize; x++){
				array[x][y] = 0;
			}
		}
		
		//if the board is 0x0 then it will return an empty array
		if(boardSize == 0){
			return array;
		}
		
		int doTourResult = doTour( startRow, startCol );
		if( doTourResult == 1)
			return array;
		else
			return array;
	}
	
	/*
	 * This method is the one that is recursed in the knights tour. It
	 * will return the completed tour in an int arrary.
	 */
	private int doTour(int startRow, int startCol){
		
		//set up counters and positions the starting location
		if(moveCount == 1){
			array[startRow][startCol] = 1;
		}
		array[startRow][startCol] = moveCount;
		moveCount++;
		 
		if( moveCount == (boardSize*boardSize) + 1 ){
			return 1;
		}
		
			
			//begin checks for each potential move
			if( !(startRow+1 < 0 || startRow+1 >boardSize-1 || startCol+2 < 0  || startCol+2 > boardSize-1) ) {
				if( array[startRow+1][startCol+2] == 0 ){
					if ( doTour(startRow+1, startCol+2) == 1)
						return 1;
				}//(1,2)
			}
			if( !(startRow+2 < 0 || startRow+2 >boardSize-1 || startCol+1 < 0  || startCol+1 > boardSize-1) ){
					if( array[startRow+2][startCol+1] ==0 ){
						if( doTour(startRow+2, startCol+1) == 1)
							return 1;
				}//(2,1)
			}
			if( !(startRow+2 < 0 || startRow+2 >boardSize-1 || startCol-1 < 0  || startCol-1 > boardSize-1) ){
				if( array[startRow+2][startCol-1] == 0 ){
					if( doTour(startRow+2, startCol-1) == 1)
						return 1;
				}//(2,-1)
			}
			if( !(startRow+1 < 0 || startRow+1 >boardSize-1 || startCol-2 < 0  || startCol-2 > boardSize-1) ){
				if( array[startRow+1][startCol-2] ==0 ){
					if( doTour(startRow+1, startCol-2)== 1)
						return 1;
				}//(1,-2)
			}
			if( !(startRow-1 < 0 || startRow-1 >boardSize-1 || startCol-2 < 0  || startCol-2 > boardSize-1) ){
				if( array[startRow-1][startCol-2] ==0 ){
					if( doTour(startRow-1, startCol-2)== 1)
						return 1;
				}//(-1,-2)
			}
			if( !(startRow-2 < 0 || startRow-2 >boardSize-1 || startCol-1 < 0  || startCol-1 > boardSize-1) ){
				if( array[startRow-2][startCol-1] ==0 ){
					if( doTour(startRow-2, startCol-1)== 1)
						return 1;
				}//(-2,-1)
			}
			if( !(startRow-2 < 0 || startRow-2 >boardSize-1 || startCol+1 < 0  || startCol+1 > boardSize-1) ){
				if( array[startRow-2][startCol+1] ==0 ){
					if( doTour(startRow-2, startCol+1)== 1)
						return 1;
				}//(-2,1)
			}
			if( !(startRow-1 < 0 || startRow-1 >boardSize-1 || startCol+2 < 0  || startCol+2 > boardSize-1) ){
				if( array[startRow-1][startCol+2] ==0 ){
					if( doTour(startRow-1, startCol+2)== 1)
						return 1;
				}//(-1,2)
			}
		
		//will decrement moveCount and go back up the tree if no moves are found
		moveCount--;
		array[startRow][startCol] = 0;
		return 0;			
	}//doTour
	
	/* (non-Javadoc)
	 * @see knightsTour.Tour#printTour(int, int)
	 */
	public String printTour(int startRow, int startCol) {
		getTour( startRow, startCol ); //run the tour because people may call it without doing getTour
		
		//print the board
		for (int y = 0; y<boardSize; y++){
			System.out.println();
			for ( int x=0; x<boardSize; x++){
				System.out.print(array[x][y]+ "  " + "");
			}
		}		
		
			return Arrays.toString(array);
	}//printTour
}//KnightsTourP1
