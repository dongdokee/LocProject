package com.example.dongdokee.locproject.UI.DrawableViewPackage;

import android.graphics.Color;
import android.widget.ImageView;

import com.example.dongdokee.locproject.UI.Coordinate;
import com.example.dongdokee.locproject.UI.CoordinateSystem;
import com.example.dongdokee.locproject.UI.DrawableView;

import java.util.ArrayList;

/**
 * Created by dongdokee on 2015-12-02.
 */
public class TrajectoryView extends DrawableView {
    public TrajectoryView(ImageView imageView_, int bitmap_width_, int bitmap_height_, int view_width_, int view_height_, int circle_radius_, int cross_side_) {
        super(imageView_, bitmap_width_, bitmap_height_, circle_radius_, cross_side_);

        bitmap_width = bitmap_width_;
        bitmap_height = bitmap_height_;
        view_width = view_width_;
        view_height = view_height_;

        mSystem = new CoordinateSystem(0, 0, bitmap_width, bitmap_height, view_width, view_height);

        pinpoints = new ArrayList<>();
    }
    private int bitmap_width;
    private int bitmap_height;
    private double view_width;
    private double view_height;

    private CoordinateSystem mSystem;
    // pinpoint coordinates in double
    private ArrayList<Coordinate> pinpoints;

    // coordinate system ( bitmap - map coordinate mapping )

    // draw current position (always center?)

    // update trajectory
    // 1. current position
    // 2. write the current position to locally stored map in this class
    // 3. update the other pinpoint position
    public void update(double x, double y)
    {
        // clear view
        clearView();

        // add pinpoint
        pinpoints.add(new Coordinate(x, y));

        // setting view centered on (x, y)
        mSystem.set_param(x, y, bitmap_width, bitmap_height, view_width, view_height);

        // calculate translated coordinate of all pinpoints
        float[][] translated_coordinates = mSystem.translate(pinpoints);

        // draw it with circles and line?
        setColor(Color.BLACK);
        drawCircle(translated_coordinates);
        setColor(Color.RED);
        drawCircle(translated_coordinates[translated_coordinates.length - 1][0], translated_coordinates[translated_coordinates.length - 1][1]);

        setColor(Color.CYAN);
        drawLine(translated_coordinates);
    }
}
