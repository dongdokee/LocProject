package com.example.dongdokee.locproject.Draw;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.widget.ImageView;

import com.example.dongdokee.locproject.Map.Map;

/**
 * Created by dongdokee on 2015-11-11.
 */
public class DrawModule {
    //private ImageView imgView; // image view where will be drawn
    private Canvas canvas;
    private Paint paint;
    private Bitmap bitmap;

    private float width;
    private float height;

    private int bitmap_width;
    private int bitmap_height;

    private double scale;
    private float radius;

    private double cx;
    private double cy;

    // scale?
    // for example, what length will be shown in view? (average side length?)
    // the ratio of
    // for example, if we will show the 5 * 5 meter area of map
    // width, aspect,             generate bitmap    // constructor
    // translate the coordinate of map to bitmap coordinate  //function


    public DrawModule()
    {
        //imgView = null;
        canvas = null;
        paint = null;
        bitmap = null;
    }

    // width is view window width of map (map scale)
    // aspect is aspect ratio of (height/width)           view and view window aspect are same
    // resolution means the minimum number of pixels in width ( bitmap scale) )
    public DrawModule(float width_, float height_, int resolution)
    {
        //imgView = imgView_;
        width = width_;
        height = height_;

        bitmap_width = (int)(width * resolution);
        bitmap_height = (int)(height * resolution);

        scale = bitmap_width / width;
        radius = (float)( (bitmap_width+bitmap_height) * 0.5 * 0.05 );

        bitmap = Bitmap.createBitmap(bitmap_width, bitmap_height, Bitmap.Config.ARGB_8888);
        canvas = new Canvas(bitmap);
        paint = new Paint();

        paint.setStrokeWidth(5);
    }

    public float[] translate_coord(double x, double y)
    {
        // 1. map coordinate to view window coordinate  ( x - cx, y - cy )
        double vx = x - cx + width/2;
        double vy = cy - y + height/2;

        // 2. enlarge to bitmap scale
        float result[] = {(float)(vx * scale), (float)(vy * scale)};
        return result;
    }
    public void setCenter(double x, double y)
    {
        cx = x;
        cy = y;
    }

    public void applyBitmap()
    {
        //imgView.setImageBitmap(bitmap);

    }

    public void clear()
    {
        canvas.drawColor(Color.WHITE);
    }

    public void drawX(double x, double y)
    {
        float coordinate[] = translate_coord(x, y);

        canvas.drawLine(coordinate[0]-radius/2, coordinate[1]-radius/2, coordinate[0]+radius/2, coordinate[1]+radius/2, paint);
        canvas.drawLine(coordinate[0] - radius/2, coordinate[1] + radius/2, coordinate[0] + radius/2, coordinate[1] - radius/2, paint);
    }

    public void drawCircle(double[] x, double[] y)
    {
        for (int i = 0 ; i < x.length ; i++)
        {
            float coordinate[] = translate_coord(x[i], y[i]);
            canvas.drawCircle(coordinate[0], coordinate[1], radius/5, paint);
        }
    }

    public void drawLines(double[] xs, double[] ys) {
        float[] translated_xs = new float[xs.length];
        float[] translated_ys = new float[ys.length];
        for (int i = 0 ; i < xs.length ; i++)
        {
            float coordinate[] = translate_coord(xs[i], ys[i]);
            translated_xs[i] = coordinate[0];
            translated_ys[i] = coordinate[1];
        }

        for (int i = 0 ; i < xs.length-1 ; i++) {
            canvas.drawLine(translated_xs[i], translated_ys[i], translated_xs[i+1], translated_ys[i+1], paint);
        }
    }


    // particle draw methods
    public void draw_specific_particle(double ap_x, double ap_y, double xs[], double ys[]) {
        clear();
        drawX(ap_x, ap_y);

        drawCircle(xs, ys);
        drawLines(xs, ys);
    }



    public Bitmap getBitmap() { return bitmap; }
}
