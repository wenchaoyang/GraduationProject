package com.won.usb_ch340;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbManager;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.unity3d.player.UnityPlayer;
import com.unity3d.player.UnityPlayerActivity;

import java.io.IOException;
import java.nio.charset.Charset;


public class USBOTGCenter extends UnityPlayerActivity {
	private final String TAG = "com.won.usb_ch340";
	private static final String ACTION_USB_PERMISSION = "com.wondfo.USB_PERMISSION";

	private CH340AndroidDriver ch340AndroidDriver;
	private Context mContext = null;
	private Activity mActivity = null;
	private final int baurt = 9600;
	private boolean isExits = false;
	private boolean isGet = false;
	private final int BUF_SIZE = 1024;// 接收缓冲区大小
	private int receiveDataLength;

	private final int MSG_USB_INSERT = 0xAA;
	private final int MSG_USB_UNINSERT = 0xBB;
	private final int MSG_USB_GETDATA = 0xCC;

    private class MyHandler extends Handler {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            switch (msg.what) {
                case MSG_USB_GETDATA:
                    if (isGet && receiveDataLength > 7)
					{

						byte[] bdata = (byte[])msg.obj;
						int len = 0;
						while('\r' != bdata[len] && '\0' != bdata[len])
						{
							++len;
						}
						byte[] realdata = new byte[len];
						for(int i = 0; i < len; ++i)
						{
							realdata[i] = bdata[i];
						}
						//realdata[len] = '\0';
						String str = new String(realdata,Charset.forName("UTF-8"));

						if('D' == bdata[0])
						{
//							str += "#" + BackgroundCameraServer.getInstance().center[0] + ":" + BackgroundCameraServer.getInstance().center[1]
//									+ ":" + BackgroundCameraServer.getInstance().distance + "\n";
							UnityPlayer.UnitySendMessage("VRGloveFirstPerson", "USBmsgReciever", str);
							Log.i(TAG,str);
						}
                    }
                    break;
                case MSG_USB_INSERT:
                    initUSB();
                    break;
                case MSG_USB_UNINSERT:
                    ch340AndroidDriver.CloseDevice();
                    break;
            }
        }
    }
    private MyHandler handler = new MyHandler();

	public USBOTGCenter(Context context)
	{
		mContext = context;
		mActivity = (Activity)context;
		mContext.registerReceiver(mUsbDeviceReceiver, new IntentFilter(
				UsbManager.ACTION_USB_DEVICE_ATTACHED));
		mContext.registerReceiver(mUsbDeviceReceiver, new IntentFilter(
				UsbManager.ACTION_USB_DEVICE_DETACHED));
		ch340AndroidDriver = new CH340AndroidDriver(
				(UsbManager) mContext.getSystemService(Context.USB_SERVICE), mContext,
				ACTION_USB_PERMISSION);
	}

	private void initUSB() {
		UsbDevice device = ch340AndroidDriver.EnumerateDevice();// 枚举设备，获取USB设备
		ch340AndroidDriver.OpenDevice(device);// 打开并连接USB
		if (ch340AndroidDriver.isConnected()) {
			boolean flags = ch340AndroidDriver.UartInit();// 初始化串口
			if (!flags) {
				Log.e(TAG, "Init Uart Error");

			} else {// 配置串口
				if (ch340AndroidDriver.SetConfig(baurt, (byte) 8, (byte) 1,
						(byte) 0, (byte) 0)) {
					Log.i(TAG, "Uart Configed");
				}
			}
		} else {
			Log.e(TAG, "ch340AndroidDriver not connected");
		}

		new Thread() {
			@Override
			public void run() {
				super.run();
				while (!isExits) {
					try {
						Thread.sleep(10);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					if (ch340AndroidDriver != null) {
						byte[] readBuffer = new byte[BUF_SIZE];
						receiveDataLength = ch340AndroidDriver.ReadData(readBuffer, readBuffer.length);
						if ( receiveDataLength> 0) {
							Message msg = new Message();
							msg.what = MSG_USB_GETDATA;
							msg.obj = readBuffer;
                            isGet = true;
							handler.sendMessage(msg);
						} else {
							isGet = false;
						}
					}
				}
			}
		}.start();
	}

	public void SendMessagebyUsb(String msg)
	{
		byte[] message = msg.getBytes();
		Log.i(TAG,msg + " bytes:" + new String(message));
		try {
			ch340AndroidDriver.WriteData(message, message.length);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	private void RecieveMessagetoUnity(String msg)
	{
		Log.i(TAG,"Unity:" + msg);
		UnityPlayer.UnitySendMessage("Canvas","USBmsgReciever",msg);
	}

	private final BroadcastReceiver mUsbDeviceReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			Log.i(TAG, "action:" + action);
			if (UsbManager.ACTION_USB_DEVICE_ATTACHED.equals(action)) {
				UsbDevice deviceFound = (UsbDevice) intent
						.getParcelableExtra(UsbManager.EXTRA_DEVICE);
				Log.i(TAG,"ACTION_USB_DEVICE_ATTACHED: " + deviceFound.toString());
				handler.sendEmptyMessage(MSG_USB_INSERT);
			} else if (UsbManager.ACTION_USB_DEVICE_DETACHED.equals(action)) {
				UsbDevice device = (UsbDevice) intent
						.getParcelableExtra(UsbManager.EXTRA_DEVICE);
				Log.i(TAG,"ACTION_USB_DEVICE_DETACHED: " + device.toString());
				handler.sendEmptyMessage(MSG_USB_UNINSERT);
			}
		}

	};
	@Override
	public void onDestroy() {
		super.onDestroy();
		isExits = true;
		ch340AndroidDriver.CloseDevice();
		mContext.unregisterReceiver(mUsbDeviceReceiver);
		Intent intent = new Intent(mContext, BackgroundCameraServer.class);
		stopService(intent);
	}
}
