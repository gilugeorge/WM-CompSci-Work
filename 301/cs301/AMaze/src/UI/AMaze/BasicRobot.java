package UI.AMaze;

import UI.AMaze.Cells;
import UI.AMaze.HitObstacleException;
import UI.AMaze.Maze;
import UI.AMaze.MazeBuilder;
import UI.AMaze.Robot;
import UI.AMaze.UnsupportedArgumentException;
import UI.AMaze.UnsupportedMethodException;


public class BasicRobot implements Robot {
	int battery = 1000;
	int steps;
	
	Maze maze;
	//GraphicsWrapper gc;

	/**Constructor
	 * 
	 * @param position The current position of the robot
	 * @param direction The direction that the robot head is pointing
	 * @param battery The amount of energy remaining
	 */
	BasicRobot(Maze m){
		maze = m;
		//testCode = 2;
	}

	/**
	 * Turn robot on the spot. If given degree is not supported by existing robot, method throws a corresponding exception. 
	 * For example, a robot may only be able to turn left (90) degrees or right (-90) degrees. The angle is measured in a counterclockwise manner
	 * as it is common for polar coordinates.
	 * @param degree specifies in which direction to turn (negative values turn right, positive values turn left), actual implementation may be limited to a few discrete value settings. 
	 * @throws UnsupportedArgumentException if the robot does not support a given degree value. 
	 */
	public void rotate(int degree) throws UnsupportedArgumentException {
		if(getCurrentBatteryLevel() > 0){
			degree = degree/90;
			maze.rotate(degree);
		}
		
		battery -= 2; //subtract battery value
	}//rotate
	
	/**
	 * Moves robot forward or backward a given number of steps. A step matches a single cell.
	 * Since a robot may only have a distance sensor in its front, driving backwards may happen blindly as distance2Obstacle may not provide values for that direction.
	 * If the robot runs out of energy somewhere on its way, it stops, which can be checked by hasStopped() and by checking the battery level. 
	 * @param distance is the number of cells to move according to the robots current direction if forward = true, opposite direction if forward = false
	 * @param forward specifies if the robot should move forward (true) or backward (false)
	 * @throws HitObstacleException if robot hits an obstacle like a wall or border, which also make the robot stop, i.e. hasStopped() = true 
	 */
	public void move(int distance, boolean forward) throws HitObstacleException {
			
			for(int i = 0; i < distance; i++){
				if(hasStopped() == true){
					break;
				}				
				try {
					if(distanceToObstacleAhead() == 0){
						break;
					}
				} catch (UnsupportedMethodException e) {
					e.printStackTrace();
				}
				
				if(forward == true){
					maze.walk(1);
					battery -= getEnergyForStepForward();
				}else{
					maze.walk(-1);
					battery -= getEnergyForStepForward();
				}
			}//for
		
	}//move
	
	/**
	 * Provides the current position as (x,y) coordinates for the maze cell as an array of length 2 with [x,y].
	 * Note that 0 <= x < width, 0 <= y < height of the maze. 
	 * @return array of length 2, x = array[0], y=array[1]
	 */
	public int[] getCurrentPosition() {
		int[] position = {maze.px, maze.py};
		return position;
	}//getCurrentPosition
	
	/**
	 * Tells if current position is at the goal. Used to recognize termination of a search.
	 * Note that goal recognition is limited by the sensing functionality of robot such that isAtGoal returns false
	 * even if it is positioned directly at the exit but has no distance sensor towards the exit direction. 
	 * @return true if robot is at the goal and has a distance sensor in the direction of the goal, false otherwise
	 */
	public boolean isAtGoal() {

		int n;
		int[] masks = Cells.getMasks();
		for (n = 0; n < 4; n++) {
			// skip this direction if there is a wall or border
			if (maze.mazecells.hasMaskedBitsGTZero(maze.px, maze.py, masks[n]))
				continue;
			// stop if position in this direction is end position
			if (maze.isEndPosition(maze.px + MazeBuilder.dirsx[n], maze.py
					+ MazeBuilder.dirsy[n])) {
				maze.rotateTo(n);
				try {
					move(1, true);
				} catch (HitObstacleException e) {
					e.printStackTrace();
				}
				return true;
			}
		}

		return false;
	}// isAtGoal
	
	/**
	 * Provides the current direction as (dx,dy) values for the robot as an array of length 2 with [dx,dy].
	 * Note that dx,dy are elements of {-1,0,1} and as in bitmasks masks in Cells.java and dirsx,dirsy in MazeBuilder.java.
	 * 
	 * @return array of length 2, dx = array[0], dy=array[1]
	 */	
	public int[] getCurrentDirection() {
		
		int[] direction = {maze.dx, maze.dy};
		return direction;
	}//getCurrentDirection
	
	/**
	 * The robot has a given battery level (energy level) that it draws energy from during operations. 
	 * The particular energy consumption is device dependent such that a call for distance2Obstacle may use less energy than a move forward operation.
	 * If battery level <= 0 then robot stops to function and hasStopped() is true.
	 * @return current battery level, level is > 0 if operational. 
	 */
	public float getCurrentBatteryLevel() {
		return battery;
	}//getCurrentBatteryLevel
	
	/**
	 * Gives the energy consumption for a full 360 degree rotation.
	 * Scaling by other degrees approximates the corresponding consumption. 
	 * @return energy for a full rotation
	 */
	public float getEnergyForFullRotation() {
		return 8;
	}//getEnergyForFullRotation
	
	/**
	 * Gives the energy consumption for moving 1 step forward.
	 * For simplicity, we assume that this equals the energy necessary to move 1 step backwards and that scaling by a larger number of moves is 
	 * approximately the corresponding multiple.
	 * @return energy for a single step forward
	 */
	public float getEnergyForStepForward() {
		return 3;
	}//getEnergyForStepForward
	
	/**
	 * Tells if the robot has stopped for reasons like lack of energy, hitting an obstacle, etc.
	 * @return true if the robot has stopped, false otherwise
	 */
	public boolean hasStopped() { //TODO:

		if (battery <= 0 /*&& maze.mazecells.canGo(maze.px, maze.py, maze.dx, maze.dy) && maze.mazecells.canGo(maze.px, maze.py, -maze.dx, -maze.dy)*/) {
			return true;
		}else
			return false;
	}// hasStopped
	
	/**
	 * Tells if a sensor can identify the goal in the robot's current forward direction from the current position.
	 * @return true if the goal (here: exit of the maze) is visible in a straight line of sight
	 * @throws UnsupportedMethodException if robot has no sensor in this direction
	 */
	public boolean canSeeGoalAhead() throws UnsupportedMethodException {
		int[] temp = { maze.px, maze.py }; // create temp position
		int[] exit = maze.getExit(); // get exit positions
		//If blocks to account for every possible direction, once within a while loop,
		//our temp position will continue shifting until Goal coordinates have been reached.
		// Going North
		if (maze.dx == 0) {
			if (maze.dy == 1) {
				// System.out.println("facing north within while(basicRobot Ahead)"); TODO:
				//System.out.println("1");
				while (temp[0] > -1
						&& temp[1] > -1
						&& temp[0] < maze.mazew
						&& temp[1] < maze.mazeh
						&& maze.mazecells.hasWallOnBottom(temp[0], temp[1]) == false) {
					if (temp[0] == exit[0] && temp[1] == exit[1]) {
						battery--;
						return true;
					} else
						temp[1]++;
				}// while
			}
		}
		// Going South
		if (maze.dx == 0) {
			if (maze.dy == -1) {
				// System.out.println("facing South within while(basicRobot Ahead)");
				// //TODO:
				//System.out.println("2");
				while (temp[0] > -1
						&& temp[1] > -1
						&& temp[0] < maze.mazew
						&& temp[1] < maze.mazeh
						&& maze.mazecells.hasWallOnTop(temp[0], temp[1]) == false) {
					if (temp[0] == exit[0] && temp[1] == exit[1]) {
						battery--;
						return true;
					} else
						temp[1]--;
				}// while
			}
		}
		// Going East
		if (maze.dx == 1) {
			if (maze.dy == 0) {
				// System.out.println("facing East within while(basicRobot Ahead)");
				// //TODO:
				//System.out.println("3");
				while (temp[0] > -1
						&& temp[1] > -1
						&& temp[0] < maze.mazew
						&& temp[1] < maze.mazeh
						&& maze.mazecells.hasWallOnRight(temp[0], temp[1]) == false) {
					if (temp[0] == exit[0] && temp[1] == exit[1]) {
						battery--;
						return true;
					} else
						temp[0]++;
				}// while
			}
		}
		// Going West
		if (maze.dx == -1) {
			if (maze.dy == 0) {
				// System.out.println("facing West within while(basicRobot Ahead)");
				// //TODO:
				//System.out.println("4");
				while (temp[0] > -1
						&& temp[1] > -1
						&& temp[0] < maze.mazew
						&& temp[1] < maze.mazeh
						&& maze.mazecells.hasWallOnLeft(temp[0], temp[1]) == false) {
					if (temp[0] == exit[0] && temp[1] == exit[1]) {
						battery--;
						return true;
					} else
						temp[0]--;
				}// while
			}
		}
		//System.out.println("false");
		battery--;
		return false;
	}//canSeeGoalAhead
	
	/**
	 * Methods analogous to canSeeGoalAhead but for a the robot's current backward direction
	 * @return true if the goal (here: exit of the maze) is visible in a straight line of sight
	 * @throws UnsupportedMethodException if robot has no sensor in this direction
	 */
	public boolean canSeeGoalBehind() throws UnsupportedMethodException {
		return false;
	}//canSeeGoalBehind
	
	/**
	 * Methods analogous to canSeeGoalAhead but for the robot's current left direction (left relative to forward)
	 * @return true if the goal (here: exit of the maze) is visible in a straight line of sight
	 * @throws UnsupportedMethodException if robot has no sensor in this direction
	 */
	public boolean canSeeGoalOnLeft() throws UnsupportedMethodException {
		int[] temp = {maze.px, maze.py}; 	//create temp position
		int[] exit = maze.getExit(); // get exit positions
		
		//If blocks to account for every possible direction, once within a while loop,
		//our temp position will continue shifting until Goal coordinates have been reached.
		//Facing North 
		if(maze.dx == 0){
			if(maze.dy == 1){
				//System.out.println("facing north within while(basicRobot Left)");TODO:
				System.out.println("l1");
				while(temp[0] > -1 && temp[1] > -1 && temp[0] < maze.mazew && temp[1] < maze.mazeh && maze.mazecells.hasWallOnLeft(temp[0], temp[1]) == false ){
					if (temp[0] == exit[0] && temp[1] == exit[1]) {
						battery--;
						return true;
					} else
						temp[0]--;
				}//while
			}
		}
		//Facing South
		if(maze.dx == 0){
			if(maze.dy == -1){
				//System.out.println("facing South within while(basicRobot Left)");TODO:
				System.out.println("l2");
				while(temp[0] > -1 && temp[1] > -1 && temp[0] < maze.mazew && temp[1] < maze.mazeh && maze.mazecells.hasWallOnRight(temp[0], temp[1]) == false ){
					if (temp[0] == exit[0] && temp[1] == exit[1]) {
						battery--;
						return true;
					} else					
						temp[0]++;
				}//while
			}
		}
		//Going East
		if(maze.dx == 1){
			if(maze.dy == 0){
				//System.out.println("facing East within while(basicRobot Left)");TODO:
				System.out.println("l3");
				while(temp[0] > -1 && temp[1] > -1 && temp[0] < maze.mazew && temp[1] < maze.mazeh && maze.mazecells.hasWallOnBottom(temp[0], temp[1]) == false ){
					if (temp[0] == exit[0] && temp[1] == exit[1]) {
						battery--;
						return true;
					} else
						temp[1]++;
				}//while
			}
		}
		//Going West
		if(maze.dx == -1){
			if(maze.dy == 0){
				//System.out.println("facing West within while(basicRobot Left)"); TODO:
				System.out.println("l4");
				while(temp[0] > -1 && temp[1] > -1 && temp[0] < maze.mazew && temp[1] < maze.mazeh && maze.mazecells.hasWallOnTop(temp[0], temp[1]) == false ){
					if (temp[0] == exit[0] && temp[1] == exit[1]) {
						battery--;
						return true;
					} else
						temp[1]--;
				}//while
			}
		}
		System.out.println("lfalse");
		battery--;
		return false;
	}//canSeeGoalOnLeft
	
	/**
	 * Methods analogous to canSeeGoalAhead but for the robot's current right direction (right relative to forward)
	 * @return true if the goal (here: exit of the maze) is visible in a straight line of sight
	 * @throws UnsupportedMethodException if robot has no sensor in this direction
	 */
	public boolean canSeeGoalOnRight() throws UnsupportedMethodException {
		return false;
	}//canSeeGoalOnRight

	/**
	 * Tells the distance to an obstacle (a wall or border) for a the robot's current forward direction.
	 * Distance is measured in the number of cells towards that obstacle, e.g. 0 if current cell has a wall in this direction
	 * @return number of steps towards obstacle if obstacle is visible in a straight line of sight, Integer.MAX_VALUE otherwise
	 * @throws UnsupportedArgumentException if not supported by robot
	 */
	public int distanceToObstacleAhead() throws UnsupportedMethodException {		
		int distance = 0;		//create distance counter
		int[] temp = {maze.px, maze.py}; 	//create temp position
		
		//If blocks to account for every possible direction, once within a while loop,
		//our temp position will continue shifting until it hits a wall.
		//Facing North
		if(maze.dx == 0){
			if(maze.dy == 1){
				//System.out.println("facing north within while(basicRobot Ahead)"); //TODO:
				
				while(temp[0] > -1 && temp[1] > -1 && temp[0] < maze.mazew && temp[1] < maze.mazeh && maze.mazecells.hasWallOnBottom(temp[0], temp[1]) == false ){
					
					temp[1]++;
					distance++;
				}//while
			}
		}		
		//Going South
		if(maze.dx == 0){
			if(maze.dy == -1){
				//System.out.println("facing South within while(basicRobot Ahead)"); //TODO:
				
				while(temp[0] > -1 && temp[1] > -1 && temp[0] < maze.mazew && temp[1] < maze.mazeh && maze.mazecells.hasWallOnTop(temp[0], temp[1]) == false ){
					
					temp[1]--;
					distance++;
				}//while
			}
		}
		//Going East
		if(maze.dx == 1){
			if(maze.dy == 0){
				//System.out.println("facing East within while(basicRobot Ahead)"); //TODO:
				
				while(temp[0] > -1 && temp[1] > -1 && temp[0] < maze.mazew && temp[1] < maze.mazeh && maze.mazecells.hasWallOnRight(temp[0], temp[1]) == false ){
					
					temp[0]++;
					distance++;
				}//while
			}
		}
		//Going West
		if(maze.dx == -1){
			if(maze.dy == 0){
				//System.out.println("facing West within while(basicRobot Ahead)"); //TODO:
				
				while(temp[0] > -1 && temp[1] > -1 && temp[0] < maze.mazew && temp[1] < maze.mazeh && maze.mazecells.hasWallOnLeft(temp[0], temp[1]) == false ){
					
					temp[0]--;
					distance++;
				}//while
			}
		}

		battery--;
		return distance;
	}//distanceToObstacleAhead
	
	/**
	 * Methods analogous to distanceToObstacleAhead but for the robot's current left direction (left relative to forward)
	 * @return number of steps towards obstacle if obstacle is visible in a straight line of sight, Integer.MAX_VALUE otherwise
	 * @throws UnsupportedArgumentException if not supported by robot
	 */
	public int distanceToObstacleOnRight() throws UnsupportedMethodException {
		return 0;
	}//distanceToObstacleOnRight
	
	

	/**
	 * Methods analogous to distanceToObstacleAhead but for the robot's current right direction (right relative to forward)
	 * @return number of steps towards obstacle if obstacle is visible in a straight line of sight, Integer.MAX_VALUE otherwise
	 * @throws UnsupportedArgumentException if not supported by robot
	 */
	public int distanceToObstacleOnLeft() throws UnsupportedMethodException {
		int distance = 0;		//create distance counter
		int[] temp = {maze.px, maze.py}; 	//create temp position
		
		//If blocks to account for every possible direction, once within a while loop,
		//our temp position will continue shifting until it hits a wall.		
		//Facing North 
		if(maze.dx == 0){
			if(maze.dy == 1){
				//System.out.println("facing north within while(basicRobot Left)");TODO:
				
				while(temp[0] > -1 && temp[1] > -1 && temp[0] < maze.mazew && temp[1] < maze.mazeh && maze.mazecells.hasWallOnLeft(temp[0], temp[1]) == false ){
	
					temp[0]--;
					distance++;
				}//while
			}
		}
		//Facing South
		if(maze.dx == 0){
			if(maze.dy == -1){
				//System.out.println("facing South within while(basicRobot Left)");TODO:
				
				while(temp[0] > -1 && temp[1] > -1 && temp[0] < maze.mazew && temp[1] < maze.mazeh && maze.mazecells.hasWallOnRight(temp[0], temp[1]) == false ){
										
					temp[0]++;
					distance++;
				}//while
			}
		}
		//Going East
		if(maze.dx == 1){
			if(maze.dy == 0){
				//System.out.println("facing East within while(basicRobot Left)");TODO:
				
				while(temp[0] > -1 && temp[1] > -1 && temp[0] < maze.mazew && temp[1] < maze.mazeh && maze.mazecells.hasWallOnBottom(temp[0], temp[1]) == false ){
					
					temp[1]++;
					distance++;
				}//while
			}
		}
		//Going West
		if(maze.dx == -1){
			if(maze.dy == 0){
				//System.out.println("facing West within while(basicRobot Left)"); TODO:
				
				while(temp[0] > -1 && temp[1] > -1 && temp[0] < maze.mazew && temp[1] < maze.mazeh && maze.mazecells.hasWallOnTop(temp[0], temp[1]) == false ){
					
					temp[1]--;
					distance++;
				}//while
			}
		}
		
		battery--;
		return distance;
	}//distanceToObstacleOnRight
	
	/**
	 * Methods analogous to distanceToObstacleAhead but for a the robot's current backward direction
	 * @return number of steps towards obstacle if obstacle is visible in a straight line of sight, Integer.MAX_VALUE otherwise
	 * @throws UnsupportedArgumentException if not supported by robot
	 */
	public int distanceToObstacleBehind() throws UnsupportedMethodException {
		return 0;
	}//distanceToObstacleBehind
	
	/**
	 * Returns the size of the of maze.
	 */
	public int[] getMazeSize(){
		int[] size = {maze.mazew, maze.mazeh};
		return size;		
	}//getMazeSize
	
	/**
	 * Solves Using distance matrix
	 */
	public void solve(){
		maze.solving = true;
		while(maze.solving){
			maze.solveStep();
		}
		battery -= maze.energyUsed;
		steps = maze.steps;
	}//solve
	
	/**
	 * Get Energy Used in Wizard
	 */
	public int getEnergyUsed(){
		return maze.energyUsed;
	}
	
	/**
	 * Get Number of Steps done in Wizard
	 */
	public int getSteps(){
		return maze.steps;
	}
	
	/**
	 * Get direction robot is facing.
	 */
	public int[] getDirection(){
		int[] d = {maze.dx, maze.dy};
		return d;
	}
	
	/**
	 * Get Position of robot.
	 */
	public int[] getPosition(){
		int[] pos = {maze.px, maze.py};
		return pos;
	}
}
