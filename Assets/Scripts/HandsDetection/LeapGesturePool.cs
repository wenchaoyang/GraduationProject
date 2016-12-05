using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System;

public class LeapGesturePool {

    public static List<Vector3> stretchJoints;
    public static List<Vector3> fingerCloseStretchJoints;
    public static List<Vector3> flexureSmallJoints;
    public static List<Vector3> flexureMiddelJoints;
    public static List<Vector3> flexureLotsJoints;
    public static List<Vector3> closeJoints;
    int maxValueofFlex = 3000;
    struct GestureTemplate
    {
        public int thumbFingerFlex;
        public int indexFingerFlex;
        public int middleFingerFlex;
        public List<Vector3> positionJoints;
    }
    List<GestureTemplate> gestureTemplateList;
    public LeapGesturePool()
    {
        /*
        #region 记录模板姿势,硬写入
        stretchJoints = new List<Vector3>();
        stretchJoints.Add(new Vector3(0.02026441f, 0.009853702f, 0.05235317f));
        stretchJoints.Add(new Vector3(0.04968263f, 0.002076756f, 0.0174514f));
        stretchJoints.Add(new Vector3(0.06667043f, -0.006502627f, -0.007808976f));
        stretchJoints.Add(new Vector3(0.08073592f, -0.009829441f, -0.02400735f));
        stretchJoints.Add(new Vector3(0.02227664f, 0.001508927f, -0.02413809f));
        stretchJoints.Add(new Vector3(0.0256903f, -0.004243324f, -0.06342483f));
        stretchJoints.Add(new Vector3(0.02822015f, -0.01045039f, -0.08482002f));
        stretchJoints.Add(new Vector3(0.03040906f, -0.01687673f, -0.09914099f));
        stretchJoints.Add(new Vector3(0.001874678f, -0.000721243f, -0.02371605f));
        stretchJoints.Add(new Vector3(-0.008114851f, -0.005936888f, -0.06698344f));
        stretchJoints.Add(new Vector3(-0.01318531f, -0.01160943f, -0.09224008f));
        stretchJoints.Add(new Vector3(-0.01590663f, -0.01716942f, -0.1085354f));
        stretchJoints.Add(new Vector3(-0.0179515f, -0.003497131f, -0.01693333f));
        stretchJoints.Add(new Vector3(-0.03121284f, -0.0076658f, -0.05597747f));
        stretchJoints.Add(new Vector3(-0.03869896f, -0.01231067f, -0.08011644f));
        stretchJoints.Add(new Vector3(-0.04303079f, -0.01725724f, -0.09615211f));
        stretchJoints.Add(new Vector3(-0.034647f, -0.009277651f, -0.007859287f));
        stretchJoints.Add(new Vector3(-0.05507115f, -0.01568672f, -0.03271031f));
        stretchJoints.Add(new Vector3(-0.06553667f, -0.021172f, -0.04647799f));
        stretchJoints.Add(new Vector3(-0.0737558f, -0.02790149f, -0.05842809f));
        stretchJoints.Add(new Vector3(-0.01764297f, 0.002039369f, 0.05415876f));
        stretchJoints.Add(new Vector3(0f, 0f, 0f));

        fingerCloseStretchJoints = new List<Vector3>();
        fingerCloseStretchJoints.Add(new Vector3(0.01524736f, 0.007273683f, 0.05444439f));
        fingerCloseStretchJoints.Add(new Vector3(0.04581453f, -0.001256236f, 0.02071626f));
        fingerCloseStretchJoints.Add(new Vector3(0.05491804f, -0.01605386f, -0.005717414f));
        fingerCloseStretchJoints.Add(new Vector3(0.05523251f, -0.02894626f, -0.02318515f));
        fingerCloseStretchJoints.Add(new Vector3(0.02466297f, 0.001213463f, -0.02171998f));
        fingerCloseStretchJoints.Add(new Vector3(0.0188317f, -0.007438543f, -0.06018828f));
        fingerCloseStretchJoints.Add(new Vector3(0.01578518f, -0.01474928f, -0.08116697f));
        fingerCloseStretchJoints.Add(new Vector3(0.01369329f, -0.02048153f, -0.09579644f));
        fingerCloseStretchJoints.Add(new Vector3(0.004243367f, -7.396424E-05f, -0.02342313f));
        fingerCloseStretchJoints.Add(new Vector3(0.001554697f, -0.01049415f, -0.06682657f));
        fingerCloseStretchJoints.Add(new Vector3(0.0005878991f, -0.01880769f, -0.09184548f));
        fingerCloseStretchJoints.Add(new Vector3(0.0001415652f, -0.02495468f, -0.1081539f));
        fingerCloseStretchJoints.Add(new Vector3(-0.01627399f, -0.002130022f, -0.01876239f));
        fingerCloseStretchJoints.Add(new Vector3(-0.01630071f, -0.01037549f, -0.05938525f));
        fingerCloseStretchJoints.Add(new Vector3(-0.01602344f, -0.01626857f, -0.08439934f));
        fingerCloseStretchJoints.Add(new Vector3(-0.01564699f, -0.02074333f, -0.1011416f));
        fingerCloseStretchJoints.Add(new Vector3(-0.0340431f, -0.007403549f, -0.011616f));
        fingerCloseStretchJoints.Add(new Vector3(-0.03491477f, -0.01244209f, -0.04401932f));
        fingerCloseStretchJoints.Add(new Vector3(-0.03506427f, -0.01582715f, -0.06184572f));
        fingerCloseStretchJoints.Add(new Vector3(-0.03491526f, -0.01931151f, -0.07745214f));
        fingerCloseStretchJoints.Add(new Vector3(-0.02295565f, 0.001184575f, 0.05216536f));
        fingerCloseStretchJoints.Add(new Vector3(0f, 0f, 0f));

        flexureSmallJoints = new List<Vector3>();
        flexureSmallJoints.Add(new Vector3(0.01122429f, 0.01181756f, 0.05462549f));
        flexureSmallJoints.Add(new Vector3(0.04284716f, -0.01216107f, 0.03075685f));
        flexureSmallJoints.Add(new Vector3(0.05203127f, -0.03580736f, 0.01186003f));
        flexureSmallJoints.Add(new Vector3(0.05083272f, -0.0535432f, -0.0006075045f));
        flexureSmallJoints.Add(new Vector3(0.02617883f, -0.0003737016f, -0.01990056f));
        flexureSmallJoints.Add(new Vector3(0.03378127f, -0.009984332f, -0.05782824f));
        flexureSmallJoints.Add(new Vector3(0.03869029f, -0.02274772f, -0.07559985f));
        flexureSmallJoints.Add(new Vector3(0.04215546f, -0.03559825f, -0.08420877f));
        flexureSmallJoints.Add(new Vector3(0.005940187f, -0.001954964f, -0.02296846f));
        flexureSmallJoints.Add(new Vector3(0.002194374f, -0.009412915f, -0.06690042f));
        flexureSmallJoints.Add(new Vector3(0.00203247f, -0.02166093f, -0.09026609f));
        flexureSmallJoints.Add(new Vector3(0.003236233f, -0.03394676f, -0.1025771f));
        flexureSmallJoints.Add(new Vector3(-0.01485898f, -0.003783028f, -0.01965474f));
        flexureSmallJoints.Add(new Vector3(-0.02057985f, -0.0108161f, -0.06010241f));
        flexureSmallJoints.Add(new Vector3(-0.02156835f, -0.02271568f, -0.08286051f));
        flexureSmallJoints.Add(new Vector3(-0.02041084f, -0.0350511f, -0.09498341f));
        flexureSmallJoints.Add(new Vector3(-0.03309204f, -0.008593044f, -0.01340696f));
        flexureSmallJoints.Add(new Vector3(-0.04792861f, -0.01736671f, -0.04131787f));
        flexureSmallJoints.Add(new Vector3(-0.05323034f, -0.02795811f, -0.05506471f));
        flexureSmallJoints.Add(new Vector3(-0.05493004f, -0.04089994f, -0.06430283f));
        flexureSmallJoints.Add(new Vector3(-0.02669977f, 0.005265205f, 0.05008976f));
        flexureSmallJoints.Add(new Vector3(0f, 0f, 0f));

        flexureMiddelJoints = new List<Vector3>();
        flexureMiddelJoints.Add(new Vector3(0.009887954f, 0.0002622406f, 0.05615352f));
        flexureMiddelJoints.Add(new Vector3(0.04450585f, -0.001840801f, 0.02544798f));
        flexureMiddelJoints.Add(new Vector3(0.05332184f, -0.0146061f, -0.002126814f));
        flexureMiddelJoints.Add(new Vector3(0.04967831f, -0.02713345f, -0.01948881f));
        flexureMiddelJoints.Add(new Vector3(0.02642322f, 0.005199256f, -0.01888845f));
        flexureMiddelJoints.Add(new Vector3(0.03397582f, -0.009890931f, -0.0550082f));
        flexureMiddelJoints.Add(new Vector3(0.03801224f, -0.03153454f, -0.05928876f));
        flexureMiddelJoints.Add(new Vector3(0.0388312f, -0.04468363f, -0.05046828f));
        flexureMiddelJoints.Add(new Vector3(0.006331438f, 0.003343679f, -0.02270786f));
        flexureMiddelJoints.Add(new Vector3(0.01035211f, -0.01068168f, -0.06498908f));
        flexureMiddelJoints.Add(new Vector3(0.01763626f, -0.0347039f, -0.0731243f));
        flexureMiddelJoints.Add(new Vector3(0.02218122f, -0.04942341f, -0.06495304f));
        flexureMiddelJoints.Add(new Vector3(-0.01438953f, -0.0001588059f, -0.02036201f));
        flexureMiddelJoints.Add(new Vector3(-0.013876f, -0.01256123f, -0.05992088f));
        flexureMiddelJoints.Add(new Vector3(-0.006880569f, -0.03465154f, -0.07105148f));
        flexureMiddelJoints.Add(new Vector3(-0.0006981408f, -0.04997798f, -0.06580918f));
        flexureMiddelJoints.Add(new Vector3(-0.03242947f, -0.00708029f, -0.01573144f));
        flexureMiddelJoints.Add(new Vector3(-0.0416408f, -0.01803701f, -0.04525629f));
        flexureMiddelJoints.Add(new Vector3(-0.03800755f, -0.03363334f, -0.05379833f));
        flexureMiddelJoints.Add(new Vector3(-0.02989441f, -0.04719292f, -0.0513173f));
        flexureMiddelJoints.Add(new Vector3(-0.02758908f, -0.006977956f, 0.04940871f));
        flexureMiddelJoints.Add(new Vector3(0f, 0f, 0f));

        flexureLotsJoints = new List<Vector3>();
        flexureLotsJoints.Add(new Vector3(0.01496365f, 0.001677276f, 0.05499406f));
        flexureLotsJoints.Add(new Vector3(0.04562571f, 0.002922853f, 0.02029612f));
        flexureLotsJoints.Add(new Vector3(0.0499909f, -0.01041321f, -0.008061175f));
        flexureLotsJoints.Add(new Vector3(0.04060911f, -0.02467058f, -0.02149089f));
        flexureLotsJoints.Add(new Vector3(0.02394987f, 0.007519909f, -0.02125689f));
        flexureLotsJoints.Add(new Vector3(0.03036188f, -0.01852705f, -0.05074988f));
        flexureLotsJoints.Add(new Vector3(0.03533575f, -0.03880844f, -0.04256505f));
        flexureLotsJoints.Add(new Vector3(0.03663728f, -0.04414784f, -0.02769333f));
        flexureLotsJoints.Add(new Vector3(0.003859283f, 0.003735247f, -0.02319632f));
        flexureLotsJoints.Add(new Vector3(0.01547477f, -0.02359524f, -0.05664341f));
        flexureLotsJoints.Add(new Vector3(0.02537271f, -0.04595792f, -0.04673104f));
        flexureLotsJoints.Add(new Vector3(0.02825376f, -0.05214952f, -0.03068568f));
        flexureLotsJoints.Add(new Vector3(-0.01612831f, -0.001695979f, -0.0189392f));
        flexureLotsJoints.Add(new Vector3(-0.01046804f, -0.02241177f, -0.0544048f));
        flexureLotsJoints.Add(new Vector3(0.00108905f, -0.04537353f, -0.0543524f));
        flexureLotsJoints.Add(new Vector3(0.007821753f, -0.05544988f, -0.04195314f));
        flexureLotsJoints.Add(new Vector3(-0.03292228f, -0.01025706f, -0.01265699f));
        flexureLotsJoints.Add(new Vector3(-0.03713373f, -0.02383698f, -0.04222831f));
        flexureLotsJoints.Add(new Vector3(-0.02900152f, -0.03917839f, -0.04751245f));
        flexureLotsJoints.Add(new Vector3(-0.01881414f, -0.0496689f, -0.0410313f));
        flexureLotsJoints.Add(new Vector3(-0.02211618f, -0.009140958f, 0.05175317f));
        flexureLotsJoints.Add(new Vector3(0f, 0f, 0f));

        closeJoints = new List<Vector3>();
        closeJoints.Add(new Vector3(0.01044896f, 0.01312584f, 0.05449431f));
        closeJoints.Add(new Vector3(0.0326531f, -0.009415894f, 0.02066328f));
        closeJoints.Add(new Vector3(0.03037451f, -0.03233951f, -0.001024619f));
        closeJoints.Add(new Vector3(0.01654431f, -0.04719196f, -0.008756844f));
        closeJoints.Add(new Vector3(0.02647495f, -0.0009168054f, -0.01949983f));
        closeJoints.Add(new Vector3(0.03327248f, -0.04019061f, -0.01862123f));
        closeJoints.Add(new Vector3(0.03079245f, -0.04882275f, 0.001931237f));
        closeJoints.Add(new Vector3(0.02729724f, -0.04581284f, 0.01710024f));
        closeJoints.Add(new Vector3(0.006274927f, -0.002528643f, -0.02282872f));
        closeJoints.Add(new Vector3(0.0194461f, -0.04514145f, -0.02618609f));
        closeJoints.Add(new Vector3(0.02175066f, -0.05662422f, -0.002539649f));
        closeJoints.Add(new Vector3(0.02027509f, -0.05465635f, 0.01472426f));
        closeJoints.Add(new Vector3(-0.01458003f, -0.004230177f, -0.01977942f));
        closeJoints.Add(new Vector3(-0.00540332f, -0.03941058f, -0.0397076f));
        closeJoints.Add(new Vector3(0.002392957f, -0.0597863f, -0.02611103f));
        closeJoints.Add(new Vector3(0.005764915f, -0.06543282f, -0.0100688f));
        closeJoints.Add(new Vector3(-0.03291991f, -0.008847455f, -0.0136858f));
        closeJoints.Add(new Vector3(-0.03203873f, -0.03145014f, -0.0374548f));
        closeJoints.Add(new Vector3(-0.02485256f, -0.04808766f, -0.03647115f));
        closeJoints.Add(new Vector3(-0.01723486f, -0.05827553f, -0.02677471f));
        closeJoints.Add(new Vector3(-0.02742933f, 0.006546121f, 0.04955681f));
        closeJoints.Add(new Vector3(0f, 0f, 0f));
        #endregion
         * */
        gestureTemplateList = new List<GestureTemplate>();
        //LoadFile("train_data.txt");
        ResourceLoadFile("train_data");
    }
    public List<Vector3> CalcuGestureFinger(int[] inputFingers)
    {
        float similarity = 0;
        float simitemp;
        List<Vector3> backData = new List<Vector3>();
        foreach(var tempPoll in gestureTemplateList)
        {
            simitemp = 1 - 0.5f * Mathf.Abs(inputFingers[0] - tempPoll.thumbFingerFlex) / maxValueofFlex 
                         - 0.5f * Mathf.Abs(inputFingers[1] - tempPoll.indexFingerFlex) / maxValueofFlex;
            if(simitemp > similarity)
            {
                similarity = simitemp;
                backData = tempPoll.positionJoints;
            }
        }
        return backData;
    }
    void StoreAgestureTemplate(string templateData)
    {
        if(templateData.Length < 10 || templateData[0] != '{')
        {
            Debug.Log("wrong data format");
        }
        string[] stepOneStrs = templateData.Split(new char[] { '#','{','}' });
        if(stepOneStrs.Length > 2)
        {
            string[] flexs = stepOneStrs[1].Split(new char[] { ':' });
            GestureTemplate oneTemplate = new GestureTemplate();
            oneTemplate.thumbFingerFlex = int.Parse(flexs[0]);
            oneTemplate.indexFingerFlex = int.Parse(flexs[1]);
            oneTemplate.positionJoints = new List<Vector3>();

            stepOneStrs[2] = stepOneStrs[2].Replace("[","");
            stepOneStrs[2] = stepOneStrs[2].Replace("]","");
            stepOneStrs[2] = stepOneStrs[2].Replace(" ","");
            string[] vects = stepOneStrs[2].Split(new char[] { '[', ']',':' });
            foreach(string data in vects)
            {
                string[] fdata = data.Split(new char[] {','});
                Vector3 vv = new Vector3(float.Parse(fdata[0]), float.Parse(fdata[1]), float.Parse(fdata[2]));
                oneTemplate.positionJoints.Add(vv);
            }
            if(oneTemplate.positionJoints.Count > 21)
                gestureTemplateList.Add(oneTemplate);
        }
    }
    /////////////////////////////////////文件读写过程全在这里////////////////////////////////////////
    void CreateFile(string name, string info)
    {
        string path = Application.persistentDataPath;
        //文件流信息
        StreamWriter sw;
        FileInfo t = new FileInfo(path + "//" + name);
        if (!t.Exists)
        {
            //如果此文件不存在则创建
            sw = t.CreateText();
        }
        else
        {
            //如果此文件存在则打开
            sw = t.AppendText();
        }
        //以行的形式写入信息
        sw.WriteLine(info);
        //关闭流
        sw.Close();
        //销毁流
        sw.Dispose();
    }
    ArrayList LoadFile(string name)
    {
        string path = Application.persistentDataPath;
        Debug.Log(path);
        //使用流的形式读取
        StreamReader sr = null;
        try
        {
            sr = File.OpenText(path + "//" + name);
        }
        catch (Exception e)
        {
            //路径与名称未找到文件则直接返回空
            return null;
        }
        string line;
        ArrayList arrlist = new ArrayList();
        while ((line = sr.ReadLine()) != null)
        {
            //一行一行的读取
            //将每一行的内容存入数组链表容器中
            StoreAgestureTemplate(line);
            //arrlist.Add(line);
        }
        //关闭流
        sr.Close();
        //销毁流
        sr.Dispose();
        //将数组链表容器返回
        return arrlist;
    }
    void ResourceLoadFile(string filename)
    {
        TextAsset txtAsset = Resources.Load(filename) as TextAsset;
        string pool = txtAsset.text;
        string[] lines = pool.Split(new char[] { '\n' });
        foreach(string lin in lines)
        {
            StoreAgestureTemplate(lin);
        }
    }
}
