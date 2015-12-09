package com.example.dongdokee.locproject;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.dongdokee.locproject.Draw.DrawModule;
import com.example.dongdokee.locproject.Map.Map;
import com.example.dongdokee.locproject.Sensors.InertialThread;
import com.example.dongdokee.locproject.UI.UIManager;

public class MainActivity extends AppCompatActivity {

    public InertialThread inertialThread;
    public Handler handler;

    public DrawModule mDraw;

    public Map map;

    public UIManager uiManager;



    public TextView step_view;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);



        uiManager = UIManager.getInstance();
        uiManager.init(this, 300, 200, 30, 20, 6, 12);
        //uiManager = new UIManager(this, 270, 200, 26, 20, 6, 12);

        Button particleBtn = (Button) findViewById(R.id.particleViewBtn);
        particleBtn.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, ParticleActivity.class);
                startActivity(intent);
            }
        });

        inertialThread = new InertialThread(this, 0, 0, 0, 0);
        inertialThread.start();

        handler = new Handler();

        init();
        uiManager.init();

        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                start_navigation();
            }
        }, 1000);
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


    static {
        System.loadLibrary("locproj");
    }

    // native initialization function
    public native void init();
    public native void start_navigation();
    public native void test();
}
