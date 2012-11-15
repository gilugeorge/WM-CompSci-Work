package UI.AMaze;

import UI.AMaze.Robot;
import UI.AMaze.RobotDriver;
import UI.AMaze.UnsuitableRobotException;
import java.lang.Exception;

import android.os.Handler;

public class Wizard implements RobotDriver{
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
		
		//Call the solve function from robot.
		//robot uses a modified version of the solveStep() method in 
		//the Maze class.
		robot.solve();
		return true;
	}

	/**
	 * Returns the total energy consumption of the journey
	 */
	public float getEnergyConsumption() {
		
		return robot.getEnergyUsed();
	}

	/**
	 * Returns the total length of the journey in number of cells traversed. The initial position counts as 0. 
	 */
	public int getPathLength() {
		
		return robot.getSteps();
	}

}
