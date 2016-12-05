using UnityEngine;
using System.Collections;
using System.Threading;
using UnityEngine.UI;

public class WebCamera : MonoBehaviour {
    WebCamTexture cameraTexture;
    string cameraName = "";
    private bool isPlay = false;
    Color32[] camColorPixels;
    Color32[] camFilterColorPixels;
    Texture2D filterCamTexture;
    public Text debugg;
    private int camWidth = 640;
    private int camHeight = 480;

    Vector3 initPosition = new Vector3();
    Vector3 handPosition = new Vector3();
    public Vector3 GetHandPosition
    {
        get { return handPosition; }
    }

    private static WebCamera instance;
    public static WebCamera GetInstance
    {
        get
        {
            if (instance = null) Debug.LogError("there is no webcamera been found");
            return instance;
        }
    }

    void Awake()
    {
        instance = this;
        handPosition = gameObject.transform.position;
        initPosition = gameObject.transform.position;
    }
	// Use this for initialization
	void Start () {
        StartCoroutine(CameraImageShow());
        camColorPixels = new Color32[camWidth * camHeight];
        camFilterColorPixels = new Color32[camWidth * camHeight];
        filterCamTexture = new Texture2D(camWidth, camHeight, TextureFormat.RGBA32, false);
    }
	
	// Update is called once per frame
	void Update () {
	
	}

    IEnumerator CameraImageShow()
    {
        yield return Application.RequestUserAuthorization(UserAuthorization.WebCam);
        if (Application.HasUserAuthorization(UserAuthorization.WebCam))
        {
            WebCamDevice[] devices = WebCamTexture.devices;
            cameraName = devices[0].name;
            cameraTexture = new WebCamTexture(cameraName, camWidth, camHeight, 15);
            cameraTexture.Play();
            isPlay = true;
        }  
    }
    void OnGUI()
    {
        if (isPlay)
        {
            GUI.DrawTexture(new Rect(0, 0, camWidth * 0.5f, camHeight * 0.5f), cameraTexture, ScaleMode.ScaleToFit);
            camColorPixels = cameraTexture.GetPixels32();
            //Thread filterThread = new Thread(new ThreadStart(FilterTexture));
            //filterThread.IsBackground = true;
            //filterThread.Start();
            //////////////////////////////////////////////the region to deal image and find the position of sphere////////////////////////////
            int posx = 0;
            int posy = 0;
            int dotAmount = 0;
            for (int i = 1; i < camHeight - 1; i++)
            {
                for (int j = 1; j < camWidth - 1; j++)
                {
                    int index = i * camWidth + j;
                    if (camColorPixels[index].r > 254 && camColorPixels[index].g > 254 && camColorPixels[index].b > 254 && IsColorSphere(index))
                    {
                        dotAmount++;
                        posx += j;
                        posy += i;
                        camFilterColorPixels[index] = new Color32(255, 0, 0, 255);
                    }
                    else
                    {
                        camFilterColorPixels[index] = new Color32(0, 0, 0, 255);
                    }
                    //if(i == camHeight * 0.5f && j == camWidth * 0.5f)
                    //{
                    //    float y = 0.299f * float.Parse(camColorPixels[index].r.ToString()) + 0.587f * float.Parse(camColorPixels[index].g.ToString()) + 0.114f * float.Parse(camColorPixels[index].b.ToString());
                    //    debugg.text = camColorPixels[index].ToString() + "y:" + y;
                    //    camColorPixels[index] = new Color32(0, 255, 0, 255);
                    //    camColorPixels[index + 1] = new Color32(0, 255, 0, 255);
                    //    camColorPixels[index - 1] = new Color32(0, 255, 0, 255);
                    //    camColorPixels[index + camWidth] = new Color32(0, 255, 0, 255);
                    //    camColorPixels[index - camWidth] = new Color32(0, 255, 0, 255);
                    //}
                }
            }
            if(dotAmount > 300 && dotAmount < 4800)
            {
                posx /= dotAmount;
                posy /= dotAmount;
                handPosition = Camera.main.ViewportToWorldPoint(new Vector3(1.0f * posx / camWidth, 1.0f *  posy / camHeight, (4000 - dotAmount) / 600.0f));
                debugg.text = handPosition.ToString();
                transform.position = Vector3.Lerp(transform.position, handPosition, 0.3f);
            }
            //////////////////////////////////////////////////////////end of the work to calculate the position of hand//////////////////////////
            filterCamTexture.SetPixels32(camFilterColorPixels);
            filterCamTexture.Apply();
            GUI.DrawTexture(new Rect(camWidth * 0.5f, 0, camWidth * 0.5f, camHeight * 0.5f), filterCamTexture, ScaleMode.ScaleToFit);
        }
    }

    private bool IsColorSphere(int index)
    {
        int mum = 0;
        if (IsPixelLight(index - camWidth - 1)) mum++;
        if (IsPixelLight(index - camWidth)) mum++;
        if (IsPixelLight(index - camWidth + 1)) mum++;
        if (IsPixelLight(index - 1)) mum++;
        if (IsPixelLight(index + 1)) mum++;
        if (IsPixelLight(index + camWidth - 1)) mum++;
        if (IsPixelLight(index + camWidth )) mum++;
        if (IsPixelLight(index + camWidth + 1)) mum++;
        if (mum > 4) return true;
        return false;
    }
    private bool IsPixelLight(int index)
    {
        return camColorPixels[index].r > 254 && camColorPixels[index].g > 254 && camColorPixels[index].b > 254;
    }

    private void FilterTexture()
    {
        isPlay = false;
        for(int i = 0; i< camHeight; i++)
        {
            for(int j = 0; j < camWidth; j++)
            {
                int index = i * camWidth + j;
                if(camColorPixels[index].r < 100)
                {
                    //camColorPixels[index] = new Color32(0, 0, 0, 255);
                }
            }
        }
        filterCamTexture.SetPixels32(camColorPixels);
        filterCamTexture.Apply();
        isPlay = true;
    }
}
