using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;

public class GloveDataDriver : MonoBehaviour {
    public Transform handTransform;
    public Text text;

    AndroidJavaObject javaObj;

    public static List<DetectionBase> detectorList;

    CapsuleHand handRight;

    // Use this for initialization
    void Start()
    {
        Invoke("InitDriver", 3);

        if(gameObject.GetComponentInChildren<CapsuleHand>() == null)
        {
            gameObject.AddComponent<CapsuleHand>();
        }
        handRight = gameObject.GetComponentInChildren<CapsuleHand>();

        detectorList = new List<DetectionBase>();
        detectorList.Add(new DetectionRotate());
        detectorList.Add(new DetectionInflect());
    }
    void InitDriver()
    {
        if (Application.platform == RuntimePlatform.Android)
        {
            print("Unity android model");
            AndroidJavaClass jc = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
            AndroidJavaObject jo = jc.GetStatic<AndroidJavaObject>("currentActivity");
            jo.Call("runOnUiThread", new AndroidJavaRunnable(() =>
            {
                AndroidJavaObject unityContext = jo.Call<AndroidJavaObject>("getApplicationContext");
                javaObj = new AndroidJavaObject(Glove.Data.Contains.Connection.androidIdentifer, jo);
                javaObj.Call("StartActivityCamera");
            }));
        }
        else if (Application.platform == RuntimePlatform.WindowsEditor)
        {
            print("Unity Editor model");
            if (gameObject.GetComponent<PortBridgeCenter>() == null)
                this.gameObject.AddComponent<PortBridgeCenter>();
            print("add portbridgecenter");
            PortBridgeCenter.PortGloveEvent += USBmsgReciever;
            print("add glove reciever");
        }
    }

    private void PortGloveDataReciever(byte[] data)
    {
        //string str = System.Text.Encoding.ASCII.GetString(data);
        //USBmsgReciever(str);
    }
    public void USBmsgReciever(string msg)
    {
        text.text = msg;
        string[] data = msg.Split(Glove.Data.Contains.Connection.dataSplit_1);
        if (data.Length > 2)
        {
            foreach (DetectionBase detector in detectorList)
            {
                switch (detector.Tag)
                {
                    case Glove.Data.Contains.Connection.tagDealRotate:
                        Quaternion quatern = detector.DataDealment<Quaternion>(data[1]);
                        handRight.UpdateRotations(quatern);
                        break;
                    case Glove.Data.Contains.Connection.tagDealInflect:
                        int[] flexure = detector.DataDealment<int[]>(data[2]);
                        handRight.UpdateHandSphereCapsule(flexure);
                        break;
                    default:
                        Debug.Log(detector.Tag);
                        break;
                }
            }
        }
        //text.text = "x:" + gloveData[0] + "\n\ty:" + gloveData[1] + "\n\tz:" + gloveData[2];
        //Debug.Log("Recieve Message:" + msg);
    }

    void OnDisable()
    {
        PortBridgeCenter.PortGloveEvent -= USBmsgReciever;
    }
}
