package UI.AMaze;

import UI.AMaze.R;
import UI.AMaze.R.array;
import UI.AMaze.R.id;
import UI.AMaze.R.layout;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.Spinner;
import android.widget.Toast;

/* This is the menu screen activity. The user will select a maze option as well as
 * a maze level and to begin the maze.
 * 
 */
public class AMazeActivity extends Activity {
	private static final String tag = "AMazeActivity";  
	//private static final int REQUEST_CODE = 10;
	//private CharSequence startText;
	private int mazeType = 4; //default to manual
	private int level = 0;    //default to level 0
	
	
	/**The initial screen called when the activity is called.
	 * 
	 */
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        //RadioButton Click Listeners
        OnClickListener glistener = new OnClickListener() {
            public void onClick(View v) {
                // Perform action on clicks
				//startText = "Gambler Button Pressed!";
				mazeType = 0;
            }
        };
        OnClickListener cglistener = new OnClickListener() {
            public void onClick(View v) {
                // Perform action on clicks
				//startText = "Curious Gambler Button Pressed!";
				mazeType = 1;
            }
        };
        OnClickListener wflistener = new OnClickListener() {
            public void onClick(View v) {
                // Perform action on clicks
				//startText = "Wall Follower Button Pressed!";
				mazeType = 2;
            }
        };
        OnClickListener wlistener = new OnClickListener() {
            public void onClick(View v) {
                // Perform action on clicks
				//startText = "Wizard Button Pressed!";
				mazeType = 3;
            }
        };
        OnClickListener mlistener = new OnClickListener() {
            public void onClick(View v) {
                // Perform action on clicks
				//startText = "Manual Button Pressed!";
				mazeType = 4;
            }
        };
        
        //create radio buttons
        RadioButton gambler = (RadioButton) findViewById(R.id.gambler);
        gambler.setOnClickListener(glistener);
        RadioButton cGambler = (RadioButton) findViewById(R.id.cGambler);
        cGambler.setOnClickListener(cglistener);
        RadioButton wFollower = (RadioButton) findViewById(R.id.wFollower);
        wFollower.setOnClickListener(wflistener);
        RadioButton wizard = (RadioButton) findViewById(R.id.wizard);
        wizard.setOnClickListener(wlistener);
        RadioButton manual = (RadioButton) findViewById(R.id.manual);
        manual.setOnClickListener(mlistener);
        
        //create level spinner widget
        Spinner spinner = (Spinner) findViewById(R.id.spinner1);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(
                this, R.array.level_array, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);
        spinner.setOnItemSelectedListener(new MyOnItemSelectedListener());

        Log.v(tag, "Past the spinner widget");
        
		//create the button
		Button start = (Button) findViewById(R.id.Button01);
		//Make the Buttons Clickable
		start.setOnClickListener(new View.OnClickListener() {
             public void onClick(View v) {
            	 //code that occurs once button is pressed
//            	 Context context = getApplicationContext();
//            	 CharSequence text = startText;
//            	 int duration = Toast.LENGTH_SHORT;
//            	 Toast toast = Toast.makeText(context, text, duration);
//            	 toast.show();
            	
            	Context context = getApplicationContext();
            	Intent i = new Intent(context, StateGenerating.class);
         		i.putExtra("mazeNum", mazeType);
				i.putExtra("level", level);
				// Set the request code to any code you like, you can identify
				// the callback via this code
				startActivity(i);
			}
		});
    }//onCreate
    
    /**Used in the spinner to find the proper value and store into Extras to be passed on.
     * 
     * @author ewshih
     */
    public class MyOnItemSelectedListener implements OnItemSelectedListener {

        public void onItemSelected(AdapterView<?> parent,
            View view, int pos, long id) {
        	
        //  Toast.makeText(parent.getContext(), "The level is " +
        //       parent.getItemAtPosition(pos), Toast.LENGTH_LONG).show();
          String slevel = parent.getItemAtPosition(pos).toString();
          level = Integer.parseInt(slevel);          
        }

        public void onNothingSelected(AdapterView parent) {
          // Do nothing.
        }
    }
}//AMazeActivity