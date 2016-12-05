using UnityEngine;
using System.Collections;

public abstract class DetectionBase {

    public abstract T DataDealment<T>(string data);

    [HideInInspector]
    public string Tag;
}
