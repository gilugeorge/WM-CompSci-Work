package UI.AMaze;

import UI.AMaze.BasicRobot;
import UI.AMaze.CuriousGambler;
import UI.AMaze.Gambler;
import UI.AMaze.Robot;
import UI.AMaze.RobotDriver;
import UI.AMaze.UnsuitableRobotException;
import UI.AMaze.WallFollower;
import UI.AMaze.Wizard;
import UI.AMaze.R;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.*;
import android.widget.Button;
import android.widget.Toast;

/* This is the screen where the maze is actually being shown.
 * 
 */
public class StatePlay extends Activity {
	private static final String tag = "StatePlay";
	Context context;
	GraphicsWrapper gc;
	Maze maze;
	Handler robotHandler;
	
//	Maze maze = new Maze(context);
	
	/**The initial screen called when the activity is called.
	 * 
	 */
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		maze = (Maze) getIntent().getExtras().get("mz");		
		gc = new GraphicsWrapper(this, maze);
		maze.setGraphicsWrapper(gc);
		robotHandler = new Handler();
		
		setContentView(gc);
		context = getApplicationContext();
		Log.v(tag, "Entered StatePlay");
		
		
		// get Bundles
		Bundle info = getIntent().getExtras();
		int mazeNum = info.getInt("mazeNum");
		Log.v(tag, "past the bundles");
		
		//Test that information from bundles was sent in
//		CharSequence text = "Maze:" + mazeNum + " Level:" + level;
//		int duration = Toast.LENGTH_SHORT;
//		Toast toast = Toast.makeText(context, text, duration);
//		toast.show();

//		// create the button
//		Button finish = (Button) findViewById(R.id.finish);
//		// Make the Buttons Clickable
//		finish.setOnClickListener(new View.OnClickListener() {
//			public void onClick(View v) {
//				// code that occurs once button is pressed
//				Context context = getApplicationContext();
//				Intent i = new Intent(context, StateFinish.class);
//				i.putExtras(extras);
//				// Set the request code to any code you like, you can identify
//				// the
//				// callback via this code
//				startActivity(i);
//			}
//		});
//		Log.v(tag, "Button Created");
		
		//add robot and drivers by created a single robot. The if-else
		//calls will be called depending on the mazeNum variable
		Robot robot = new BasicRobot(gc.maze);
		Log.v(tag, "Robot Created");
		
		if (mazeNum == 0) {
			final Gambler gambler = new Gambler();
			try {
				gambler.setRobot(robot);
			} catch (UnsuitableRobotException e1) {
			}
			new Thread(new Runnable() {

				@Override
				public void run() {
					try {
						gambler.drive2Exit();
						finish();
					} catch (Exception e1) {
					}
				}
			}).start();
		}else if (mazeNum == 1) {
			final CuriousGambler cGam = new CuriousGambler();
			try {
				cGam.setRobot(robot);
			} catch (UnsuitableRobotException e1) {
			}
			new Thread(new Runnable() {

				@Override
				public void run() {
					try {
						cGam.drive2Exit();
						finish();
					} catch (Exception e1) {
					}
				}
			}).start();
		}else if (mazeNum == 2) {
			final WallFollower wfollower = new WallFollower();
			try {
				wfollower.setRobot(robot);
			} catch (UnsuitableRobotException e1) {
			}
			new Thread(new Runnable() {

				@Override
				public void run() {
					try {
						wfollower.drive2Exit();
						Log.v(tag, "finish wall follower");
						finish();
					} catch (Exception e1) {
					}
				}
			}).start();
		}else if (mazeNum == 3) {
			final Wizard wiz = new Wizard();
			try {
				wiz.setRobot(robot);
			} catch (UnsuitableRobotException e1) {
			}
			new Thread(new Runnable() {

				@Override
				public void run() {
					try {
						wiz.drive2Exit();
						finish();
					} catch (Exception e1) {
					}
				}
			}).start();
		}
		
		
	}// onCreate
	
	
	@SuppressWarnings("static-access")
	/**
	 * Hard Key requests are handled
	 * 
	 */
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
//		Context context = getApplicationContext();
//		int duration = Toast.LENGTH_SHORT;
//		CharSequence text;

		switch (keyCode) {
		case GraphicsWrapper.getEventUp: case 'k': case '8':
			gc.keyDown(GraphicsWrapper.getEventUp);
			break;
		case GraphicsWrapper.getEventLeft: case 'h': case '4':
			gc.keyDown(GraphicsWrapper.getEventLeft);
			return true;
		case GraphicsWrapper.getEventRight: case 'l':
			gc.keyDown(GraphicsWrapper.getEventRight);
			return true;
		case GraphicsWrapper.getEventDown: case 'j': case '2':
			gc.keyDown(GraphicsWrapper.getEventDown);
			return true;
		case GraphicsWrapper.VK_ESCAPE: case 65385:
			gc.keyDown(GraphicsWrapper.VK_ESCAPE);
			return true;
		case (KeyEvent.KEYCODE_W): 
			gc.keyDown('w');
			return true;
		case '\t': case KeyEvent.KEYCODE_M:
			gc.keyDown('m');
			return true;
		case KeyEvent.KEYCODE_Z:
			gc.keyDown('z');
			return true;
		case KeyEvent.KEYCODE_S:
			gc.keyDown('s');
			return true;
		case KeyEvent.KEYCODE_O: //call to make the map bigger. original was +
			gc.keyDown('+');
			return true;
		case KeyEvent.KEYCODE_P: //call to make the map smaller. original was -
			gc.keyDown('-');
			return true;
		}//switch
		
		
		if(gc.maze.state == gc.maze.STATE_FINISH){
			Log.v(tag, "Within the finish check");
			
			//move on to the finish state
			context = getApplicationContext();
			Intent i = new Intent(context, StateFinish.class);
			startActivity(i);
		}
		
		return super.onKeyDown(keyCode, event);
	}//onKeyDown

	/**If the maze is finished, this will push to the StateFinish Activity
	 * 
	 */
	public void finish(){
		context = getApplicationContext();
		Intent i = new Intent(context, StateFinish.class);
		startActivity(i);
	}
	
}//StatePlay