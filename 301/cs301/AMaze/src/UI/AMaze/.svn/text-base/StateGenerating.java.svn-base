package UI.AMaze;

import java.util.Timer;
import java.util.TimerTask;

import UI.AMaze.R;
import UI.AMaze.R.id;
import UI.AMaze.R.layout;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.KeyEvent;
import android.widget.EditText;
//import android.widget.Toast;

/*This state is the loading screen section before the play screen. It will pause for several seconds
 * so that the maze is created properly.
 * 
 */
public class StateGenerating extends Activity {
    private static final String tag = "StateGenerating";  
    Maze maze;
	/**The initial screen called when the activity is called.
	 * 
	 */
	public void onCreate(final Bundle recieve) {
		super.onCreate(recieve);
		setContentView(R.layout.stategenerating);
		
		Log.v(tag, "Made it past setcontent");
		
		
		
		//get Bundles
		final Bundle info = getIntent().getExtras();
		final Bundle extras = info;
		final int mazeNum = info.getInt("mazeNum");
		final int level = info.getInt("level");
		
		Log.v(tag, "Made it past the bundles");
		
		// build maze
		//Context context = getApplicationContext();
		maze = new Maze();
		Log.v(tag, "Made it past the maze object creation");
		
		maze.setRandom(true);
		Log.v(tag, "Made it past the setRandom");
		
		maze.init();
		Log.v(tag, "Made it past the init");
		
		maze.build(level);
		Log.v(tag, "Made it past the level");
	   	
//	   	 set maze info into bundles
//	   	 extras.putExtra("mz", maze);	   	 
//		 testing that bundles were taken in
//	   	 CharSequence text = "Maze:" + mazeNum + " Level:" + level;
//	   	 int duration = Toast.LENGTH_SHORT;
//	   	 Toast toast = Toast.makeText(context, text, duration);
//	   	 toast.show();
		
		
		new AsyncTask<Void,Integer,Integer>() {

			@Override
			protected Integer doInBackground(Void... params) {
				while (!maze.done);
				return null;
			}
			
			@Override
			protected void onProgressUpdate(Integer... progress) {
		         
		     }

			@Override
		     protected void onPostExecute(Integer result) {
				//EditText text = (EditText) findViewById(R.id.editText1);
				// text.setText("mazeType:" + recieve.get("maze") +
				// " level:" + recieve.get("level"));
				//text.setText("Test Pause Complete");
				
				Context context = getApplicationContext();
				Intent i = new Intent(context, StatePlay.class);
				//Log.v(tag, "made intent");
				extras.clear();
				i.putExtra("mazeNum", mazeNum);
				i.putExtra("level", level);
				//Log.v(tag, "added extras");
				i.putExtra("mz", maze);
				//Log.v(tag, "added maze");
				//i.putExtras(extras);					
				//i.putExtra("mz", maze);
				
				// Set the request code to any code you like, you can
				// identify the
				// callback via this code
				startActivity(i);
			}			
		}.execute();		
	}//onCreate
	
	/**Takes care of back button events to return to main menu
     * 
     */
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event)  {
	    if (keyCode == KeyEvent.KEYCODE_BACK) {
	    	Context context = getApplicationContext();
			Intent i = new Intent(context, AMazeActivity.class);
			startActivityForResult(i, 10);
	        return true;
	    }

	    return super.onKeyDown(keyCode, event);
	}//onKeyDown
	
	
}//StateGenerating