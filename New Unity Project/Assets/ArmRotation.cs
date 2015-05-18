using UnityEngine;
using System.Collections;

public class ArmRotation : MonoBehaviour {

	private float rotationOffset = 90;
	
	// Update is called once per frame
	void Update () {
	
		Vector3 difference = Camera.main.ScreenToWorldPoint (Input.mousePosition)
			- transform.position;

		difference.Normalize ();

		float rotZ = Mathf.Atan2 (difference.y, difference.x) * Mathf.Rad2Deg;

		if (this.transform.parent.localScale.x > 0) {
			transform.rotation = Quaternion.Euler (0f, 0f, rotZ + rotationOffset);
		} else {
			transform.rotation = (Quaternion.Euler (0f, 0f,(-1)*(rotZ + rotationOffset)));
		}
	}
}
