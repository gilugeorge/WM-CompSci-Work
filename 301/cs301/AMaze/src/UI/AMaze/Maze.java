package UI.AMaze;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

import android.content.Context;
import android.graphics.Bitmap;
import android.util.Log;

/**
* Class handles the user interaction for the maze. 
* It implements a state-dependent behavior that controls the display and reacts to key board input from a user. 
* After refactoring the original code from an applet into a panel, it is wrapped by a MazeApplication to be a java application 
* and a MazeApp to be an applet for a web browser. At this point user keyboard input is first dealt with a key listener
* and then handed over to a Maze object by way of the keyDown method.
*
* This code is refactored code from Maze.java by Paul Falstad, www.falstad.com, Copyright (C) 1998, all rights reserved
* Paul Falstad granted permission to modify and use code for teaching purposes.
* Refactored by Peter Kemper
*/
// MEMO: original code: public class Maze extends Applet {
public class Maze implements Serializable{
	final String tag = "Maze";
	
	/**Serializable Information
	 * 
	 * @param oos
	 * @throws IOException
	 */
	private void writeObject(ObjectOutputStream o) throws IOException{
		//o.writeInt(5);
		o.writeObject(gc);
		o.writeObject(mazecells);
		o.writeObject(seencells);
		o.writeObject(mazedists);
		o.writeObject(firstpersondrawer);
		o.writeObject(mapdrawer);
		o.writeInt(energyUsed);
		o.writeInt(steps);
		o.writeInt(mazew);
		o.writeInt(mazeh);
		o.writeInt(dx);
		o.writeInt(dy);
		o.writeInt(px);
		o.writeInt(py);
		o.writeBoolean(setRandom);
		o.writeObject(rset);
		o.writeInt(zscale);
		o.writeBoolean(done);
		o.writeBoolean(showMaze);
		o.writeBoolean(showSolution);
		o.writeBoolean(solving);
		o.writeInt(viewx);
		o.writeInt(viewy);
		o.writeInt(ang);
		o.writeInt(walk_step);
		o.writeInt(view_dx);
		o.writeInt(view_dy);
		o.writeBoolean(deepdebug);
		o.writeBoolean(all_visible);
		o.writeBoolean(new_game);
		o.writeBoolean(map_mode);
		//o.writeObject(mazebuilder);
		o.writeInt(exitx);
		o.writeInt(exity);
		
		
	}
	
	/**Serializable Information
	 * 
	 * @param oos
	 * @throws IOException
	 * @throws ClassNotFoundException
	 */
	private void readObject(ObjectInputStream oos) throws IOException, ClassNotFoundException{
		//oos.readInt();
		this.gc = (GraphicsWrapper) oos.readObject();
		this.mazecells = (Cells) oos.readObject();
		this.seencells = (Cells) oos.readObject();
		this.mazedists = (int[][]) oos.readObject();
		this.firstpersondrawer = (FirstPersonDrawer) oos.readObject();
		this.mapdrawer = (MapDrawer) oos.readObject();
		this.energyUsed = oos.readInt();
		this.steps = oos.readInt();
		this.mazew = oos.readInt();
		this.mazeh = oos.readInt();
		this.dx = oos.readInt();
		this.dy = oos.readInt();
		this.px = oos.readInt();
		this.py = oos.readInt();
		this.setRandom = oos.readBoolean();
		this.rset = (RangeSet) oos.readObject();
		this.zscale = oos.readInt();
		this.done=oos.readBoolean();
		this.showMaze = oos.readBoolean();
		this.showSolution = oos.readBoolean();
		this.solving = oos.readBoolean();
		this.viewx = oos.readInt();
		this.viewy = oos.readInt();
		this.ang = oos.readInt();
		this.walk_step = oos.readInt();
		this.view_dx = oos.readInt();
		this.view_dy = oos.readInt();
		this.deepdebug = oos.readBoolean();
		this.all_visible = oos.readBoolean();
		this.new_game = oos.readBoolean();
		this.map_mode = oos.readBoolean();
		//this.mazebuilder = (MazeBuilder) oos.readObject();
		this.exitx = oos.readInt();
		this.exity = oos.readInt();
	}
	
//	public Maze(Context context) {
//		super(context);
//		// TODO Auto-generated constructor stub
//	}

	private static final long serialVersionUID = 1L;

	//	Font smallBannerFont, largeBannerFont;
//	private Image buffer_img;
	GraphicsWrapper gc;
	
	static final int view_width = 400;
	static final int view_height = 400;
	int zscale = view_height/2;

	static final int map_unit = 128;
	static final int view_offset = map_unit/8;
	static final int step_size = map_unit/4;

	RangeSet rset;

	boolean done;

	
	public int state;			// keeps track of the current GUI state, one of STATE_TITLE,...,STATE_FINISH, mainly used in redraw()
	// user can navigate 
	// title -> generating -(escape) -> title
	// title -> generation -> play -(escape)-> title
	// title -> generation -> play -> finish -> title
	// STATE_PLAY is the main state where the user can navigate through the maze in a first person view
//	static final int STATE_TITLE = 1;
//	static final int STATE_GENERATING = 2;
	static final int STATE_PLAY = 3;
	static final int STATE_FINISH = 4;
//	static final int STATE_TITLE2 = 5;

	
//	private int percentdone = 0; // describes progress during generation phase
	boolean showMaze;		 	// toggle switch to show overall maze on screen
	boolean showSolution;		// toggle switch to show solution in overall maze on screen
	public boolean solving;			// toggle switch 

	final int viewz = 50;    
	int viewx, viewy, ang;
	int dx, dy;  // current direction
	int px, py ; // current position on maze grid (x,y)
	int walk_step;
	int view_dx, view_dy; // current view direction


	// debug stuff
	boolean deepdebug = false;
	boolean all_visible = false;
	boolean new_game = false;
	int exitx;
	int exity;
	int mazew; // width of maze
	int mazeh; // height of maze
	// grid for maze
	Cells mazecells ;
	int[][] mazedists;
	Cells seencells ;
	//BSPNode bsp_root;
	
	boolean map_mode; // true: display map of maze, false: do not display map of maze
	// map_mode is toggled by user keyboard input, causes a call to draw_map during play mode
	//int map_scale; relocated to mapdrawer

	// MapDrawer to perform drawing of maps
	MapDrawer mapdrawer ;
	// Drawer to get the first person perspective
	FirstPersonDrawer firstpersondrawer ;
	// Mazebuilder is used to calculate a new maze together with a solution
	// The maze is computed in a separate thread. It is started in the local Build method.
	// The calculation communicates back by calling the local newMaze() method.
	public MazeBuilder mazebuilder;

	//user added
	int steps;
	int energyUsed;
	boolean setRandom = false;
	

	
	// The user picks a skill level between 0 - 9, a-f 
	// The following arrays transform this into corresponding dimensions for the result maze as well as the number of rooms and parts
	static int skill_x[] =     { 4, 12, 15, 20, 25, 25, 35, 35, 40, 60,
		70, 80, 90, 110, 150, 300 };
	static int skill_y[] =     { 4, 12, 15, 15, 20, 25, 25, 35, 40, 60,
		70, 75, 75,  90, 120, 240 };
	static int skill_rooms[] = { 0,  2,  2,  3,  4,  5, 10, 10, 20, 45,
		45, 50, 50,  60,  80, 160 };
	static int skill_partct[] = { 60,
		600, 900, 1200,
		2100, 2700, 3300,
		5000, 6000, 13500,
		19800, 25000, 29000,
		45000, 85000, 85000*4 };

	// fixing a value matching the escape key
	final int ESCAPE = 27;

	public void setRandom(boolean random){
		setRandom  = random;
	}

	/**
	 * Call back method for MazeBuilder to communicate newly generated maze as reaction to a call to build()
	 * @param root node for traversals, used for the first person perspective
	 * @param cells encodes the maze with its walls and border
	 * @param dists encodes the solution by providing distances to the exit for each position in the maze
	 * @param startx current position, x coordinate
	 * @param starty current position, y coordinate
	 */
	public void newMaze(BSPNode root, Cells c, int dists[][], int startx, int starty) {
		showMaze = showSolution = solving = false;
		mazecells = c ;
		mazedists = dists;
		seencells = new Cells(mazew+1,mazeh+1) ;
		//bsp_root = root; // delegated to firstpersondrawer
		//dx = 1; dy = 0;
		setCurrentDirection(1, 0) ;
		setCurrentPosition(startx,starty) ;
		walk_step = 0;
		view_dx = dx<<16; 
		view_dy = dy<<16;
		ang = 0;
		map_mode = false;
		// mazew and mazeh have been set in build() method before mazebuider was called to generate a new maze.
		// reset map_scale in mapdrawer to a value of 10
		mapdrawer = new MapDrawer(view_width,view_height,map_unit,step_size, mazecells, seencells, 10, mazedists, mazew, mazeh) ;
		
		firstpersondrawer = new FirstPersonDrawer(view_width,view_height,map_unit,step_size, mazecells, seencells, 10, mazedists, mazew, mazeh, root) ;
		// set the current state for the state-dependent behavior
		//state = STATE_PLAY;
		// graphics update
	//	redraw();//:TODO
		// the next line is needed because we're in a separate thread;
		// we can't seem to do a real paint in this thread, so tell
		// the main thread to do it.
		//repaint();
		done = true;
	}

	
	public void setCurrentPosition(int x, int y)
	{
		px = x ;
		py = y ;
	}
	private void setCurrentDirection(int x, int y)
	{
		dx = x ;
		dy = y ;
	}
	
	final double radify(int x) {
		return x*Math.PI/180;
	}

	/**
	 * overwrites Applet method
	 */
	public void paint(GraphicsWrapper g) {
		gc = g;
		g.gc.drawBitmap(g.image, 0, 0, g.paint);
	}

	/////////////////////// Methods for debugging ////////////////////////////////
	private void dbg(String str) {
		System.out.println(str);
	}

	void logPosition() {
		if (!deepdebug)
			return;
		dbg("x="+viewx/map_unit+" ("+
				viewx+") y="+viewy/map_unit+" ("+viewy+") ang="+
				ang+" dx="+dx+" dy="+dy+" "+view_dx+" "+view_dy);
	}
	///////////////////////////////////////////////////////////////////////////////

	/**
	 * Helper method for walk()
	 * @param dir
	 * @return true if there is no wall in this direction
	 */
	private boolean checkMove(int dir) {
		// obtain appropriate index for direction (CW_BOT, CW_TOP ...) 
		// for given direction parameter
		int a = ang/90;
		if (dir == -1)
			a = (a+2) & 3; // TODO: check why this works
		// check if cell has walls in this direction
		// returns true if there are no walls in this direction
		int[] masks = Cells.getMasks() ;
		return mazecells.hasMaskedBitsFalse(px, py, masks[a]) ;
	}

	 void rotateStep() {
		ang = (ang+1800) % 360;
		view_dx = (int) (Math.cos(radify(ang))*(1<<16));
		view_dy = (int) (Math.sin(radify(ang))*(1<<16));
		moveStep();
	}

	public void moveStep() {
		gc.postInvalidate();
		try {
			Thread.currentThread().sleep(25);
		} catch (Exception e) { }
	}

	public void setGraphicsWrapper(GraphicsWrapper g){
		gc = g;
	}
	
	 void rotateFinish() {
		//dx = (int) Math.cos(radify(ang));
		//dy = (int) Math.sin(radify(ang));
		setCurrentDirection((int) Math.cos(radify(ang)), (int) Math.sin(radify(ang))) ;
		logPosition();
	}

	 public void walkFinish(int dir) {
		//px += dir*dx; py += dir*dy;
		setCurrentPosition(px + dir*dx, py + dir*dy) ;
		
		if (isEndPosition(px,py)) {
			System.out.println("within walkFinish");
			state = STATE_FINISH;
			gc.postInvalidate();
		}
		walk_step = 0;
		logPosition();
	}

	/**
	 * checks if the given position is outside the maze
	 * @param x
	 * @param y
	 * @return true if position is outside, false otherwise
	 */
	public boolean isEndPosition(int x, int y) {
		return x < 0 || y < 0 || x >= mazew || y >= mazeh;
	}

	synchronized void walk(int dir) {
		if (!checkMove(dir))
			return;
		for (int step = 0; step != 4; step++) {
			walk_step += dir;
			moveStep();
		}
		walkFinish(dir);
		
	}

	synchronized void walk(int dir, GraphicsWrapper gWrap) {
		gc = gWrap;
		if (!checkMove(dir))
			return;
		for (int step = 0; step != 4; step++) {
			walk_step += dir;
			moveStep();
		}
		walkFinish(dir);
	}

	synchronized  void rotate(int dir) {
		int origang = ang;
		int steps = 4;

		for (int step = 0; step != steps; step++) {
			ang = origang + dir*(90*(step+1))/steps;
			rotateStep();
		}
		rotateFinish();
		energyUsed += 2; //TODO: user added energy consumption
	}

	/**
	 * Helper method for solveStep
	 * @param n
	 */
	 void rotateTo(int n) {
		int a = ang/90;
		if (n == a)
			;
		else if (n == ((a+2) & 3)) {
			rotate(1);
			rotate(1);
		} else if (n == ((a+1) & 3)) {
			rotate(1);
		} else
			rotate(-1);
	}

	/**
	 * Method is only called in update() method (which serves redraw())
	 */
	synchronized public void solveStep() {
		solving = false;
		int d = mazedists[px][py];
		gc.setColor(6);
		
		if(energyUsed <= 1000){	//TODO: energy usage block statement
		// case 1: we are not directly next to the final position
			if (d > 1) {
				int n = getDirectionIndexTowardsSolution(px, py, d);
				if (n == 4)
					dbg("HELP!");
				rotateTo(n);
				walk(1, gc);
				steps++; // TODO: added for counter
				energyUsed += 3;
				//update(gc); //FIND REPAINT!
				solving = true;
				return;
			}
			// case 2: we are one step close to the final position
			int n;
			int[] masks = Cells.getMasks();
			for (n = 0; n < 4; n++) {
				// skip this direction if there is a wall or border
				if (mazecells.hasMaskedBitsGTZero(px, py, masks[n]))
					continue;
				// stop if position in this direction is end position
				if (isEndPosition(px + MazeBuilder.dirsx[n], py
						+ MazeBuilder.dirsy[n]))
					break;
			}
			rotateTo(n);
			walk(1, gc);
			steps++; // TODO: user added steps counter
			energyUsed += 3;
		}//energy-if
	}


	private int getDirectionIndexTowardsSolution(int x, int y, int d) {
		int[] masks = Cells.getMasks() ;
		for (int n = 0; n < 4; n++) {
			if (mazecells.hasMaskedBitsTrue(x,y,masks[n]))
				continue;
				int dx = MazeBuilder.dirsx[n];
				int dy = MazeBuilder.dirsy[n];
				int dn = mazedists[x+dx][y+dy];
				if (dn < d)
					return n ;
		}
		return 4 ;
	}

	/**This method was called to initaite the maze objects, but that call
	 * has been shifted to the build method and activities.
	 * 
	 */
	public void init() {

		Log.v(tag, "Within Init in maze");
		Log.v(tag, "after gc.image");
		rset = new RangeSet();
	}

	public void start() {
		gc.postInvalidate();
	}

	/**
	 * Method obtains a new Mazebuilder and has it compute new maze, 
	 * it is only used in keyDown()
	 * @param skill level determines the width, height and number of rooms for the new maze
	 */
	public void build(int skill) {
		done = false;
		// state = STATE_GENERATING;
		// percentdone = 0;
		Log.v(tag, "Within Build");
		// redraw();
		Log.v(tag, "Past Redraw in build()");
		mazebuilder = new MazeBuilderFalstad(); // Change from MazeBuilder() to
												// MazeBuilderFalstad
		mazew = skill_x[skill];
		mazeh = skill_y[skill];
		int roomcount = skill_rooms[skill];

		if (setRandom) {
			Log.v(tag, "within setrandom");
			mazebuilder.build(this, mazew, mazeh, roomcount,skill_partct[skill], 3);
			Log.v(tag, "past mazebuilder.build in build()");
		} else {
			Log.v(tag, "within else of setrandom");
			mazebuilder.build(this, mazew, mazeh, roomcount,skill_partct[skill]);
			Log.v(tag, "past mazebuilder.build in build()");
			// mazebuilder calls back by calling newMaze() to return newly
			// generated maze
		}//else
		exitx = mazebuilder.exitPosition[0];
		exity = mazebuilder.exitPosition[1];
	}//build
	
	/**Return the exit position.
	 * 
	 * @return
	 */
	public int[] getExit(){
		int[] exit = {exitx, exity};
		return exit;
	}

}


