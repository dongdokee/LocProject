package com.example.dongdokee.locproject.Map;

import android.app.Activity;
import android.util.Log;
import android.widget.ImageView;

import com.example.dongdokee.locproject.Draw.DrawModule;

/**
 * Created by dongdokee on 2015-11-11.
 */

// MAP
public class Map {
    public double map_width;
    public double map_height;

    public double particle_xs[];
    public double particle_ys[];
    // particles position deploy
    //public double ap_x;
    //public double ap_y;

    public DrawModule mDraw;
    public ImageView imgView;
    public Activity mActivity;

    public Map()
    {}

    public Map(double map_width_, double map_height_, int num_particles, ImageView imgView_, Activity mActivity_)
    {
        map_width = map_width_;
        map_height = map_height_; // in real meter


        /*ap_x = 0;
        ap_y = 0;

        particle_xs = new double[num_particles];
        particle_ys = new double[num_particles];*/

        imgView = imgView_;
        mActivity = mActivity_;
    }

    // AP position deploy
    /*public void update_ap(double x, double y)
    {
        ap_x = x;
        ap_y = y;
    } */

    // update particles position
    /*public void update_particles(double xs[], double ys[])
    {
        particle_xs = xs.clone();
        particle_ys = ys.clone();
    }*/
/*
    public void init_global_draw()
    {
        mDraw = new DrawModule(imgView, (float)map_width, (float)map_height, 200 );
        mDraw.setCenter(0, 0);
    }

    // draw global view
    public void draw(final double ap_x, final double ap_y, final double[] x, final double[] y)
    {
        //for (int i=0 ; i < x.length ; i++)
        //{
        //    Log.d("FUCK", String.valueOf(x[i]) + " " + String.valueOf(y[i]));
        //}
        mActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                // this must be run in MAIN THREAD
                mDraw.clear();
                mDraw.drawX(ap_x, ap_y);
                mDraw.drawCircle(x, y);
                mDraw.applyBitmap();
            }
        });
    }
*/
/*    // draw (best) particle view ?
    public void draw_particle(final double ap_x, final double ap_y, final double[] x_traj, final double[] y_traj)
    {
        mActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mDraw.clear();
                mDraw.drawX(ap_x, ap_y);
                mDraw.drawCircle(x_traj, y_traj);

                // draw line
                mDraw.applyBitmap();
            }
        });
    }*/
}
