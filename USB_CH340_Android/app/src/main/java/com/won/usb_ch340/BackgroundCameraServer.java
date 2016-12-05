package com.won.usb_ch340;

import android.app.Activity;
import android.app.Service;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.ImageFormat;
import android.graphics.PixelFormat;
import android.graphics.Rect;
import android.graphics.YuvImage;
import android.hardware.Camera;
import android.os.IBinder;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.WindowManager;
import android.widget.LinearLayout;

import com.unity3d.player.UnityPlayer;

import java.io.ByteArrayOutputStream;

/**
 * Created by yyy on 2016/11/30.
 */
public class BackgroundCameraServer extends Service implements Camera.PreviewCallback {
    final String TAG = "com.yang.cameraservice";
    Camera camera;
    SurfaceView surfaceView;

    boolean dealing = false;
    int[][][] temp;
    //tow public varies is the glove position data to send to unity.
    public int[] center = new int[2];
    public int distance = 0;

    Activity mActivity;
    LinearLayout mFloatLayout;
    WindowManager.LayoutParams wmParams;
    WindowManager mWindowManager;

    private static BackgroundCameraServer instance = null;
    public static BackgroundCameraServer getInstance()
    {
        if(instance == null)
        {
            synchronized (BackgroundCameraServer.class)
            {
                Log.i("cameraserver", "error to create instance in camera server");
                if(instance == null) instance = new BackgroundCameraServer();
            }
        }
        return instance;
    }
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate()
    {
        super.onCreate();
        instance = this;
        mActivity = (Activity)getBaseContext();
        Log.i(TAG, "onCreate of BackgroundCameraServer");
        createFloatView();
    }

    @Override
    public void onDestroy()
    {
        // TODO Auto-generated method stub
        super.onDestroy();
        if(mFloatLayout != null)
        {
            //移除悬浮窗口
            mWindowManager.removeView(mFloatLayout);
        }
        if(camera != null)
        {
            camera.setPreviewCallback(null);
            camera.stopPreview();
            camera.release();
            camera = null;
        }
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        return  super.onStartCommand(intent, flags, startId);
    }

    /**
     * the class to deal the surfaceCallBack by WindowManager.
     */
    private class  SurfaceCamera implements SurfaceHolder.Callback {
        @Override
        public void surfaceCreated(SurfaceHolder holder) {
            Log.i(TAG, "surface created");
        }

        @Override
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
            try {
                Log.i(TAG, "sufacechanged");
                camera = Camera.open();
                camera.setPreviewDisplay(holder);
                Camera.Parameters params = camera.getParameters();
                params.setPreviewSize(640, 480);
                //params.setPreviewFormat(ImageFormat.RGB_565);
                //params.setPreviewFpsRange(3, 5);
                camera.setParameters(params);
                camera.startPreview();
                camera.setPreviewCallback(BackgroundCameraServer.this);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        @Override
        public void surfaceDestroyed(SurfaceHolder holder) {
            if (camera != null) {
                camera.setPreviewCallback(null);
                camera.release();
            }
            camera = null;
        }
    }

    private class  SurfaceDealment implements SurfaceHolder.Callback
    {
        @Override
        public void surfaceCreated(SurfaceHolder holder) {

        }

        @Override
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

        }

        @Override
        public void surfaceDestroyed(SurfaceHolder holder) {

        }
    }
    /**
     * the data.length = camera.getParameters().getPreviewSize().width
     * 						*camera.getParameters().getPreviewSize().height * 3 / 2;
     * 	its in 	yuv420sp format.
     * @param data
     * @param camera
     */
    @Override
    public void onPreviewFrame(byte[] data, Camera camera) {
        if(!dealing) {
            dealing = true;
            final byte[] sdata = data.clone();
            final int width = camera.getParameters().getPreviewSize().width;
            final int height = camera.getParameters().getPreviewSize().height;
            //Log.i(TAG, "vedio data come ..." + data.length + " " + camera.getParameters().getPreviewSize().width);
            new Thread(new Runnable() {
                @Override
                public void run() {
                    rawByteArray2RGBABitmap2(sdata, width, height);
                    dealing = false;
                }
            }).start();
        }
    }
    public byte[] convertYuvToJpeg(byte[] data, Camera camera) {
        YuvImage image = new YuvImage(data, ImageFormat.NV21,
                camera.getParameters().getPreviewSize().width, camera.getParameters().getPreviewSize().height, null);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        int quality = 100; //set quality
        image.compressToJpeg(new Rect(0, 0, camera.getParameters().getPreviewSize().width, camera.getParameters().getPreviewSize().height), quality, baos);
        return baos.toByteArray();
    }
    void rotateYUV240SP(byte[] src,byte[] des,int width,int height)	{
        int wh = width * height;
        //旋转Y
        int k = 0;
        for(int i=0;i<width;i++) {
            for(int j=0;j<height;j++)
            {
                des[k] = src[width*j + i];
                k++;
            }
        }
        for(int i=0;i<width;i+=2) {
            for(int j=0;j<height/2;j++)
            {
                des[k] = src[wh+ width*j + i];
                des[k+1]=src[wh + width*j + i+1];
                k+=2;
            }
        }
    }

    public Bitmap rawByteArray2RGBABitmap2(byte[] data, int width, int height) {
        int frameSize = width * height;

        if(temp == null)
            temp = new int[height][width][3];

        int centerX = 0;
        int centerY = 0;
        int dotAmount = 0;

        //Arrays.fill(rgba,0);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int y = (0xff & ((int) data[i * width + j]));
                int u = (0xff & ((int) data[frameSize + (i >> 1) * width + (j & ~1) + 0]));
                int v = (0xff & ((int) data[frameSize + (i >> 1) * width + (j & ~1) + 1]));
                y = y < 16 ? 16 : y;

                int r = (int) (1.164f * (y - 16) + 1.596f * (v - 128));
                int g = (int) (1.164f * (y - 16) - 0.813f * (v - 128) - 0.391f * (u - 128));
                int b = (int) (1.164f * (y - 16) + 2.018f * (u - 128));

                //if(i == height * 0.5f && j == width * 0.5f) Log.i(TAG, "R:" + r + "G:" + g + "B:" + b);
                if ( r > 255 && g > 255 && b > 255 && y > 250 )//(r > 180 && g > 200 && b < 180 && y > 180) || (r > 220 && g > 220 && b > 220 && y > 220)
                {
                    temp[i][j][0] = r;
                    temp[i][j][1] = g;
                    temp[i][j][2] = b;
                }
                else
                {
                    temp[i][j][0] = 0;
                    temp[i][j][1] = 0;
                    temp[i][j][2] = 0;
                }
                //rgba[i * width + j] = 0xff000000 + (b << 16) + (g << 8) + r;
            }
        }
        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                int r = temp[i][j][0];
                int g = temp[i][j][1];
                int b = temp[i][j][2];

                if(r != 0 || g != 0 || b != 0)
                {
                    if(isFilterTrue(i, j, temp))
                    {
                        dotAmount++;
                        centerX += j;
                        centerY += i;
                    }
                }
            }
        }
        if(dotAmount > 300 && dotAmount < 4800 ) {
            centerX /= dotAmount;
            centerY /= dotAmount;
            center[0] = centerX;
            center[1] = centerY;
            distance = 4800 - dotAmount;
            UnityPlayer.UnitySendMessage("VRGloveFirstPerson", "USBmsgReciever", "dots amount:" + dotAmount + "the center:(" + centerX + "," + centerY + ")");
            Log.i(TAG,"dots amount:" + dotAmount + "the center:(" + centerX + "," + centerY + ")");
        }
        return null;
    }

    private boolean isFilterTrue(int i, int j, int[][][] temp) {
        int mum = 0;
        if(temp[i-1][j-1][0] != 0 || temp[i-1][j-1][1] != 0 ||temp[i-1][j-1][2] != 0 ) mum++;
        if(temp[i-1][j][0] != 0 || temp[i-1][j][1] != 0 ||temp[i-1][j][2] != 0 ) mum++;
        if(temp[i-1][j+1][0] != 0 || temp[i-1][j+1][1] != 0 ||temp[i-1][j+1][2] != 0 ) mum++;
        if(temp[i][j-1][0] != 0 || temp[i][j-1][1] != 0 ||temp[i][j-1][2] != 0 ) mum++;
        if(temp[i][j+1][0] != 0 || temp[i][j+1][1] != 0 ||temp[i][j+1][2] != 0 ) mum++;
        if(temp[i+1][j+1][0] != 0 || temp[i+1][j+1][1] != 0 ||temp[i+1][j+1][2] != 0 ) mum++;
        if(temp[i+1][j-1][0] != 0 || temp[i+1][j-1][1] != 0 ||temp[i+1][j-1][2] != 0 ) mum++;
        if(temp[i+1][j][0] != 0 || temp[i+1][j][1] != 0 ||temp[i+1][j][2] != 0 ) mum++;

        if(mum > 3) return  true;
        return false;
    }

    private void createFloatView()
    {
        wmParams = new WindowManager.LayoutParams();
        mWindowManager = (WindowManager)mActivity.getSystemService(mActivity.WINDOW_SERVICE);
        wmParams.type = WindowManager.LayoutParams.TYPE_PHONE;
        wmParams.format = PixelFormat.RGBA_8888;
        wmParams.flags = WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
        //wmParams.screenOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;
        wmParams.gravity = Gravity.CENTER | Gravity.TOP;
        // 以屏幕左上角为原点，设置x、y初始值，相对于gravity
        wmParams.x = 0;
        wmParams.y = 0;

        wmParams.width = 640;
        wmParams.height = 480;

        LayoutInflater inflater = LayoutInflater.from(mActivity);
        //获取浮动窗口视图所在布局
        mFloatLayout = (LinearLayout) inflater.inflate(R.layout.surface_view_window, null);
        //添加mFloatLayout
        mWindowManager.addView(mFloatLayout, wmParams);
        //浮动窗口按钮
        surfaceView = (SurfaceView)mFloatLayout.findViewById(R.id.surface_window);
        surfaceView.getHolder().addCallback(new SurfaceCamera());
        surfaceView.getHolder().setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);

        mFloatLayout.measure(View.MeasureSpec.makeMeasureSpec(0,
                View.MeasureSpec.UNSPECIFIED), View.MeasureSpec
                .makeMeasureSpec(0, View.MeasureSpec.UNSPECIFIED));

    }
}
