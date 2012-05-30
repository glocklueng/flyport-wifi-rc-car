package wifirc.car;

import android.app.Activity;
import android.os.Bundle;
//import android.view.View.OnClickListener;
import android.view.MotionEvent;
import android.view.View.OnTouchListener;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.EditText;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
//import java.io.ObjectOutputStream;
//import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
/*import java.lang.*;
import java.io.*;
import java.net.*;*/
//import java.net.SocketException;

public class WiFiRCCarActivity extends Activity implements View.OnTouchListener, SeekBar.OnSeekBarChangeListener
{
	TextView textTop = null;
	TextView textBottom = null;
	Button  /*gauche = null, droite = null,*/ avant = null, arriere = null, retry =null, phares = null;
	EditText ipText = null, portText = null;
	SeekBar seekbar = null;
	
	//private String ipAddress = "192.168.98.86";
	//private  int port = 2050;
	
	Socket s = null;
	PrintWriter output = null;
	
	//Socket soc = null;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        //SensorManager m = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        
        textTop = (TextView) findViewById(R.id.texthaut);
        textBottom = (TextView) findViewById(R.id.textbas);
        //haut = (Button) findViewById(R.id.haut);
        /*gauche = (Button) findViewById(R.id.gauche);
        droite = (Button) findViewById(R.id.droite);*/
        avant = (Button) findViewById(R.id.avant);
        arriere = (Button) findViewById(R.id.arriere);
        retry = (Button) findViewById(R.id.retry);
        ipText = (EditText) findViewById(R.id.iptext);
        portText = (EditText) findViewById(R.id.porttext);
        phares = (Button) findViewById(R.id.phares);
        seekbar = (SeekBar) findViewById(R.id.seekBar);
        
        /*textTop.setText("Connection ...");
        textBottom.setText("");
        //haut.setOnTouchListener(this);
        avant.setOnTouchListener(this);
        arriere.setOnTouchListener(this);
        phares.setOnTouchListener(this);
        seekbar.setOnSeekBarChangeListener(this);*/

        try 
        {
            s = new Socket(ipText.getText().toString(),Integer.parseInt(portText.getText().toString()));
           
            //outgoing stream redirect to socket
            OutputStream out = s.getOutputStream();
           
            PrintWriter output = new PrintWriter(out);
            output.println("Hello I'm Android!");
            textTop.setText("Connected to " + ipText.getText().toString() + " : " + Integer.parseInt(portText.getText().toString()));
            //retry.setVisibility(1);//invisible
            
            textTop.setText("Connection ...");
            textBottom.setText("");
            //haut.setOnTouchListener(this);
            avant.setOnTouchListener(this);
            arriere.setOnTouchListener(this);
            phares.setOnTouchListener(this);
            seekbar.setOnSeekBarChangeListener(this);
            //s.close();
           
        } 
        catch (UnknownHostException e) 
      	{
       		// TODO Auto-generated catch block
        	retry.setVisibility(0);//visible
        	textTop.setText("Unknown host" + ipText.getText().toString());
       		e.printStackTrace();
       	} 
       	catch (IOException e) 
       	{
       		// TODO Auto-generated catch block
       		retry.setVisibility(0);//visible
       		textTop.setText("Couldn't get I/O for the connection to: " + ipText.getText().toString() + ":" + Integer.parseInt(portText.getText().toString()));
       		e.printStackTrace();
       	}  
    }

  
    public boolean onTouch(View v, MotionEvent event) 
    {
    	//int action = event.getAction();
    	//int actionCode = action & MotionEvent.ACTION_MASK;
    	if(event.getAction() == MotionEvent.ACTION_DOWN || event.getAction() == MotionEvent.ACTION_POINTER_DOWN || event.getAction() == MotionEvent.ACTION_POINTER_1_DOWN || event.getAction() == MotionEvent.ACTION_POINTER_2_DOWN) 
        {
    		try 
        	{
                output = new PrintWriter(s.getOutputStream(), true);
                switch(v.getId()) 
            	{
                /*case R.id.haut:
                	textBottom.setText("|");
                	output.println("|");
                	break;*/
                /*case R.id.gauche:
                	textBottom.setText("t10");
                	//output.println("t10");
                	break;
                case R.id.droite:
                	textBottom.setText("t990");
                	//output.println("t990");
                	break;*/
                case R.id.avant:
                	textBottom.setText("v80");
                	output.println("v80");
                	break;
                case R.id.arriere:
                	textBottom.setText("r80");
                	output.println("r80");
                	break;
                case R.id.phares:
                	textBottom.setText("p");
                	output.println("p");
                	break;
            	}

        	} 
        	catch (UnknownHostException e) 
        	{
        		
        		textTop.setText("Unknown host" + ipText.getText().toString());
        	} 
        	catch (IOException e) 
        	{
        		textTop.setText("Couldn't get I/O for the connection to: " + ipText.getText().toString() + ":" + Integer.parseInt(portText.getText().toString()));
        	}
    		
        	return false;
        }
    	else if(event.getAction() == MotionEvent.ACTION_UP || event.getAction() == MotionEvent.ACTION_POINTER_UP || event.getAction() == MotionEvent.ACTION_POINTER_1_UP || event.getAction() == MotionEvent.ACTION_POINTER_2_UP) 
        {
    		try 
        	{
                output = new PrintWriter(s.getOutputStream(), true);
                if (v.getId() == R.id.avant || v.getId() == R.id.arriere)
            	{
            		textBottom.setText("s");
            		output.println("s");
            	}
            	/*else if (v.getId() == R.id.gauche || v.getId() == R.id.droite)
            	{
            		textBottom.setText("t526");
            		//output.println("t526");
            	}*/
        	
        	} 
        	catch (UnknownHostException e) 
        	{
        		
        		textTop.setText("Unknown host" + ipText.getText().toString());
        	} 
        	catch (IOException e) 
        	{
        		textTop.setText("Couldn't get I/O for the connection to: " + ipText.getText().toString() + ":" + Integer.parseInt(portText.getText().toString()));
        	}
        	return false;
        }
        return true;
    }
    
    public void retryConnexion(View view) 
    {
    	textTop.setText("/Connection ...");
    	try 
        {
            s = new Socket(ipText.getText().toString(),Integer.parseInt(portText.getText().toString()));
           
            //outgoing stream redirect to socket
            OutputStream out = s.getOutputStream();
            PrintWriter output = new PrintWriter(out);
            output.println("Hello Android!");
            textTop.setText("/Connected to " + ipText.getText().toString() + " : " + Integer.parseInt(portText.getText().toString()));
            //retry.setVisibility(1);//invisible
            

            avant.setOnTouchListener(this);
            arriere.setOnTouchListener(this);
            phares.setOnTouchListener(this);
           
        } 
        catch (UnknownHostException e) 
      	{
        	retry.setVisibility(0);//visible
        	textTop.setText("/Unknown host" + ipText.getText().toString());
       		e.printStackTrace();
       	} 
       	catch (IOException e) 
       	{
       		retry.setVisibility(0);//visible
       		textTop.setText("/Couldn't get I/O for the connection to: " + ipText.getText().toString() + ":" + Integer.parseInt(portText.getText().toString()) );
       		e.printStackTrace();
       	}
    }
    
    public void setNeutre(View view) 
    {
    	seekbar.setProgress(52);
    	try 
    	{
            output = new PrintWriter(s.getOutputStream(), true);
            output.println("t526");
    	}
    	catch (UnknownHostException e) 
    	{
    		
    		textTop.setText("Unknown host" + ipText.getText().toString());
    	} 
    	catch (IOException e) 
    	{
    		textTop.setText("Couldn't get I/O for the connection to: " + ipText.getText().toString() + ":" + Integer.parseInt(portText.getText().toString()));
    	}
    }


	@Override
	public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) 
	{
		// TODO Auto-generated method stub
		double val = 9.8*progress +10 ;
		textBottom.setText("t" + (int)val );
		try 
    	{
            output = new PrintWriter(s.getOutputStream(), true);
            output.println("t" + (int)val );
    	}
    	catch (UnknownHostException e) 
    	{
    		
    		textTop.setText("Unknown host" + ipText.getText().toString());
    	} 
    	catch (IOException e) 
    	{
    		textTop.setText("Couldn't get I/O for the connection to: " + ipText.getText().toString() + ":" + Integer.parseInt(portText.getText().toString()));
    	}
	}


	@Override
	public void onStartTrackingTouch(SeekBar seekBar) 
	{	// TODO Auto-generated method stub
		
	}


	@Override
	public void onStopTrackingTouch(SeekBar seekBar) 
	{
		// TODO Auto-generated method stub
		
	}

    
}




