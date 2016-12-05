using UnityEngine;
using System.Collections;
using System;

public class DetectionInflect : DetectionBase {

	// Use this for initialization
    public DetectionInflect()
    {
        Tag = Glove.Data.Contains.Connection.tagDealInflect;
	}
	
	// Update is called once per frame
	void Update () {
	
	}
    public override T DataDealment<T>(string data)
    {
        string[] inflectData = data.Split(Glove.Data.Contains.Connection.dataSplit_2);
        try
        {
            if (2 == inflectData.Length)
            {
                int[] fingers = new int[] { int.Parse(inflectData[0]), int.Parse(inflectData[1]) };
                //Debug.Log("finger1:" + fingers[0] + " finger2:" + fingers[1]);
                return (T)(object)fingers;
            }
        }
        catch(Exception e)
        {
            Debug.Log(data);
        }
        return default(T);
    }
}
