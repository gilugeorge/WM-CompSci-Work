package UI.AMaze;

import java.io.Serializable;

//import java.awt.Color;

/**
 * 
 * This code is refactored code from Maze.java by Paul Falstad, www.falstad.com, Copyright (C) 1998, all rights reserved
 * Paul Falstad granted permission to modify and use code for teaching purposes.
 * Refactored by Peter Kemper
 */
public class Seg implements Serializable{

	private static final long serialVersionUID = 1L;
	public int x, y, dx, dy, dist;
	public int col; //change from Graphics to int
	public boolean partition, seen;

	/**
	 * Constructor
	 * @param psx
	 * @param psy
	 * @param pdx
	 * @param pdy
	 * @param cl
	 * @param cc
	 */
	Seg(int psx, int psy, int pdx, int pdy, int cl, int cc) {
		x = psx;
		y = psy;
		dx = pdx;
		dy = pdy;
		dist = cl;
		seen = false;
		cl /= 4;
		//int add = (dx != 0) ? 1 : 0;
		//int part1 = cl & 7;
		int part2 = ((cl >> 3) ^ cc) % 6;
		//int val1 = ((part1 + 2 + add) * 70)/8 + 80;
		switch (part2) {
		case 0: col = 3 ; break; //red
		case 1: col = 4 ; break; //green
		case 2: col = 5 ; break; //blue
		case 3: col = 6 ; break; //yellow
		case 4: col = 7 ; break; //cyan
		case 5: col = 8 ; break; //pink
		}
	}

	int getDir() {
		if (dx != 0)
			return (dx < 0) ? 1 : -1;
		return (dy < 0) ? 2 : -2;
	}
}

