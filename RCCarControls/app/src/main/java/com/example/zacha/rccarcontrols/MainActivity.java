package com.example.zacha.rccarcontrols;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.ToggleButton;

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

    int sendCount = 0;


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

        final EditText ipText = (EditText) findViewById(R.id.ipText);

        Button setIPButton = (Button) findViewById(R.id.IPbutton);

        ipText.setText("192.168.43.84");

        setIPButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                web1 = "http://" + ipText.getText() + "/output.cgi?text=";
            }
        });



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
                double angleDeg = ((angle * 180) / (Math.PI));
                int xInt = (int) ((power * Math.cos(angle)) / 2);
                int yInt = (int) ((power * Math.sin(angle)) /2);

                int rightForwardSpeed = 0;
                int rightReverseSpeed = 0;
                int leftForwardSpeed = 0;
                int leftReverseSpeed = 0;
                if (yInt > 0) {
                    rightForwardSpeed = yInt;
                    leftForwardSpeed = yInt;
                    if (xInt > 0) {
                        rightForwardSpeed = rightForwardSpeed + xInt;
                    } else if (xInt < 0) {
                        leftForwardSpeed = leftForwardSpeed + (-xInt);
                    }
                } else if (yInt < 0) {
                    rightReverseSpeed = -yInt;
                    leftReverseSpeed = -yInt;
                    if (xInt > 0) {
                        rightReverseSpeed = rightReverseSpeed + xInt;
                    }
                    if (xInt < 0) {
                        leftReverseSpeed = leftReverseSpeed + (-xInt);
                    }

                }

                if (rightForwardSpeed > 90) {
                    rightForwardSpeed = 90;
                }

                if (rightReverseSpeed > 90) {
                    rightReverseSpeed = 90;
                }

                if (leftForwardSpeed > 90) {
                    leftForwardSpeed = 90;
                }

                if (leftReverseSpeed > 90) {
                    leftReverseSpeed = 90;
                }


                String pText = "Right Wheel Command: " + String.format("%03d", rightForwardSpeed) + "0" + ", " + String.format("%03d", rightReverseSpeed) + "0";
                String aText = "Left Wheel Command: " + String.format("%03d", leftForwardSpeed) + "0" + ", " + String.format("%03d", leftReverseSpeed) + "0";
                // powerText.setText(pText);
                // angleText.setText(aText);


                String rightWheelCommand = "R" + String.format("%03d", rightForwardSpeed) + "0" + "R" + String.format("%03d", rightReverseSpeed) + "0";
                String leftWheelCommand = "L" + String.format("%03d", leftForwardSpeed) + "0" + "L" + String.format("%03d", leftReverseSpeed) + "0";


                if ((sendCount++ > 4) || ((rightForwardSpeed == 0) && (rightReverseSpeed == 0) && (leftForwardSpeed == 0) && (leftReverseSpeed == 0))) {

                    String url = web1 + "*" + rightWheelCommand + leftWheelCommand + web2;
                    w.loadUrl(url);
                    sendCount = 0;
                    Log.d("Command", rightWheelCommand);
                    Log.d("Command", leftWheelCommand);
                }


                try {
                    Thread.sleep(30);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        Button stopButton = (Button) findViewById(R.id.stopButton);
        stopButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String url = web1 + "*S0000" + web2;
                w.loadUrl(url);
            }
        });

        Button lineButton = (Button) findViewById(R.id.lineButton);
        lineButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String url = web1 + "*F0000" + web2;
                w.loadUrl(url);
            }
        });

        ToggleButton controlButton = (ToggleButton) findViewById(R.id.controlButton);

        controlButton.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    String url = web1 + "*E0001" + web2;
                    w.loadUrl(url);
                } else {
                    String url = web1 + "*E0000" + web2;
                    w.loadUrl(url);
                }
            }
        });

        Button displayADCButton = (Button) findViewById(R.id.displayADCButton);
        displayADCButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String url = web1 + "*A0000" + web2;
                w.loadUrl(url);
            }
        });

        Button calibrateWhiteButton = (Button) findViewById(R.id.calibrateWhiteButton);
        calibrateWhiteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String url = web1 + "*W0000" + web2;
                w.loadUrl(url);
            }
        });

        Button calibrateBlackButton = (Button) findViewById(R.id.calibrateBlackButton);
        calibrateBlackButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String url = web1 + "*B0000" + web2;
                w.loadUrl(url);
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
