package com.example.dongdokee.locproject.UI;

import android.app.Activity;
import android.graphics.Bitmap;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.dongdokee.locproject.UI.DrawableViewPackage.BestParticleInGlobalView;
import com.example.dongdokee.locproject.UI.DrawableViewPackage.ParticlesInGlobalView;
import com.example.dongdokee.locproject.UI.DrawableViewPackage.TrajectoryView;
import com.example.dongdokee.locproject.UI.TextableViewPackage.StepView;

/**
 * Created by dongdokee on 2015-11-20.
 */

// change to singletone

public class UIManager {
    // constructor
    private Activity activity;

    private static volatile UIManager instance = null;
    private UIManager() {}
    public static UIManager getInstance() {
        if (instance == null) {
            synchronized (UIManager.class) {
                if (instance == null) {
                    instance = new UIManager();
                }
            }
        }
        return instance;
    }


    //public UIManager(Activity activity_, int bitmap_width, int bitmap_height, double view_width, double view_height, int circle_radius, int cross_side) {
    public void init(Activity activity_, int bitmap_width, int bitmap_height, double view_width, double view_height, int circle_radius, int cross_side) {
        activity = activity_;

        //draw_module = new DrawModule(10, 10, 100);
        synchronized (UIManager.class) {
            trajectoryView = new TrajectoryView(null, bitmap_width, bitmap_height, view_width, view_height, circle_radius, cross_side);
            bestParticleInGlobalView = new BestParticleInGlobalView(null, bitmap_width, bitmap_height, view_width, view_height, circle_radius, cross_side);
            particlesInGlobalView = new ParticlesInGlobalView(null, bitmap_width, bitmap_height, view_width, view_height, circle_radius, cross_side);
            stepView = new StepView(null);
        }
    }

    private TrajectoryView trajectoryView;
    public void update_trajectory_view(double x, double y)
    {
        if (trajectoryView != null) {
            synchronized(trajectoryView) {

                trajectoryView.update(x, y);
                show_view(trajectoryView);
            }
        }
    }

    private BestParticleInGlobalView bestParticleInGlobalView;
    public void update_best_particle_view(double[] x, double[] y)
    {
        if (bestParticleInGlobalView != null) {
            synchronized(bestParticleInGlobalView) {
                bestParticleInGlobalView.update(x, y);
                show_view(bestParticleInGlobalView);
            }
        }
    }

    private ParticlesInGlobalView particlesInGlobalView;
    public void update_all_particle_view(double[] x, double[] y)
    {
        if (particlesInGlobalView != null) {
            synchronized(particlesInGlobalView) {
                particlesInGlobalView.update(x, y);
                show_view(particlesInGlobalView);
            }
        }
    }

    private StepView stepView;
    public void update_step(int step_num) {
        if (stepView != null) {
            synchronized(stepView) {
                stepView.update(step_num);
                show_view(stepView);
            }
        }
    }


    public void show_view(final DrawableView view) {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                view.applyBitmap();
            }
        });
    }

    public void show_view(final TextableView view) {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                view.applyView();
            }
        });
    }

    public void register_step_view(TextView step_view) {
        if (stepView != null) {
            synchronized (stepView) {
                stepView.registerView(step_view);
                show_view(stepView);
            }
        }
    }
    public void unregister_step_view() {
        if (stepView != null) {
            synchronized (stepView) {
                stepView.unregister();
            }
        }
    }
    public void register_all_view(ImageView img_view) {
        if (particlesInGlobalView != null) {
            synchronized (particlesInGlobalView) {
                particlesInGlobalView.registerView(img_view);
                show_view(particlesInGlobalView);
            }
        }
    }
    public void unregister_all_view() {
        if (particlesInGlobalView != null) {
            synchronized (particlesInGlobalView) {
                particlesInGlobalView.unregisterView();
            }
        }
    }
    public void register_best_view(ImageView img_view) {
        if (bestParticleInGlobalView != null) {
            synchronized (bestParticleInGlobalView) {
                bestParticleInGlobalView.registerView(img_view);
                show_view(bestParticleInGlobalView);
            }
        }
    }
    public void unregister_best_view() {
        if (bestParticleInGlobalView != null) {
            synchronized (bestParticleInGlobalView) {
                bestParticleInGlobalView.unregisterView();
            }
        }
    }
    public void register_trajectory_view(ImageView img_view) {
        if (trajectoryView != null) {
            synchronized (trajectoryView) {
                trajectoryView.registerView(img_view);
                show_view(trajectoryView);
            }
        }
    }
    public void unregister_trajectory_view() {
        if (trajectoryView != null) {
            synchronized (trajectoryView) {
                trajectoryView.unregisterView();
            }
        }
    }

    public native void init();
}
