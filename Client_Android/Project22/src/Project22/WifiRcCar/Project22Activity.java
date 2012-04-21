package Project22.WifiRcCar;

import android.app.Activity;
import android.os.Bundle;
//import android.view.View.OnClickListener;
import android.view.MotionEvent;
import android.view.View.OnTouchListener;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

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

public class Project22Activity extends Activity implements View.OnTouchListener
{
	TextView textTop = null;
	TextView textBottom = null;
	Button haut = null, gauche = null, droite = null, avant = null, arriere = null, retry =null;
	
	private String ipAddress = "192.168.1.115";
	private  int port = 2050;
	
	Socket s = null;
	PrintWriter output = null;
	
	//Socket soc = null;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        
        textTop = (TextView) findViewById(R.id.texthaut);
        textBottom = (TextView) findViewById(R.id.textbas);
        haut = (Button) findViewById(R.id.haut);
        gauche = (Button) findViewById(R.id.gauche);
        droite = (Button) findViewById(R.id.droite);
        avant = (Button) findViewById(R.id.avant);
        arriere = (Button) findViewById(R.id.arriere);
        retry = (Button) findViewById(R.id.retry);
        textTop.setText("Connection ...");
        try 
        {
        	
            s = new Socket(ipAddress,port);
           
            //outgoing stream redirect to socket
            OutputStream out = s.getOutputStream();
           
            PrintWriter output = new PrintWriter(out);
            output.println("Hello I'm Android!");
            textTop.setText("Connected");
            retry.setVisibility(1);//invisible
            
            haut.setOnTouchListener(this);
            gauche.setOnTouchListener(this);
            droite.setOnTouchListener(this);
            avant.setOnTouchListener(this);
            arriere.setOnTouchListener(this);
            //s.close();
           
        } 
        catch (UnknownHostException e) 
      	{
       		// TODO Auto-generated catch block
        	retry.setVisibility(0);//visible
        	textTop.setText("Unknown host" + ipAddress);
       		e.printStackTrace();
       	} 
       	catch (IOException e) 
       	{
       		// TODO Auto-generated catch block
       		retry.setVisibility(0);//visible
       		textTop.setText("Couldn't get I/O for the connection to: " + ipAddress + ":" + port);
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
                case R.id.haut:
                	textBottom.setText("|");
                	output.println("|");
                	break;
                case R.id.gauche:
                	textBottom.setText("g");
                	output.println("g");
                	break;
                case R.id.droite:
                	textBottom.setText("d");
                	output.println("d");
                	break;
                case R.id.avant:
                	textBottom.setText("V");
                	output.println("V");
                	break;
                case R.id.arriere:
                	textBottom.setText("v");
                	output.println("v");
                	break;
            	}

        	} 
        	catch (UnknownHostException e) 
        	{
        		
        		textTop.setText("Unknown host" + ipAddress);
        	} 
        	catch (IOException e) 
        	{
        		textTop.setText("Couldn't get I/O for the connection to: " + ipAddress + ":" + port);
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
            		textBottom.setText("|");
            		output.println("|");
            	}
        	
        	} 
        	catch (UnknownHostException e) 
        	{
        		
        		textTop.setText("Unknown host" + ipAddress);
        	} 
        	catch (IOException e) 
        	{
        		textTop.setText("Couldn't get I/O for the connection to: " + ipAddress + ":" + port);
        	}
        	return false;
        }
        return true;
    }
    
    public void retryConnexion(View view) 
    {
    	textTop.setText("retry/Connection ...");
    	try 
        {
            s = new Socket(ipAddress,port);
           
            //outgoing stream redirect to socket
            OutputStream out = s.getOutputStream();
            PrintWriter output = new PrintWriter(out);
            output.println("Hello Android!");
            textTop.setText("retry/Hello");
            retry.setVisibility(1);//invisible
           
        } 
        catch (UnknownHostException e) 
      	{
        	retry.setVisibility(0);//visible
        	textTop.setText("retry/Unknown host" + ipAddress);
       		e.printStackTrace();
       	} 
       	catch (IOException e) 
       	{
       		retry.setVisibility(0);//visible
       		textTop.setText("retry/Couldn't get I/O for the connection to: " + ipAddress + ":" + port );
       		e.printStackTrace();
       	}
    }
    

    
}




