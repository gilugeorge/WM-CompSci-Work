package knightsTour;

/**
 * This interface specifies required functionality for a class 
 * that represents a chess board and is able to solve the so-called open knight's tour problem.
 * 
 * Knight's tour problem: The objective is to find a sequence of moves performed by a knight on an n x n chess board from a given initial position such that every square on the board is visited exactly once.
 * Note that the knight is able to perform a move that consists of 2 squares in one direction followed by 1 square to the right or left of the first direction.
 * This interface is for the so-called open knight's tour problem, which means that the tour does not describe a cycle. 
 * If the tour happens to end at a position such that the knight can proceed to the initial position (the path describes a cycle), then the tour is called closed.
 * This property is not of interest in this context.
 * 
 * @author kemper
 *
 */
public interface Tour {
	/**
	 * This method sets the dimension of the board.
	 */
	void setDimension(int n) ;
	/**
	 * This method returns the dimension of the board.
	 * @return dimension n, 0 <= n
	 */
	int getDimension() ;
	/**
	 * This method computes a tour for a given starting position and returns a 2 x n integer array with coordinates (row,col) for a sequence of n positions. 
	 * @param startRow specifies the initial row position, 0 <= startRow < n
	 * @param startCol specifies the initial column position, 0 <= startCol < n
	 * @return an array of  length 2 * n such that a pair of adjacent entries [2k,2k+1] provides 
	 * a position of the knight for values of k, 0 <= k < n, and the sequence of pairs describes the knight's tour.
	 * The array is empty (length 0) if the computation failed.
	 */
	int[][] getTour(int startRow, int startCol) ;
	/**
	 * This method is a convenience method to output a knight's tour. It returns the result of getTour()
	 * in a string format ready for printing or to be put on display.
	 * The format is in the form of a chess board such that position indices are omitted and
	 * numerical index values for the sequence of steps are arranged in a square pattern following 
	 * the chess board.
	 * If there is no tour, the method returns an empty string. 
	 * @param startRow specifies the initial row position, 0 <= startRow < n
	 * @param startCol specifies the initial column position, 0 <= startCol < n
	 * @return formatted string that describes the tour, empty if tour does not exists.
	 */
	String printTour(int startRow, int startCol) ;
	
}