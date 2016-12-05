using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using Glove.Data;
using System.Collections.Generic;

public class AndroidBridgeCenter : MonoBehaviour {
    public Transform handTransform;
    public Text text;

    float[] gloveData = new float[3] {0,0,0};
    AndroidJavaObject javaObj;

    public static List<DetectionBase> detectorList = new List<DetectionBase>();
    Vector3 handTargetEluar = Vector3.zero;
	// Use this for initialization
	void Start () {
        AndroidJavaClass jc = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
        AndroidJavaObject jo = jc.GetStatic<AndroidJavaObject>("currentActivity");
        jo.Call("runOnUiThread", new AndroidJavaRunnable(() =>
            {
                AndroidJavaObject unityContext = jo.Call<AndroidJavaObject>("getApplicationContext");
                javaObj = new AndroidJavaObject(Glove.Data.Contains.Connection.androidIdentifer, jo);
            }));
	}
	
	// Update is called once per frame
	void FixedUpdate () {
        //handTransform.localEulerAngles = Vector3.Lerp(handTransform.localEulerAngles, handTargetEluar, Time.fixedDeltaTime * 5f);
	}
    public void SendMsgUSB(string s = "")
    {
        string str = "";
        if (s == "")
        {
            str = "yeap";
            text.text += str;
        }
        else
        {
            str = s;
        }

        if (javaObj == null)
        {
            Debug.LogError("javaObj is null why");
        }
        else
        {
            javaObj.Call("SendMessagebyUsb", str);
        }

    }
    public void USBmsgReciever(string msg)
    {
        text.text = msg;
        string[] data = msg.Split(Glove.Data.Contains.Connection.dataSplit_1);
        if(data.Length > 2)
        {
            foreach(DetectionBase detector in detectorList)
            {
                switch(detector.Tag)
                {
                    case Glove.Data.Contains.Connection.tagDealRotate:
                        //detector.DataDealment(data[1]);
                        break;
                    case Glove.Data.Contains.Connection.tagDealInflect:
                        //detector.DataDealment(data[2]);
                        break;
                    default:
                        Debug.Log(detector.Tag);
                        break;
                }
            }
        }
        //text.text = "x:" + gloveData[0] + "\n\ty:" + gloveData[1] + "\n\tz:" + gloveData[2];
        Debug.Log("Recieve Message:" + msg);
    }

}
