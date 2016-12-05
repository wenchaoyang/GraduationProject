using UnityEngine;
using System.Collections;
namespace Glove.Data
{
    public static class Contains
    {
        public static class Connection
        {
            public static char[] dataSplit_1 = new char[] { '#' };
            public static char[] dataSplit_2 = new char[] { ':' };

            public const string tagDealRotate = "Rotation";
            public const string tagDealInflect = "Inflection";

            public const string androidIdentifer = "com.won.usb_ch340.USBOTGCenter";
            public const string funSendtoAndroid = "SendMessagebyUsb";
        }
    }
}
