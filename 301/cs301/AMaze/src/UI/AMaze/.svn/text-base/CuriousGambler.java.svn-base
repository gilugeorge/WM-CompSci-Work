package UI.AMaze;

import java.util.Random;

import android.os.Handler;

public class CuriousGambler implements RobotDriver{
	BasicRobot robot;
	
//	public CuriousGambler(GraphicsWrapper gw) {
//		robot = new BasicRobot(gw); //construct new robot
//		h = gw.s.robotHandler;
//	}

	/**
	 * Assigns a robot platform to the driver. Not alsl robot configurations may be suitable such that the method 
	 * will throw an exception if the robot does not match minimal configuration requirements, e.g. providing a sensor
	 * to measure the distance to an object in a particular direction. 
	 * @param r robot to operate
	 * @throws UnsuitableRobotException if driver cannot operate the given robot
	 */
	public void setRobot(Robot r) throws UnsuitableRobotException {
		
		robot = (BasicRobot) r;
		robot.battery = 1000;
	}

	/**
	 * Drives the robot towards the exit given it exists and given the robot's energy supply lasts long enough. 
	 * @return true if driver successfully reaches the exit, false otherwise
	 * @throws exception if robot stopped due to an accident
	 */
	public boolean drive2Exit() throws Exception {
		//create random number
		Random random = new Random();
		int r;
		int[] pos = new int[2];
		int[] dir = new int[2];
		
		//create 2D array to hold visited values and fill with 0's
		int[] size = robot.getMazeSize();
		int[][] visited = new int[size[0]][size[1]];
		for(int i = 0; i < size[0]; i++){
			for(int j = 0; j < size[1]; j++){
				visited[i][j] = 0;
			}
		}
		
		
		while(robot.isAtGoal() == false){
			//gets the robots position, direction, and creates a random number to be used
			pos = robot.getCurrentPosition();
			dir = robot.getCurrentDirection();
			r = random.nextInt(2);
			
			if(robot.getCurrentBatteryLevel() <= 0){
				return false;
			}
			//Check which directions it can go, then check which one has less, if equal, then random direction
			try {
				if(robot.distanceToObstacleAhead() == 0 && robot.distanceToObstacleOnLeft() == 0){
					robot.rotate(90);
					robot.rotate(90);
				}else if(dir[0] == 0){ //North or South Direction
					if(dir[1] == 1){   //Facing North
						if(pos[0]-1 > -1 && pos[1]+1 > -1 && pos[0]-1 < size[0]-1 && pos[1]+1 < size[1]-1 && visited[pos[0]][pos[1]+1] > visited[pos[0]-1][pos[1]]){ //when ahead has more
							robot.move(1, true);
							robot.steps++;
						}
						else if(pos[0]-1 > -1 && pos[1]+1 > -1 && pos[0]-1 < size[0]-1 && pos[1]+1 < size[1]-1 && visited[pos[0]][pos[1]+1] < visited[pos[0]-1][pos[1]]){ //when left
							robot.rotate(90);
							robot.move(1, true);
							robot.steps++;
						}else{
							randomMove(r);
						}						
					}
					if(dir[1] == -1){   //Facing South
						if(pos[0]+1 > -1 && pos[1]-1 > -1 && pos[0]+1 < size[0]-1 && pos[1]-1 < size[1]-1 && visited[pos[0]][pos[1]-1] > visited[pos[0]+1][pos[1]]){ //when ahead has more
							robot.move(1, true);
							robot.steps++;
						}
						else if(pos[0]+1 > -1 && pos[1]-1 > -1 && pos[0]+1 < size[0]-1 && pos[1]-1 < size[1]-1 && visited[pos[0]][pos[1]-1] < visited[pos[0]+1][pos[1]]){ //when left
							robot.rotate(90);
							robot.move(1, true);
							robot.steps++;
						}else{
							randomMove(r);
						}						
					}				
				}//End N-S check
				else{
					if(dir[0] == 1){ //Facing East
						if(pos[0]+1 > -1 && pos[1]+1 > -1 && pos[0]+1 < size[0]-1 && pos[1]+1 < size[1]-1 && visited[pos[0]+1][pos[1]] > visited[pos[0]][pos[1]+1]){ //when ahead has more
							robot.move(1, true);
							robot.steps++;
						}
						else if(pos[0]+1 > -1 && pos[1] > -1 && pos[0]+1 < size[0]-1 && pos[1]+1 < size[1]-1 && visited[pos[0]+1][pos[1]] < visited[pos[0]][pos[1]+1]){ //when left
							robot.rotate(90);
							robot.move(1, true);
							robot.steps++;
						}else{
							randomMove(r);
						}	
					}
					if(dir[0] == -1){ //Facing West
						if(pos[0]-1 > -1 && pos[1]-1 > -1 && pos[0]-1 < size[0]-1 && pos[1]-1 < size[1]-1 && visited[pos[0]-1][pos[1]] > visited[pos[0]][pos[1]-1]){ //when ahead has more
							robot.move(1, true);
							robot.steps++;
						}
						else if(pos[0]-1 > -1 && pos[1]-1 > -1 && pos[0]-1 < size[0]-1 && pos[1]-1 < size[1]-1 && visited[pos[0]-1][pos[1]] < visited[pos[0]][pos[1]-1]){ //when left
							robot.rotate(90);
							robot.move(1, true);
							robot.steps++;
						}else{
							randomMove(r);
						}	
					}
				}
			} catch (UnsupportedMethodException e) {
				e.printStackTrace();
			} catch (UnsupportedArgumentException e) {
				e.printStackTrace();
			} catch (HitObstacleException e) {
				e.printStackTrace();
			}//End E-W check
			
		}//while
		
		
		return true;
	}//drive2Exit	
	
	/**
	 * Does the random movement when spaces are equal.
	 * @param r
	 * @throws HitObstacleException 
	 * @throws UnsupportedMethodException 
	 * @throws UnsupportedArgumentException 
	 */
	private void randomMove(int r) throws UnsupportedMethodException, HitObstacleException, UnsupportedArgumentException {

		// move forward
		if (r == 0) {
			if (robot.distanceToObstacleAhead() != 0) {
				robot.move(1, true);
				robot.steps++;
			}
		}
		// move left
		if (r == 1) {
			if (robot.distanceToObstacleOnLeft() != 0) {
				robot.rotate(90);
				robot.move(1, true);
				robot.steps++;
			}
		}
	}//randomMove

	/**
	 * Returns the total energy consumption of the journey
	 */
	public float getEnergyConsumption() {
		
		return 1000-robot.getCurrentBatteryLevel();
	}

	/**
	 * Returns the total length of the journey in number of cells traversed. The initial position counts as 0. 
	 */
	public int getPathLength() {
		
		return  robot.steps;
	}

}
