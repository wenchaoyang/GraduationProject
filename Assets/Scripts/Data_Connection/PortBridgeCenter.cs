using UnityEngine;
using System.Collections;
using System.Threading;
using System;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Collections.Generic;
//using UnityEditor;


public class PortBridgeCenter : MonoBehaviour {

    //Port base information and setups 
    public string portName = "COM7";
    SerialPort port;
    char[] data = new char[4096];
    //定义一个上次串口数据，每次比较有不同的数据时才通知数据更新。
    string lastData = "";
    List<int> buffer = new List<int>();

    public delegate void PortGlove(string bs);
    public static event PortGlove PortGloveEvent;

    void Start()
    {
        port = new SerialPort(portName, 9600);
        port.ReadBufferSize = 1024;//默认值为4096
        port.NewLine = "\r\n";
        port.ReadTimeout = 2;//Unity在Windows平台下不能通过新线程与串口通信，这样会导致数据丢失，必须在主线程中进行
        //port.DataReceived += PortDataReceived;//Unity不支持DataReceived事件，参考：http://www.cnblogs.com/zhaozhengling/p/3696251.html
        //port.ReceivedBytesThreshold = 1;//理由同上
        if (port == null)
        {
            Application.Quit();
            //EditorApplication.isPlaying = false;
            return;
        }
        else
        {
            port.Open();
        }
    }

    void FixedUpdate()
    {
        if (buffer.Count > 0)
        {
            int i = 0;
            for (; i < buffer.Count; i++)
            {
                if ((char)buffer[i] == 'D')
                {
                    for (int j = 0; i < buffer.Count - 1; i++, j++)
                    {
                        data[j] = (char)buffer[i];//将数据存入data中
                        if (buffer[j] == 10 || buffer[j] == 13 || buffer[i] == '\n' || buffer[i] == '\r' || buffer[i] == '\0')
                        {
                            data[j] = ('\0');
                            print(new string(data));
                            break;
                        }
                    }
                    string thisData = new string(data);
                    if (!thisData.Equals(lastData))
                    {
                        if (PortGloveEvent != null) PortGloveEvent(thisData);
                        lastData = thisData;
                    }
                    break;
                }
            }
            buffer.RemoveRange(0, buffer.Count);
        }

        if (port != null && port.IsOpen)
        {
            try
            {
                for (int i = 0; i < port.ReadBufferSize; i++)
                {
                    buffer.Add(port.ReadByte());//port.ReadByte()：当串口缓冲区无数据可读时将触发"读取超时"异常
                }
            }
            catch (TimeoutException)
            {
                //UnityEngine.Debug.Log("读取超时");
            }
        }
    }
}
