package wifirc.car;

import android.app.Activity;
import android.os.Bundle;
//import android.view.View.OnClickListener;
import android.view.MotionEvent;
import android.view.View.OnTouchListener;
import android.view.View;
import android.widget.Button;
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

public class WiFiRCCarActivity extends Activity implements View.OnTouchListener
{
	TextView textTop = null;
	TextView textBottom = null;
	Button  gauche = null, droite = null, avant = null, arriere = null, retry =null, phares = null;
	EditText ipText = null, portText = null;
	
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
        gauche = (Button) findViewById(R.id.gauche);
        droite = (Button) findViewById(R.id.droite);
        avant = (Button) findViewById(R.id.avant);
        arriere = (Button) findViewById(R.id.arriere);
        retry = (Button) findViewById(R.id.retry);
        ipText = (EditText) findViewById(R.id.iptext);
        portText = (EditText) findViewById(R.id.porttext);
        phares = (Button) findViewById(R.id.phares);
        
        textTop.setText("Connection ...");
        textBottom.setText("");
        try 
        {
            s = new Socket(ipText.getText().toString(),Integer.parseInt(portText.getText().toString()));
           
            //outgoing stream redirect to socket
            OutputStream out = s.getOutputStream();
           
            PrintWriter output = new PrintWriter(out);
            output.println("Hello I'm Android!");
            textTop.setText("Connected to " + ipText.getText().toString() + " : " + Integer.parseInt(portText.getText().toString()));
            //retry.setVisibility(1);//invisible
            
            //haut.setOnTouchListener(this);
            gauche.setOnTouchListener(this);
            droite.setOnTouchListener(this);
            avant.setOnTouchListener(this);
            arriere.setOnTouchListener(this);
            phares.setOnTouchListener(this);
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
    	if(event.getAction() == MotionEvent.ACTION_DOWN) 
        {
    		try 
        	{
                output = new PrintWriter(s.getOutputStream(), true);
                textTop.setText("Connected");
                switch(v.getId()) 
            	{
                /*case R.id.haut:
                	textBottom.setText("|");
                	output.println("|");
                	break;*/
                case R.id.gauche:
                	textBottom.setText("t10");
                	output.println("t10");
                	break;
                case R.id.droite:
                	textBottom.setText("t990");
                	output.println("t990");
                	break;
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
    	else if(event.getAction() == MotionEvent.ACTION_UP) 
        {
    		try 
        	{
                output = new PrintWriter(s.getOutputStream(), true);
                textTop.setText("Connected");
                if (v.getId() == R.id.avant || v.getId() == R.id.arriere)
            	{
            		textBottom.setText("s");
            		output.println("s");
            	}
            	else
            	{
            		textBottom.setText("t526");
            		output.println("t526");
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
            
            gauche.setOnTouchListener(this);
            droite.setOnTouchListener(this);
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
    

    
}




