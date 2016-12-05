using UnityEngine;
using System.Collections;
using System;

public class DetectionRotate : DetectionBase {
    Vector3 gloveData = Vector3.zero;
	// Use this for initialization
    public DetectionRotate()
    {
        Tag = Glove.Data.Contains.Connection.tagDealRotate;
	}
	
	// Update is called once per frame
	void Update () {
	
	}
    public override T DataDealment<T>(string data)
    {
        string[] rotateData = data.Split(Glove.Data.Contains.Connection.dataSplit_2);
        //if (rotateData.Length != 3) return default(T);
        try
        {
            //1/-2/0
            float[] dataTemp = new float[] { float.Parse(rotateData[1]) / 10, -float.Parse(rotateData[2]) / 10 , float.Parse(rotateData[0]) / 10};
            Debug.Log(dataTemp[0].ToString() + " " + dataTemp[1] + " " + dataTemp[2]);
            for (int i = 0; i < dataTemp.Length; i++)
            {
                gloveData[i] = dataTemp[i];
                //to ensure the data of hand at -88~88
                if (dataTemp[i] > 175) dataTemp[i] = 175;
                if (dataTemp[i] < -175) dataTemp[i] = -175;
            }
            gloveData.x += 180;
            //gloveData.y += 180;
            gloveData.z += 180;
        }
        catch(Exception e)
        {
            Debug.Log(data);
        }
        Quaternion quaternion = Quaternion.Euler(gloveData);
        Debug.Log(quaternion.ToString());
        return (T)(object)quaternion;
    }
}
