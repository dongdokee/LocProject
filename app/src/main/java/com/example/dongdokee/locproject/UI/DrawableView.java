package com.example.dongdokee.locproject.UI;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.widget.ImageView;

/**
 * Created by dongdokee on 2015-12-02.
 */
public class DrawableView {
    private ImageView imageView;
    private Canvas canvas;
    private Paint paint;
    private Bitmap bitmap;

    // in terms of pixel
    private int bitmap_width;
    private int bitmap_height;

    // size of primitive in pixels
    private int circle_radius;
    private int cross_side;

    public DrawableView(ImageView imageView_, int bitmap_width_, int bitmap_height_, int circle_radius_, int cross_side_)
    {
        imageView = imageView_;

        // any initialization tasks
        bitmap_width = bitmap_width_;
        bitmap_height = bitmap_height_;

        circle_radius = circle_radius_;
        cross_side = cross_side_;

        bitmap = Bitmap.createBitmap(bitmap_width, bitmap_height, Bitmap.Config.ARGB_8888);
        canvas = new Canvas(bitmap);
        paint = new Paint();

        paint.setStrokeWidth(3);

    }

    public void applyBitmap()
    {
        imageView.setImageBitmap(bitmap);
    }

    public void clearView()
    {
        canvas.drawColor(Color.WHITE);
    }

    public void setColor(int color)
    {
        paint.setColor(color);
    }

    public void drawX(float x, float y)
    {
        canvas.drawLine(x - cross_side/2, y - cross_side/2, x + cross_side/2, y + cross_side/2, paint);
        canvas.drawLine(x - cross_side/2, y + cross_side/2, x + cross_side/2, y - cross_side/2, paint);
    }

    public void drawX(float[] x, float[] y)
    {
        if (x.length != y.length)
            return;

        for (int i = 0 ; i < x.length ; i++)
            drawX(x[i], y[i]);
    }

    public void drawX(float[][] coordinates)
    {
        for (int i = 0 ; i < coordinates.length ; i++)
            drawX(coordinates[i][0], coordinates[i][1]);
    }

    public void drawCircle(float x, float y)
    {
        canvas.drawCircle(x, y, circle_radius, paint);
    }
    public void drawCircle(float[] x, float[] y) {
        if (x.length != y.length)
            return;

        for (int i = 0; i < x.length; i++)
            drawCircle(x[i], y[i]);
    }

    public void drawCircle(float[][] coordinates)
    {
        for (int i = 0 ; i < coordinates.length ; i++)
            drawCircle(coordinates[i][0], coordinates[i][1]);
    }

    public void drawLine(float x1, float y1, float x2, float y2)
    {
        canvas.drawLine(x1, y1, x2, y2, paint);
    }

    public void drawLine(float[] x, float[] y)
    {
        if (x.length != y.length)
            return;

        for (int i = 0 ; i < x.length-1 ; i++)
            drawLine(x[i], y[i], x[i+1], y[i+1]);
    }

    public void drawLine(float[][] points)
    {
        for (int i = 0 ; i < points.length-1 ; i++)
            drawLine(points[i][0], points[i][1], points[i+1][0], points[i+1][1]);
    }

    public Bitmap getBitmap() { return bitmap; }

}
