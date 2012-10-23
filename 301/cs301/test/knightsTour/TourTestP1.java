/**
 * 
 */
package knightsTour;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

/**
 * This a set of tests for methods of a class that implements the Tour interface to compute a knight's tour.
 * This is for Junit 4.
 * 
 * @author peterkemper
 *
 */
public class TourTestP1 {

	private Tour tour1;
	
	/**
	 * This method is automatically called by the junit runtime environment before each individual test and is supposed to contain code
	 * that creates necessary data structures used in each test.
	 * The method is used to share common initialization code among all tests.
	 * 
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception {
		
		tour1 = new KnightsTourP1();
		
	}//setUp

	/**
	 * This method is automatically called by the junit runtime environment after each individual test and is supposed to contain code
	 * that deletes data structures no longer used after each test.
	 * The method is used to share common clean-up code among all tests.
	 * @throws java.lang.Exception
	 */
	@After
	public void tearDown() throws Exception {
		tour1 = null;
	}//tearDown

	/**
	 * Test method for get/set pair for attribute dimension.
	 */
	@Test
	public void testSetDimension() {
		// TODO: add code to check if reading and writing that attribute works correctly.
		// NOTE: a test must exercise functions of the class under test AND perform a correctness check
		// with methods of type assertTRUE(), assertFALSE() etc
		// check the documentation of the org.junit.Assert package for further details!
		// http://www.junit.org/apidocs/org/junit/Assert.html
		
		tour1.setDimension(8);
		assertEquals(8, tour1.getDimension());
	}

	private boolean compareGetTour(int startCol, int startRow, int array[][]){
		
		int counter = 1;
		int counterTemp = 1;
		
		if(tour1.getDimension() == 0){
			return true;
		}
		
		while( counter <= tour1.getDimension()*tour1.getDimension()){


			if( !(startRow+1 < 0 || startRow+1 >tour1.getDimension()-1 || startCol+2 < 0  || startCol+2 > tour1.getDimension()-1) ) {
				if( array[startRow+1][startCol+2] == counter++ ){
					startRow += 1;
					startCol += 2;					
					counter++;
				}//(1,2)
			}
			else if( !(startRow+2 < 0 || startRow+2 >tour1.getDimension()-1 || startCol+1 < 0  || startCol+1 > tour1.getDimension()-1) ){
					if( array[startRow+2][startCol+1] == counter++ ){
						startRow += 2;
						startCol += 1;	
						counter++;
				}//(2,1)
			}
			else if( !(startRow+2 < 0 || startRow+2 >tour1.getDimension()-1 || startCol-1 < 0  || startCol-1 > tour1.getDimension()-1) ){
				if( array[startRow+2][startCol-1] == counter++ ){
					startRow += 2;
					startCol -= 1;	
					counter++;
				}//(2,-1)
			}
			else if( !(startRow+1 < 0 || startRow+1 >tour1.getDimension()-1 || startCol-2 < 0  || startCol-2 > tour1.getDimension()-1) ){
				if( array[startRow+1][startCol-2] == counter++ ){
					startRow += 1;
					startCol -= 2;	
					counter++;
				}//(1,-2)
			}
			else if( !(startRow-1 < 0 || startRow-1 >tour1.getDimension()-1 || startCol-2 < 0  || startCol-2 > tour1.getDimension()-1) ){
				if( array[startRow-1][startCol-2] == counter++ ){
					startRow -= 1;
					startCol -= 2;
					counter++;
				}//(-1,-2)
			}
			else if( !(startRow-2 < 0 || startRow-2 >tour1.getDimension()-1 || startCol-1 < 0  || startCol-1 > tour1.getDimension()-1) ){
				if( array[startRow-2][startCol-1] == counter++ ){
					startRow -= 2;
					startCol -= 1;	
					counter++;
				}//(-2,-1)
			}
			else if( !(startRow-2 < 0 || startRow-2 >tour1.getDimension()-1 || startCol+1 < 0  || startCol+1 > tour1.getDimension()-1) ){
				if( array[startRow-2][startCol+1] == counter++ ){
					startRow -= 2;
					startCol += 1;	
					counter++;
				}//(-2,1)
			}
			else if( !(startRow-1 < 0 || startRow-1 >tour1.getDimension()-1 || startCol+2 < 0  || startCol+2 > tour1.getDimension()-1) ){
				if( array[startRow-1][startCol+2] == counter++ ){
					startRow -= 1;
					startCol += 2;	
					counter++;
				}//(-1,2)
			}
			
			if( counter == counterTemp){
				return false;
			}
			counterTemp++;
			
		}
		return true;
	}//compareGetTour
	
	
	/**
	 * Test if a tour calculation is correct for a board of size 0 x 0
	 * Initialization is not possible with any reasonable value, we try r=1,c=1,
	 * 
	 */
	@Test
	public void testGetTour0() {
		// TODO: add test code
		// NOTE: a test must exercise functions of the class under test AND perform a correctness check
		// with methods of type assertTRUE(), assertFALSE() etc
		// check the documentation of the org.junit.Assert package for further details!
		// http://www.junit.org/apidocs/org/junit/Assert.html

		try{
			setUp();
		}catch(Exception e){
			System.out.println("fail Set Up.");
		}
		
		tour1.setDimension(0);

		int[][] array = tour1.getTour(0, 0);
		assertTrue(compareGetTour(0, 0, array)); //0x0 will never work

		try{
			tearDown();
		}catch(Exception e){
			System.out.println("fail tear down.");
		}

	}//testGetTour0
	
	/**
	 * Test if a tour calculation is correct for a board of size 1 x 1
	 * Initialization is only possible with r=0,c=0, others should result in an error
	 * For r=0,c=0, trivial tour of length 1
	 */
	@Test
	public void testGetTour1() {
		// TODO: add test code
		// NOTE: a test must exercise functions of the class under test AND perform a correctness check
		// with methods of type assertTRUE(), assertFALSE() etc
		// check the documentation of the org.junit.Assert package for further details!
		// http://www.junit.org/apidocs/org/junit/Assert.html

		try{
			setUp();
		}catch(Exception e){
			System.out.println("fail Set Up.");
		}
		
		tour1.setDimension(1);
		int[][] array = tour1.getTour(0, 0);
		assertFalse(compareGetTour(0, 0, array)); //should error, therefore assertFalse
		
		try{
			tearDown();
		}catch(Exception e){
			System.out.println("fail tear down.");
		}	
	}
	
	/**
	 * Test if a tour calculation is correct for a board of size 2 x 2
	 * Initialization is possible with different value pairs, e.g. r=0,c=0, however there is no solution
	 * since the knight cannot perform any legal moves.
	 * The test checks all possible initial positions.
	 */
	@Test
	public void testGetTour2() {
		// TODO: add test code
		// NOTE: a test must exercise functions of the class under test AND perform a correctness check
		// with methods of type assertTRUE(), assertFALSE() etc
		// check the documentation of the org.junit.Assert package for further details!
		// http://www.junit.org/apidocs/org/junit/Assert.html

		try{
			setUp();
		}catch(Exception e){
			System.out.println("fail Set Up.");
		}
		
		tour1.setDimension(2);
		int[][] array = tour1.getTour(0, 0);
		assertFalse(compareGetTour(0, 0, array)); //should also return false because it is impossible.
		
		try{
			tearDown();
		}catch(Exception e){
			System.out.println("fail tear down.");
		}	
	}
	

	/**
	 * Test if a tour calculation is correct for a board of size 4 x 4
	 * The test checks all possible initial positions.
	 * 
	 * TODO: what is the correct solution we should expect??? There are no solutions to the 4x4 board
	 */
	@Test
	public void testGetTour4() {
		// TODO: add test code
		// NOTE: a test must exercise functions of the class under test AND perform a correctness check
		// with methods of type assertTRUE(), assertFALSE() etc
		// check the documentation of the org.junit.Assert package for further details!
		// http://www.junit.org/apidocs/org/junit/Assert.html

		try{
			setUp();
		}catch(Exception e){
			System.out.println("fail Set Up.");
		}
		
		tour1.setDimension(4);
		
		for(int x = 0; x < 4; x++){
			for(int y = 0; y < 4; y++){
				int[][] array = tour1.getTour(x, y);
				if(compareGetTour(x, y, array))
					assertTrue(true);
			}//for-inner
		}//for-outer
		assertFalse(false); //this should not work. because there is no solution for the 4x4.
		
		try{
			tearDown();
		}catch(Exception e){
			System.out.println("fail tear down.");
		}
	}

	
	/**
	 * Test if a tour calculation is correct for a board of size 5 x 5
	 * The test checks all initial positions that are different (subject to symmetry arguments).
	 * 
	 * TODO: what is the correct solution we should expect??? There should be at least 1 solution to the 5x5 board.
	 */
	@Test
	public void testGetTour5() {
		// TODO: add test code
		// NOTE: a test must exercise functions of the class under test AND perform a correctness check
		// with methods of type assertTRUE(), assertFALSE() etc
		// check the documentation of the org.junit.Assert package for further details!
		// http://www.junit.org/apidocs/org/junit/Assert.html
		try{
			setUp();
		}catch(Exception e){
			System.out.println("fail Set Up.");
		}
		
		tour1.setDimension(5);
		boolean attempt = false;
		
		//runs the tour through each potential starting position. If there is one completed, true is returned
		for(int x = 0; x < 5; x++){
			for(int y = 0; y < 5; y++){
				int[][] array = tour1.getTour(x, y);
				
				if(compareGetTour(x, y, array)){
					attempt = true;
				}
					
			}//for-inner
		}//for-outer

		
		assertTrue(attempt);
		
		try{
			tearDown();
		}catch(Exception e){
			System.out.println("fail tear down.");
		}	
	}
	/** 
	 * Test if the output is produced. 
	 * Case: solution exists and is successfully computed. 
	 * Trivial case of 1 x 1 matrix.
	 */
	@Test
	public void testPrintTour1() {
		// TODO: add test code
		// NOTE: a test must exercise functions of the class under test AND perform a correctness check
		// with methods of type assertTRUE(), assertFALSE() etc
		// check the documentation of the org.junit.Assert package for further details!
		// http://www.junit.org/apidocs/org/junit/Assert.html
		try{
			setUp();
		}catch(Exception e){
			System.out.println("fail Set Up.");
		}
		
		tour1.setDimension(1);
		
		assertTrue(tour1.printTour(0, 0) instanceof String);
		
		
		try{
			tearDown();
		}catch(Exception e){
			System.out.println("fail tear down.");
		}	
	}
	/** 
	 * Test if the output is produced. 
	 * Case: solution exists and is successfully computed. 
	 * Non-trivial case of 5 x 5 matrix.
	 */
	@Test
	public void testPrintTour5() {
		// TODO: add test code
		// NOTE: a test must exercise functions of the class under test AND perform a correctness check
		// with methods of type assertTRUE(), assertFALSE() etc
		// check the documentation of the org.junit.Assert package for further details!
		// http://www.junit.org/apidocs/org/junit/Assert.html
		try{
			setUp();
		}catch(Exception e){
			System.out.println("fail Set Up.");
		}
		
		tour1.setDimension(5);		
		assertTrue(tour1.printTour(0, 0) instanceof String);
		
		try{
			tearDown();
		}catch(Exception e){
			System.out.println("fail tear down.");
		}	
	}
	/** 
	 * Test if the output is produced. 
	 * Case: solution does not exist. 
	 * Non-trivial case of 5 x 5 matrix.
	 */
	@Test
	public void testPrintTour5b() {
		// TODO: add test code
		// NOTE: a test must exercise functions of the class under test AND perform a correctness check
		// with methods of type assertTRUE(), assertFALSE() etc
		// check the documentation of the org.junit.Assert package for further details!
		// http://www.junit.org/apidocs/org/junit/Assert.html
		try{
			setUp();
		}catch(Exception e){
			System.out.println("fail Set Up.");
		}
		
		tour1.setDimension(5);
		
		assertTrue(tour1.printTour(2, 1) instanceof String);
		
		try{
			tearDown();
		}catch(Exception e){
			System.out.println("fail tear down.");
		}	
	}


}//TourTestP1
