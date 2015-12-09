package com.example.dongdokee.locproject;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.dongdokee.locproject.UI.UIManager;

/**
 * Created by dongdokee on 2015-12-08.
 */
public class ParticleActivity extends Activity {
    private ImageView bestView;
    private ImageView allView;
    private ImageView trajectoryView;
    private TextView statusView;

    private UIManager uiManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_particle);
        // load views
        bestView = (ImageView)findViewById(R.id.bestParticleView);
        allView = (ImageView)findViewById(R.id.allParticleView);
        trajectoryView = (ImageView)findViewById(R.id.trajectoryView);
        statusView = (TextView)findViewById(R.id.statusView);

        if (bestView == null)
        {
            Log.i("Activity", "SIBAL TRESH");
        }

        uiManager = UIManager.getInstance();
        uiManager.register_best_view(bestView);
        uiManager.register_all_view(allView);
        uiManager.register_trajectory_view(trajectoryView);
        uiManager.register_step_view(statusView);

        Log.i("Activity", "register done");
    }

    @Override
    protected void onDestroy() {
        uiManager.unregister_best_view();
        uiManager.unregister_all_view();
        uiManager.unregister_trajectory_view();
        uiManager.unregister_step_view();

        Log.i("Activity", "unregister done");
        super.onDestroy();
    }
}
