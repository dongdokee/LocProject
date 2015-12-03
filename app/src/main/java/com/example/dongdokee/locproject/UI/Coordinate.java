package com.example.dongdokee.locproject.UI;

/**
 * Created by dongdokee on 2015-12-02.
 */
public class Coordinate {
    public double x;
    public double y;

    public Coordinate(double x_, double y_)
    {
        x = x_;
        y = y_;
    }

    public Coordinate(double[] val)
    {
        // assume size is 2
        x = val[0];
        y = val[1];
    }
}
