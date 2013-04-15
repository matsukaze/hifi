//---------------------------------------------------------------------
//
// Created by Jeffrey Ventrella for High Fidelity.
// Copyright (c) 2013 High Fidelity, Inc. All rights reserved.
//
//---------------------------------------------------------------------

#include "Camera.h"
#include "Util.h"



//------------------------
Camera::Camera()
{
	mode			= CAMERA_MODE_THIRD_PERSON;
	tightness		= DEFAULT_CAMERA_TIGHTNESS;
	fieldOfView		= 60.0; // default
	yaw				= 0.0;
	pitch			= 0.0;
	roll			= 0.0;
	up				= 0.0;
	distance		= 0.0;
	targetPosition	= glm::vec3( 0.0, 0.0, 0.0 );
	position		= glm::vec3( 0.0, 0.0, 0.0 );
	idealPosition	= glm::vec3( 0.0, 0.0, 0.0 );
	orientation.setToIdentity();
}




//------------------------------------
void Camera::update( float deltaTime )
{
	double radian = ( yaw / 180.0 ) * PIE;

	//these need to be checked to make sure they correspond to the cordinate system.
	double x = distance * -sin( radian );
	double z = distance *  cos( radian );
	double y = up;
	
	idealPosition = targetPosition + glm::vec3( x, y, z );
	
	float t = tightness * deltaTime;
	
	if ( t > 1.0 ){
		t = 1.0;
	}
	
	position += ( idealPosition - position ) * t; 
	
	//-------------------------------------------------------------------------
	//geterate the ortho-normals for the orientation based on the Euler angles
	//-------------------------------------------------------------------------
	orientation.setToIdentity();
	orientation.yaw		( yaw	);
	orientation.pitch	( pitch	);
	orientation.roll	( roll	);
}
