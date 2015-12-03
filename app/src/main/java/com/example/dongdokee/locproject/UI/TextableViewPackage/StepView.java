package com.example.dongdokee.locproject.UI.TextableViewPackage;

import android.widget.TextView;

import com.example.dongdokee.locproject.UI.TextableView;

/**
 * Created by dongdokee on 2015-12-03.
 */
public class StepView extends TextableView {
    public StepView(TextView textView)
    {
        super(textView);
    }

    public void update(int step_num)
    {
        text = "step count is " + step_num;
    }
}
