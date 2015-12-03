package com.example.dongdokee.locproject.UI;

import java.util.ArrayList;

/**
 * Created by dongdokee on 2015-12-02.
 */
public class CoordinateSystem {
    // cx and cy is view center of real map (in meter)
    // view width and height are also view size of real map (in meter)
    // bitmap_width and bitmap_height are the bitmap size in pixels
    public CoordinateSystem(double cx, double cy, int bitmap_width, int bitmap_height, double view_width, double view_height)
    {
        set_param(cx, cy, bitmap_width, bitmap_height, view_width, view_height);
    }

////
    /*double vx = x - cx + width/2;
    double vy = cy - y + height/2;

    // 2. enlarge to bitmap scale
    float result[] = {(float)(vx * scale), (float)(vy * scale)};*/
////

    private float a, b, scale;
    public void set_param(double cx, double cy, int bitmap_width, int bitmap_height, double view_width, double view_height)
    {
        // assume that aspect ratio of view and bitmap are same
        scale = (float)(bitmap_width / view_width);
        a = (float)(-cx + view_width/2);
        b = (float)(cy + view_height/2);
    }

    public float[] translate(double x, double y)
    {
        float[] result = {((float)x+a)*scale, (b-(float)y)*scale};
        return result;
    }
    public float[][] translate(double[] xs, double[] ys)
    {
        // assume length of xs and ys are same
        float[][] result = new float[xs.length][2];

        for (int i = 0 ; i < xs.length ; i++)
        {
            result[i] = translate(xs[i], ys[i]);
        }
        return result;

    }

    public float[][] translate(ArrayList<Coordinate> pinpoints)
    {
        float[][] result = new float[pinpoints.size()][2];
        for (int i = 0 ; i < pinpoints.size() ; i++) {
            Coordinate coordinate = pinpoints.get(i);
            result[i] = translate(coordinate.x, coordinate.y);
        }

        return result;
    }


}
