package com.example.dongdokee.locproject.UI;

import android.util.Log;
import android.widget.TextView;

/**
 * Created by dongdokee on 2015-12-03.
 */
public class TextableView {
    private TextView textView;
    protected String text;

    public TextableView(TextView textView_)
    {
        textView = textView_;
    }

    public void applyView()
    {
        if (textView != null) {
            Log.i("TEXTABLE", "apply performed");
            textView.setText(text);
        }
    }

    public void registerView(TextView view) {
        textView = view;
    }
    public void unregister() {
        textView = null;
    }
}
