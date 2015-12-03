package com.example.dongdokee.locproject.utils;

/**
 * Created by dongdokee on 2015-10-27.
 */
public class TimeStamper {
    public boolean isInit = false;
    //public boolean isInit_long = false;

    public double global_reftime = 0.0;
    public double sensor_reftime = 0.0;

    //public long global_reftime_long = 0;
    //public long sensor_reftime_long = 0;

    public TimeStamper() {
    }

    /*public double getTimestamp(double time) {
        if(!isInit) {
            global_reftime = System.nanoTime();
            sensor_reftime = time;
            isInit = true;
        }

        return global_reftime + (time - sensor_reftime);
    }*/

    /*public long getTimestamp(long time) {
        if(!isInit_long) {
            global_reftime_long = System.nanoTime();
            sensor_reftime_long = time;
            isInit_long = true;
        }

        return global_reftime_long + (time - sensor_reftime_long);
    } */

    public double getTimestamp(long time) {
        if(!isInit) {
            global_reftime = ns2s(System.nanoTime());
            sensor_reftime = ns2s(time);
            isInit = true;
        }

        return global_reftime + (ns2s(time) - sensor_reftime);
    }

    public static double ns2s(long ns)
    {
        return (double)ns/1e9;
    }

    public static double us2s(long us)
    {
        return (double)us/1e6;
    }
    public static long us2ns(long us) { return us * 1000; }
    public static int s2ms(double s)
    {
        return (int)(s*1000);
    }
}
