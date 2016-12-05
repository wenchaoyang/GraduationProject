using UnityEngine;
using System.Collections;

public class WebCamPosition : MonoBehaviour {
    public Camera mainCam;
    WebCamTexture cameraTexture;
    private bool isPlay = false;
    Color32[] camColorPixels;
    private int camWidth = 640;
    private int camHeight = 480;

    Vector3 initPosition = new Vector3();
    Vector3 handPosition = new Vector3();
    public Vector3 GetHandPosition
    {
        get { return handPosition; }
    }

    private static WebCamPosition instance;
    public static WebCamPosition GetInstance
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
    void Start()
    {
        StartCoroutine(CameraImageShow());
        camColorPixels = new Color32[camWidth * camHeight];
    }

    // Update is called once per frame
    void Update()
    {

    }

    IEnumerator CameraImageShow()
    {
        yield return Application.RequestUserAuthorization(UserAuthorization.WebCam);
        if (Application.HasUserAuthorization(UserAuthorization.WebCam))
        {
            WebCamDevice[] devices = WebCamTexture.devices;
            string cameraName = devices[0].name;
            cameraTexture = new WebCamTexture(cameraName, camWidth, camHeight, 15);
            cameraTexture.Play();
            isPlay = true;
        }
    }
    void OnGUI()
    {
        if (isPlay)
        {
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
                    }
                }
            }
            if (dotAmount > 300 && dotAmount < 5000)
            {
                posx /= dotAmount;
                posy /= dotAmount;
                handPosition = mainCam.ViewportToWorldPoint(new Vector3(1.0f * posx / camWidth, 1.0f * posy / camHeight, (4200 - dotAmount) / 2000.0f));
                transform.position = handPosition;
            }
            //////////////////////////////////////////////////////////end of the work to calculate the position of hand//////////////////////////
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
        if (IsPixelLight(index + camWidth)) mum++;
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
        for (int i = 0; i < camHeight; i++)
        {
            for (int j = 0; j < camWidth; j++)
            {
                int index = i * camWidth + j;
                if (camColorPixels[index].r < 100)
                {
                    //camColorPixels[index] = new Color32(0, 0, 0, 255);
                }
            }
        }
        isPlay = true;
    }
}
