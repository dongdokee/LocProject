package com.example.dongdokee.locproject.UI.DrawableViewPackage;

import android.graphics.Color;
import android.widget.ImageView;

import com.example.dongdokee.locproject.UI.CoordinateSystem;
import com.example.dongdokee.locproject.UI.DrawableView;

/**
 * Created by dongdokee on 2015-12-02.
 */
public class ParticlesInGlobalView extends DrawableView {
    public ParticlesInGlobalView(ImageView imageView_, int bitmap_width_, int bitmap_height_, int view_width_, int view_height_, int circle_radius_, int cross_side_) {
        super(imageView_, bitmap_width_, bitmap_height_, circle_radius_, cross_side_);

        bitmap_width = bitmap_width_;
        bitmap_height = bitmap_height_;
        view_width = view_width_;
        view_height = view_height_;

        mSystem = new CoordinateSystem(0, 0, bitmap_width, bitmap_height, view_width, view_height);

    }
    private int bitmap_width;
    private int bitmap_height;
    private double view_width;
    private double view_height;

    private CoordinateSystem mSystem;

    public void update(double[] xs, double[] ys)
    {
        // clear view
        clearView();

        // translate
        float[][] translated_coordiante = mSystem.translate(xs, ys);

        // draw circle
        setColor(Color.BLACK);
        drawCircle(translated_coordiante);

        // draw ap
        setColor(Color.RED);
        float[] ap_coordinate = mSystem.translate(0, 0);
        drawX(ap_coordinate[0], ap_coordinate[1]);
    }
}
