package UI.AMaze;


import java.util.Random;

import android.os.Handler;

public class Gambler implements RobotDriver{
	BasicRobot robot;


	/**
	 * Assigns a robot platform to the driver. Not also robot configurations may be suitable such that the method 
	 * will throw an exception if the robot does not match minimal configuration requirements, e.g. providing a sensor
	 * to measure the distance to an object in a particular direction. 
	 * @param r robot to operate
	 * @throws UnsuitableRobotException if driver cannot operate the given robot
	 */
	public void setRobot(Robot r) throws UnsuitableRobotException {
		robot = (BasicRobot) r;
		robot.battery = 1000;
	}//setRobot
	
	/**
	 * Drives the robot towards the exit given it exists and given the robot's energy supply lasts long enough. 
	 * @return true if driver successfully reaches the exit, false otherwise
	 * @throws exception if robot stopped due to an accident
	 */
	public boolean drive2Exit() throws Exception {
		Random random = new Random();
		int r;
		
		//System.out.println("within solution method");
		
		while(robot.isAtGoal() == false){
			
			//System.out.println("within while loop1");
			//System.out.println("Battery Level:" +robot.getCurrentBatteryLevel());
			
			if(robot.getCurrentBatteryLevel() <= 0){
				return false;
			}
			
			//Will take the random number and find the corresponding movement
			//if-block to perform the appropriate movement.
			r = random.nextInt(4);			
			
			// move forward
			if (r == 0) {				
				try {
					if (robot.distanceToObstacleAhead() == 0) {
						continue;
					}else{
						robot.move(1, true);						
						robot.steps += 1;
					}
				} catch (HitObstacleException e) {
					e.printStackTrace();
				} catch (UnsupportedMethodException e1) {
					e1.printStackTrace();
				}
			}
			
			//move right
			if(r == 1){
				try {
					
					robot.rotate(-90);
					if (robot.distanceToObstacleAhead() == 0){
						continue;
					}
					robot.move(1, true);
					robot.steps += 1;
				} catch (HitObstacleException e) {
					e.printStackTrace();
				}catch (UnsupportedArgumentException e) {
					e.printStackTrace();
				} catch (UnsupportedMethodException e) {
					e.printStackTrace();
				}
			}
			
			//move left
			if(r == 2){
				try {
					robot.rotate(90);
					robot.move(1, true);
					robot.steps += 1;
				} catch (UnsupportedArgumentException e) {
					e.printStackTrace();
				} catch (HitObstacleException e) {
					e.printStackTrace();
				}
			}
			
			//move backwards
			if(r == 3){
				try {
					robot.rotate(180);
					if (robot.distanceToObstacleAhead() == 0) {
						continue;
					}else{
						robot.move(1, true);
						robot.steps += 1;
					}
				} catch (HitObstacleException e) {
					e.printStackTrace();
				} catch (UnsupportedMethodException e1) {
					e1.printStackTrace();
				} catch (UnsupportedArgumentException e) {
					e.printStackTrace();
				}
			}
			
		}//while
		
		return true;
	}

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
		
		return robot.steps;
	}//getPathLength

}
