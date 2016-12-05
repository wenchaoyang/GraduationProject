package com.won.usb_ch340;

import android.app.Activity;
import android.os.Bundle;

/**
 * Created by yyy on 2016/12/2.
 */
public class CameraBridge extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
//        requestWindowFeature(Window.FEATURE_NO_TITLE);//隐藏标题
//        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
//                WindowManager.LayoutParams.FLAG_FULLSCREEN);//设置全屏
        setContentView(R.layout.window);
//        Intent intent = new Intent(, BackgroundCameraServer.class);
//        startService(intent);
    }
}
