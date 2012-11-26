package UI.AMaze;

import java.lang.Exception;

import android.os.Handler;

public class WallFollower implements RobotDriver{
	BasicRobot robot;
	

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
		
		while (robot.isAtGoal() == false) {// TODO: while not at end
			//System.out.println("within robot not at goal while loop");
			try {
				//System.out.println("getting tried");
				if (robot.canSeeGoalAhead()) {
					System.out.println("exit 1");
					robot.move(1, true);
					robot.steps++;
				} else if (robot.canSeeGoalOnLeft()) {
					System.out.println("exit 2");
					robot.rotate(90);
					robot.move(1, true);
					robot.steps++;
				} else if (robot.distanceToObstacleOnLeft() != 0) {
					System.out.println("exit 3");
					robot.rotate(90);
					robot.move(1, true);
					robot.steps++;
				} else if (robot.distanceToObstacleAhead() != 0) {
					System.out.println("exit 4");
					robot.move(1, true);
					robot.steps++;
				} else {
					System.out.println("exit 5");
					robot.rotate(180);
				}
				System.out.println("before the catches");
			} catch (UnsupportedMethodException e) {
				System.out.println("exception 1");
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (UnsupportedArgumentException e) {
				System.out.println("exception 2");
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (HitObstacleException e) {
				System.out.println("exception 3");
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println("WTFFFFFFFFFFFFFFFFFFFFFF");
		}
		System.out.println("if i am here i didnt do anything. Sadface.");
		return true;
	}
	
	/**
	 * Returns the total energy consumption of the journey
	 */
	public float getEnergyConsumption() {
		
		return 1000-robot.getCurrentBatteryLevel();
	}//getEnergyConsumption

	/**
	 * Returns the total length of the journey in number of cells traversed. The initial position counts as 0. 
	 */
	public int getPathLength() {
		
		return robot.steps;
	}//getPathLength

}
