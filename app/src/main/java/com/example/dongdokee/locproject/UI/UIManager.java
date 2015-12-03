package com.example.dongdokee.locproject.UI;

import android.app.Activity;
import android.graphics.Bitmap;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.dongdokee.locproject.UI.DrawableViewPackage.BestParticleInGlobalView;
import com.example.dongdokee.locproject.UI.DrawableViewPackage.ParticlesInGlobalView;
import com.example.dongdokee.locproject.UI.DrawableViewPackage.TrajectoryView;
import com.example.dongdokee.locproject.UI.TextableViewPackage.StepView;

/**
 * Created by dongdokee on 2015-11-20.
 */
public class UIManager {
    // constructor
    private Activity activity;

    public UIManager(Activity activity_, TextView step_view, ImageView trajectory_view, ImageView best_particle_view, ImageView all_particle_view) {
        activity = activity_;

        //draw_module = new DrawModule(10, 10, 100);
        trajectoryView = new TrajectoryView(trajectory_view, 240, 320, 18, 24, 7, 14);
        bestParticleInGlobalView = new BestParticleInGlobalView(best_particle_view, 240, 320, 18, 24, 7, 14);
        particlesInGlobalView = new ParticlesInGlobalView(all_particle_view, 240, 320, 18, 24, 7, 14);
        stepView = new StepView(step_view);
    }

    private TrajectoryView trajectoryView;
    public void update_trajectory_view(double x, double y)
    {
        trajectoryView.update(x, y);
        show_view(trajectoryView);
    }

    private BestParticleInGlobalView bestParticleInGlobalView;
    public void update_best_particle_view(double x, double y)
    {
        bestParticleInGlobalView.update(x, y);
        show_view(bestParticleInGlobalView);
    }

    private ParticlesInGlobalView particlesInGlobalView;
    public void update_all_particle_view(double[] x, double[] y)
    {
        particlesInGlobalView.update(x, y);
        show_view(particlesInGlobalView);
    }

    private StepView stepView;
    public void update_step(int step_num) {
        stepView.update(step_num);
        show_view(stepView);
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

    public native void init();
}
