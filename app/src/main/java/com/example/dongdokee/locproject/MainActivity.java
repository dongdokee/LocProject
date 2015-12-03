package com.example.dongdokee.locproject;

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
    public ImageView img_view;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //init();
        //step_view = (TextView)findViewById(R.id.stepnum_text);
        img_view = (ImageView)findViewById(R.id.imgView);
        //uiManager = new UIManager(this, step_view, null);
        //uiManager.init();
        uiManager = new UIManager(this, step_view, img_view, img_view, img_view);

        //inertialThread = new InertialThread(this, 0, 0, 0, 0);
        //inertialThread.start();

        handler = new Handler();

        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                //test();
                //start_navigation();
                //uiManager.update_trajectory_view(0, 0);
                //uiManager.update_best_particle_view(1, 1);
                double[] x = {1,2,3,4,5};
                double[] y = {5,4,3,2,1};
                uiManager.update_all_particle_view(x, y);
            }
        }, 1000);
/*
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                //test();
                //start_navigation();
                //uiManager.update_trajectory_view(0, 1);
                uiManager.update_best_particle_view(2, 2);
            }
        }, 2000);

        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                //test();
                //start_navigation();
                //uiManager.update_trajectory_view(1, 1);
                uiManager.update_best_particle_view(2, 3);
            }
        }, 3000);

        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                //test();
                //start_navigation();
                //uiManager.update_trajectory_view(2, 2);
                uiManager.update_best_particle_view(-1, 3);
            }
        }, 4000);*/
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
