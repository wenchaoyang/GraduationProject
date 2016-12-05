
function Update () {
	this.transform.Translate(Vector3.forward*Time.deltaTime*10);
	if(transform.position.z > 350)
	{
		Destroy(this.gameObject);
	}
}