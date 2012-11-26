package UI.AMaze;

import UI.AMaze.R;
import UI.AMaze.R.id;
import UI.AMaze.R.layout;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

/* This state occurs once the maze is finished or the robot runs out of battery.
 * It then prompts the user to return to the main menu screen to begin again.
 * 
 */
public class StateFinish extends Activity {

	/**The initial screen called when the activity is called.
	 * 
	 */
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.statefinish);
      
//		// get Bundles
//		Bundle info = getIntent().getExtras();
//		int mazeNum = info.getInt("maze");
//		int level = info.getInt("level");

//		// testing that bundles were taken in
//		Context context = getApplicationContext();
//		CharSequence text = "Maze:" + mazeNum + " Level:" + level;
//		int duration = Toast.LENGTH_SHORT;
//		Toast toast = Toast.makeText(context, text, duration);
//		toast.show();

		// create the button
		Button ret = (Button) findViewById(R.id.returnButton);
		// Make the Buttons Clickable
		ret.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				// code that occurs once button is pressed
				Context context = getApplicationContext();
				Intent i = new Intent(context, AMazeActivity.class);
				// Set the request code to any code you like, you can identify
				// the
				// callback via this code
				startActivityForResult(i, 10);

			}
		});
    }
    
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
	}
}