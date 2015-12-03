package com.example.dongdokee.locproject.Sensors;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import com.example.dongdokee.locproject.utils.TimeStamper;

/**
 * Created by dongdokee on 2015-10-27.
 */
public class InertialThread extends Thread {
    public static final String TAG = InertialThread.class.getSimpleName();

    private SensorManager mSensorManager;
    private Context m_ctx;

    private Sensor accelSensor;
    private Sensor gyroSensor;
    private Sensor magnetSensor;
    private Sensor gravitySensor;

    // intervals in micro seconds
    private int accel_interval;
    private int gyro_interval;
    private int magnet_interval;
    private int gravity_interval;

    private Handler handler;
    private boolean isSense = false;
    private TimeStamper accel_timestamper = new TimeStamper();
    private TimeStamper gyro_timestamper = new TimeStamper();
    private TimeStamper magnet_timestamper = new TimeStamper();
    private TimeStamper gravity_timestamper = new TimeStamper();


    public InertialThread() {
    }

    public InertialThread(Context ctx, int accel_interval_, int gyro_interval_, int magnet_interval_, int gravity_interval_) {
        init(ctx, accel_interval_, gyro_interval_, magnet_interval_, gravity_interval_);
    }

    public void init(Context ctx, int accel_interval_, int gyro_interval_, int magnet_interval_, int gravity_interval_) {
        m_ctx = ctx;

        accel_interval = accel_interval_;
        gyro_interval = gyro_interval_;
        magnet_interval = magnet_interval_;
        gravity_interval = gravity_interval_;

        mSensorManager = (SensorManager) m_ctx.getSystemService(Context.SENSOR_SERVICE);

        accelSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        gyroSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
        magnetSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
        gravitySensor = mSensorManager.getDefaultSensor(Sensor.TYPE_GRAVITY);
    }

    @Override
    public void run() {
        Log.d(TAG, "thread runs");
        Looper.prepare();
        handler = new Handler();
        startSense();
        Looper.loop();
    }

    public void startSense()
    {
        if(!isSense) {
            Log.d(TAG, "register sensors");
            registerSensors(handler);
            isSense = true;
        }
    }

    public void stopSense() {
        if(isSense) {
            Log.d(TAG, "unregister sensors");
            unregisterSensors();
            isSense = false;
        }
    }

    public void destroyThread() {
        if(isSense) {
            unregisterSensors();
            isSense = false;
        }
        handler.removeCallbacksAndMessages(null);
        handler.getLooper().quit();
    }

    private void registerSensors(Handler handler) {
        mSensorManager.registerListener(AccelEventListener, accelSensor, accel_interval, handler);
        mSensorManager.registerListener(GyroEventListener, gyroSensor, gyro_interval, handler);
        mSensorManager.registerListener(MagnetEventListener, magnetSensor, magnet_interval, handler);
        mSensorManager.registerListener(GravityEventListener, gravitySensor, gravity_interval, handler);
    }

    private void unregisterSensors() {
        mSensorManager.unregisterListener(AccelEventListener);
        mSensorManager.unregisterListener(GyroEventListener);
        mSensorManager.unregisterListener(MagnetEventListener);
        mSensorManager.unregisterListener(GravityEventListener);
    }

    private SensorEventListener AccelEventListener = new SensorEventListener() {
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
            //do nothing
        }

        @Override
        public void onSensorChanged(SensorEvent event) {
            double timestamp = accel_timestamper.getTimestamp(event.timestamp);
            inputAccel(timestamp, event.values[0], event.values[1], event.values[2]);

        }
    };

    private SensorEventListener GyroEventListener = new SensorEventListener() {
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
            //do nothing
        }

        @Override
        public void onSensorChanged(SensorEvent event) {
            double timestamp = gyro_timestamper.getTimestamp(event.timestamp);
            inputGyro(timestamp, event.values[0], event.values[1], event.values[2]);
        }
    };

    private SensorEventListener MagnetEventListener = new SensorEventListener() {
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
            //do nothing
        }

        @Override
        public void onSensorChanged(SensorEvent event) {
            double timestamp = magnet_timestamper.getTimestamp(event.timestamp);
            inputCompass(timestamp, event.values[0], event.values[1], event.values[2]);
        }
    };

    private SensorEventListener GravityEventListener = new SensorEventListener() {
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
            //do nothing
        }

        @Override
        public void onSensorChanged(SensorEvent event) {
            double timestamp = gravity_timestamper.getTimestamp(event.timestamp);
            inputGravity(timestamp, event.values[0], event.values[1], event.values[2]);
        }
    };

    public native void inputAccel(double timestamp, double x, double y, double z);
    public native void inputGyro(double timestamp, double x, double y, double z);
    public native void inputCompass(double timestamp, double x, double y, double z);
    public native void inputGravity(double timestamp, double x, double y, double z);
}
