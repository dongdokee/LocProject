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
public class BestParticleInGlobalView extends DrawableView {
    public BestParticleInGlobalView(ImageView imageView_, int bitmap_width_, int bitmap_height_, double view_width_, double view_height_, int circle_radius_, int cross_side_) {
        super(imageView_, bitmap_width_, bitmap_height_, circle_radius_, cross_side_);

        bitmap_width = bitmap_width_;
        bitmap_height = bitmap_height_;
        view_width = view_width_;
        view_height = view_height_;

        mSystem = new CoordinateSystem(0, 0, bitmap_width, bitmap_height, view_width, view_height);

        last_coordinate = null;

        clearView();
        float[] translated_coordinate = mSystem.translate(0, 0);
        drawX(translated_coordinate[0], translated_coordinate[1]);

    }
    private int bitmap_width;
    private int bitmap_height;
    private double view_width;
    private double view_height;

    private CoordinateSystem mSystem;

    private float[] last_coordinate;

    public void update(double[] x, double[] y)
    {
        // translate
        float[][] translated_coordinates = mSystem.translate(x, y);

        // draw it with circles and line?
        setColor(Color.BLACK);
        drawCircle(translated_coordinates);
        setColor(Color.RED);
        drawCircle(translated_coordinates[translated_coordinates.length - 1][0], translated_coordinates[translated_coordinates.length - 1][1]);

        setColor(Color.CYAN);
        drawLine(translated_coordinates);
    }
}
