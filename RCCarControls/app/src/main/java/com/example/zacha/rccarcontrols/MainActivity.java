package com.example.zacha.rccarcontrols;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;

import com.erz.joysticklibrary.JoyStick;


//Request: http://192.168.43.84/output.cgi?text=MESSAGE&submit=Submit
/*int duty = progress - 50;
        if(duty >= 0) {

        String url = web1 + "*F0" +  String.format("%02d" , duty) + "0"  + web2;
        w.loadUrl(url);*/

public class MainActivity extends AppCompatActivity {

    WebView w;
    String web1 = "http://192.168.43.84/output.cgi?text=";
    String web2 = "&submit=Submit";

    TextView powerText;
    TextView angleText;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        final Button connectButton = (Button) findViewById(R.id.connectButton);
        powerText = (TextView) findViewById(R.id.powerText);
        angleText = (TextView) findViewById(R.id.AngleText);
          w = (WebView) findViewById(R.id.w);



        connectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                final String url = "http://192.168.43.84/output.cgi?text=*C0000&submit=Submit";
                WebView w = (WebView) findViewById(R.id.w);
                w.loadUrl(url);
            }
        });

        JoyStick joyStick = (JoyStick) findViewById(R.id.joystick);
        joyStick.setListener(new JoyStick.JoyStickListener() {
            @Override
            public void onMove(JoyStick joyStick, double angle, double power) {
                angle = (angle * 180) / (3.14159);
                int powerInt = (int) power;
                int angleInt = (int) angle;
                String pText = "Power: " + Integer.toString(powerInt);
                String aText = "Angle: " + Integer.toString(angleInt);
                powerText.setText(pText);
                angleText.setText(aText);

            }
        });




    }



    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
