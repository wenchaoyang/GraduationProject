using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine.UI;

public class CapsuleHand : MonoBehaviour {
    public enum FingerType
    {
        TYPE_THUMB = 0,
        TYPE_INDEX = 1,
        TYPE_MIDDLE = 2,
        TYPE_RING = 3,
        /** The pinky or little finger  */
        TYPE_PINKY = 4,
        TYPE_UNKNOWN = -1
    }

    private const int THUMB_BASE_INDEX = (int)FingerType.TYPE_THUMB * 4;
    private const int PINKY_BASE_INDEX = (int)FingerType.TYPE_PINKY * 4;

  private const float SPHERE_RADIUS = 0.008f;
  private const float CYLINDER_RADIUS = 0.006f;
  private const float PALM_RADIUS = 0.015f;


  [SerializeField]
  private Material _material;

  private Material jointMat;
  [SerializeField]
  public Transform[] _jointSpheres = new Transform[20];

    [SerializeField]
  private Transform mockThumbJointSphere;
    [SerializeField]
  public Transform palmPositionSphere;
    [SerializeField]
  private Transform wristPositionSphere;

  private List<Renderer> _armRenderers;
  private List<Transform> _capsuleTransforms;
  private List<Transform> _sphereATransforms;
  private List<Transform> _sphereBTransforms;

    private List<Vector3> targetSpherePosition;

    LeapGesturePool leapGesturePool;

    Quaternion targetQuaternion;

    public float speedRotate = 0.3f;
    public float speedFlex = 0.35f;
    [Range(0,5)]
    public int stateRange;

  //private Transform armFrontLeft, armFrontRight, armBackLeft, armBackRight;
  //private Hand hand_;

  void OnValidate() {
    //Update visibility on validate so that the user can toggle in real-time

  }

    void Start()
  {
      _armRenderers = new List<Renderer>();
      _capsuleTransforms = new List<Transform>();
      _sphereATransforms = new List<Transform>();
      _sphereBTransforms = new List<Transform>();
      targetSpherePosition = new List<Vector3>();
      leapGesturePool = new LeapGesturePool();
      ///////////////////////Save all sphare position as static ones//////////
      foreach (var sphere in _jointSpheres)
      {
          targetSpherePosition.Add(sphere.localPosition - palmPositionSphere.localPosition);
      }
      createCapsules();
      updateCapsules();
  }

    void Update()
    {
        gameObject.transform.rotation = Quaternion.Lerp(transform.rotation, targetQuaternion, speedRotate);
        updateSpheres(targetSpherePosition);
        updateCapsules();
    }

    void Update_no_use()
    {
        switch(stateRange)
        {
            case 0:
                updateSpheres(LeapGesturePool.stretchJoints);
                updateCapsules();
                break;
            case 1:
                updateSpheres(LeapGesturePool.fingerCloseStretchJoints);
                updateCapsules();
                break;
            case 2:
                updateSpheres(LeapGesturePool.flexureSmallJoints);
                updateCapsules();
                break;
            case 3:
                updateSpheres(LeapGesturePool.flexureMiddelJoints);
                updateCapsules();
                break;
            case 4:
                updateSpheres(LeapGesturePool.flexureLotsJoints);
                updateCapsules();
                break;
            case 5:
                updateSpheres(LeapGesturePool.closeJoints);
                updateCapsules();
                break;
            default: break;
        }
    }

    public void UpdateHandSphereCapsule(int[] flexureValue)
    {
        if (flexureValue == null || flexureValue.Length < 2) return;
        targetSpherePosition = leapGesturePool.CalcuGestureFinger(flexureValue);
        //updateSpheres(leapGesturePool.CalcuGestureFinger(flexureValue));
        //updateCapsules();

    }

    public void UpdateRotations(Quaternion quatern)
    {
        targetQuaternion = quatern;
    }
  private void updateSpheres(List<Vector3> handPosList) {
      if (handPosList.Count < 22) return; ;
     for(int i = 0; i<_jointSpheres.Length; i++)
     {
         _jointSpheres[i].localPosition = Vector3.Lerp(_jointSpheres[i].localPosition, palmPositionSphere.localPosition + handPosList[i], speedFlex);
     }
     mockThumbJointSphere.localPosition = Vector3.Lerp(mockThumbJointSphere.localPosition, palmPositionSphere.localPosition + handPosList[20], speedFlex);
     wristPositionSphere.localPosition = Vector3.Lerp(wristPositionSphere.localPosition, palmPositionSphere.localPosition + handPosList[21], speedFlex);
  }


  private void updateCapsules() {
    for (int i = 0; i < _capsuleTransforms.Count; i++) {
      Transform capsule = _capsuleTransforms[i];
      Transform sphereA = _sphereATransforms[i];
      Transform sphereB = _sphereBTransforms[i];

      Vector3 delta = sphereA.position - sphereB.position;

      Vector3 scale = capsule.localScale;
      scale.x = CYLINDER_RADIUS * 2;
      scale.y = delta.magnitude * 0.5f / transform.lossyScale.x;
      scale.z = CYLINDER_RADIUS * 2;

      capsule.localScale = scale;

      capsule.position = (sphereA.position + sphereB.position) / 2;

      if (delta.sqrMagnitude <= Mathf.Epsilon) {
        //Two spheres are at the same location, no rotation will be found
        continue;
      }

      Vector3 perp;
      if (Vector3.Angle(delta, Vector3.up) > 170 || Vector3.Angle(delta, Vector3.up) < 10) {
        perp = Vector3.Cross(delta, Vector3.right);
      }
      else {
        perp = Vector3.Cross(delta, Vector3.up);
      }

      capsule.rotation = Quaternion.LookRotation(perp, delta);
    }
  }

  private void createCapsules() {
    //Create capsules between finger joints
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 3; j++) {
        int keyA = getFingerJointIndex(i, j);
        int keyB = getFingerJointIndex(i, j + 1);

        Transform sphereA = _jointSpheres[keyA];
        Transform sphereB = _jointSpheres[keyB];

        createCapsule("Finger Joint", sphereA, sphereB);
      }
    }

    //Create capsule between finger knuckles
    for (int i = 0; i < 4; i++) {
      int keyA = getFingerJointIndex(i, 0);
      int keyB = getFingerJointIndex(i + 1, 0);

      Transform sphereA = _jointSpheres[keyA];
      Transform sphereB = _jointSpheres[keyB];

      createCapsule("Hand Joints", sphereA, sphereB);
    }

    //Create the rest of the hand
    Transform thumbBase = _jointSpheres[THUMB_BASE_INDEX];
    Transform pinkyBase = _jointSpheres[PINKY_BASE_INDEX];
    createCapsule("Hand Bottom", thumbBase, mockThumbJointSphere);
    createCapsule("Hand Side", pinkyBase, mockThumbJointSphere);
  }

  private int getFingerJointIndex(int fingerIndex, int jointIndex) {
    return fingerIndex * 4 + jointIndex;
  }


  private void createCapsule(string name, Transform jointA, Transform jointB, bool isPartOfArm = false) {
    GameObject capsule = GameObject.CreatePrimitive(PrimitiveType.Cylinder);
    DestroyImmediate(capsule.GetComponent<Collider>());
    capsule.name = name;
    capsule.transform.parent = transform;
    capsule.transform.localScale = Vector3.one * CYLINDER_RADIUS * 2;
    capsule.GetComponent<Renderer>().sharedMaterial = _material;

    _capsuleTransforms.Add(capsule.transform);
    _sphereATransforms.Add(jointA);
    _sphereBTransforms.Add(jointB);

    capsule.hideFlags = HideFlags.DontSave | HideFlags.HideInHierarchy | HideFlags.HideInInspector;

    if (isPartOfArm) {
      _armRenderers.Add(capsule.GetComponent<Renderer>());
    }
  }
}
