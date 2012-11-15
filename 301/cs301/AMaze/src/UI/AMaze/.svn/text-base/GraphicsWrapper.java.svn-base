package UI.AMaze;

//import java.awt.*;
//import java.awt.event.KeyEvent;
//import java.awt.event.KeyListener;
import java.io.Serializable;

import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
//Color, Canvas, Paint
import android.content.Context;
import android.content.Intent;
import android.graphics.*;
import android.graphics.Paint.*;

public class GraphicsWrapper extends View implements Serializable {

	private static final String tag = "GraphicsWrapper";
	private static final long serialVersionUID = 1L;

	Maze maze;
	int key, code;

	// the set of new android calls
	int testCode = 0;
	Canvas gc;
	int[] p;
	Paint paint;
	Path path;
	Bitmap image;
	StatePlay s;
	
	// protected Container parent;//:TODO make it canvas
	public static final int getEventUp = KeyEvent.KEYCODE_DPAD_UP;
	public static final int getEventLeft = KeyEvent.KEYCODE_DPAD_LEFT;
	public static final int getEventRight = KeyEvent.KEYCODE_DPAD_RIGHT;
	public static final int getEventDown = KeyEvent.KEYCODE_DPAD_DOWN;

	// public static final int CHAR_UNDEFINED = KeyEvent.;
	public static final int VK_0 = KeyEvent.KEYCODE_0;
	public static final int VK_9 = KeyEvent.KEYCODE_9;
	public static final int VK_A = KeyEvent.KEYCODE_BUTTON_A;
	public static final int VK_Z = KeyEvent.KEYCODE_BUTTON_Z;
	public static final int VK_ESCAPE = KeyEvent.KEYCODE_BACK;
	public static final int VK_UP = KeyEvent.KEYCODE_DPAD_UP;
	public static final int VK_DOWN = KeyEvent.KEYCODE_DPAD_DOWN;
	public static final int VK_LEFT = KeyEvent.KEYCODE_DPAD_LEFT;
	public static final int VK_RIGHT = KeyEvent.KEYCODE_DPAD_RIGHT;

	// Log Tags
	private static final String TAG = "Graphics Wrapper";

	/**
	 * Constructor for graphics wrapper
	 * 
	 */
	public GraphicsWrapper(StatePlay s, Maze maze) {
		super(s);
		this.s = s;
		this.maze = maze;
		this.testCode = 1;
		maze.state = maze.STATE_PLAY;
		image = Bitmap.createBitmap(Maze.view_width, Maze.view_height,
				Bitmap.Config.ARGB_8888);
		gc = new Canvas(image);
		paint = new Paint();

		p = new int[2];
	}

	/**This method redraws the screen
	 * 
	 * 
	 */
	public void onDraw(Canvas c) {
		gc = c;
		redrawPlay(gc);
	}

	/**
	 * 
	 */
	public void keyDown(int key) {

		if (maze.state == Maze.STATE_PLAY) {
			switch (key) {
			case getEventUp:
			case 'k':
			case '8':
				maze.walk(1, this);
				invalidate();
				break;
			case getEventLeft:
			case 'h':
			case '4':
				maze.rotate(1);
				invalidate();
				break;
			case getEventRight:
			case 'l':
			case '6':
				maze.rotate(-1);
				invalidate();
				break;
			case getEventDown:
			case 'j':
			case '2':
				maze.walk(-1, this);
				invalidate();
				break;
			case VK_ESCAPE:
			case 65385:
				if (maze.solving)
					maze.solving = false;
				invalidate();
				break;
			case ('w' & 0x1f): {
				maze.setCurrentPosition(maze.px + maze.dx, maze.py + maze.dy);
				invalidate();
				break;
			}
			case '\t':
			case 'm':
				maze.map_mode = !maze.map_mode;
				invalidate();
				break;
			case 'z':
				maze.showMaze = !maze.showMaze;
				invalidate();
				break;
			case 's':
				maze.showSolution = !maze.showSolution;
				invalidate();
				break;
			case ('s' & KeyEvent.KEYCODE_SHIFT_LEFT): 
				if (maze.solving)
					maze.solving = false;
				else {
					maze.solving = true;
					invalidate();
				}
				break;
			case '+':
			case '=': {
				if (maze.mapdrawer != null) {
					maze.mapdrawer.incrementMapScale();
					invalidate();
				}
				break;
			}
			case '-':

				if (maze.mapdrawer != null) {
					maze.mapdrawer.decrementMapScale();
					invalidate();
				}
				break;
			}//switch
		}//if

	}// keyDown

	/**
	 * Set color method from FirstPersonDrawer
	 * 
	 */
	public void setColor(int c) {

		switch (c) {
		case 0:
			paint.setColor(Color.BLACK);
			break;
		case 1:
			paint.setColor(Color.DKGRAY);
			break;
		case 2:
			paint.setColor(Color.WHITE);
			break;
		case 3:
			paint.setColor(Color.RED);
			break;
		case 4:
			paint.setColor(Color.GREEN);
			break;
		case 5:
			paint.setColor(Color.BLUE);
			break;
		case 6:
			paint.setColor(Color.YELLOW);
			break;
		case 7:
			paint.setColor(Color.CYAN);
			break;
		case 8:
			paint.setColor(Color.MAGENTA);
			break; // pink to magenta
		case 9:
			paint.setColor(Color.GRAY);
			break;
		case 10:
			paint.setColor(Color.WHITE);
			break; // orange to white
		}

	}

	/**
	 * Implements Fill Rectangle method from FirstPersonDrawer
	 * 
	 * @param i
	 * @param j
	 * @param view_width
	 * @param k
	 */
	public void fillRect(int i, int j, int view_width, int k) {
		gc.drawRect(i, j, i + view_width, j + k, paint);
	}

	/**
	 * Implements the drawLine function in MapDrawer
	 * 
	 * @param nx1
	 * @param ny1
	 * @param nx2
	 * @param ny12
	 */
	public void drawLine(int nx1, int ny1, int nx2, int ny12) {
		gc.drawLine(nx1, ny1, nx2, ny12, paint);
	}

	/**
	 * Implements Fill Oval method in MapDrawer
	 * 
	 * @param i
	 * @param j
	 * @param cirsiz
	 * @param cirsiz2
	 */
	public void fillOval(int x, int y, int width, int height) {
		// if its messed up, then the width and heights may be diameter or
		// radius.

		RectF rectf = new RectF(x - width, y - height, x + width, y + height);
		gc.drawOval(rectf, paint);
	}

	/**
	 * set x point value for FirstPersonDrawer
	 * 
	 * @param x
	 */
	public void setX(int x) {
		p[0] = x;
	}

	/**
	 * set y point value for FirstPersonDrawer
	 * 
	 * @param x
	 */
	public void setY(int y) {
		p[1] = y;
	}

	/**
	 * getter for Point x for FirstPersonDrawer
	 * 
	 * @return
	 */
	public int getX() {
		return p[0];
	}

	/**
	 * getter for Point Y for FirstPersonDrawer
	 * 
	 * @return
	 */
	public int getY() {
		return p[1];
	}

	public void redrawPlay(Canvas c) {
		maze.firstpersondrawer.redrawPlay(this, maze.px, maze.py, maze.view_dx,
				maze.view_dy, maze.walk_step, Maze.view_offset, maze.rset,
				maze.ang);

		if (maze.map_mode) {
			maze.mapdrawer.draw_map(this, maze.px, maze.py, maze.walk_step,
					maze.view_dx, maze.view_dy, maze.showMaze,
					maze.showSolution);
			maze.mapdrawer.draw_currentlocation(this, maze.view_dx,
					maze.view_dy);
		}
	}


	/**
	 * Returns the font metrics in Maze
	 * 
	 * @return
	 */
	public FontMetrics getFontMetrics() {
		return paint.getFontMetrics();
		// return gc.getFontMetrics();
	}

	/**
	 * Called to create a graphics object in Maze (line 185)
	 * 
	 */
	public GraphicsWrapper getGraphics() {
		Log.v(tag, "Within getGraphics");
		return this;
	}// getGraphics


}// GraphicsWrapper

