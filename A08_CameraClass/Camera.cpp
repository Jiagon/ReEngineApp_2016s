#include "Camera.h"

Camera::Camera() {
	Camera(vector3(0.0f, 0.0f, 1.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);
}

Camera::Camera(vector3 target, vector3 position, vector3 up)
{
	// Sets target, position, and up according to parameter values
	m_v3Target = target;
	m_v3Position = position;
	m_v3Up = up;

	// Creates default front and back clipping planes relative to the
		// camera's and target's positions, respectively
	m_cpFront.v3BottomLeft = vector3(position.x - 10.80f, position.y - 7.68f, position.z - 5.0f);
	m_cpFront.v3TopRight = vector3(position.x + 10.80f, position.y + 7.68f, position.z - 5.0f);

	m_cpBack.v3BottomLeft = vector3(position.x - 10.80f, position.y - 7.68f, target.z - 5.0f);
	m_cpBack.v3TopRight = vector3(position.x + 10.80f, position.y + 7.68f, target.z - 5.0f);

	// Sets default fov to orthographic, not perspective
	m_bOrthographic = true;

	// Sets initial fov to 45.0f; currently cannot be changed
	fov = 45.0f;
}

matrix4 Camera::GetView(void)
{
	UpdateViewMatrix();
	return m_m4View;
}

matrix4 Camera::GetProjection(bool bOrthographic)
{
	m_bOrthographic = bOrthographic;
	UpdateProjectionMatrix();
	return m_m4Projection;
}

void Camera::SetPosition(vector3 v3Position)
{
	m_v3Position = v3Position;
}

void Camera::SetTarget(vector3 v3Target)
{
	m_v3Target = v3Target;
}

void Camera::SetUp(vector3 v3Up)
{
	m_v3Up = v3Up;
}

void Camera::MoveForward(float fIncrement)
{
}

void Camera::MoveSideways(float fIncrement)
{
}

void Camera::MoveVertical(float fIncrement)
{
}

void Camera::ChangePitch(float fIncrement)
{
}

void Camera::ChangeRoll(float fIncrement)
{
}

void Camera::ChangeYaw(float fIncrement)
{
}

void Camera::SetFrontClippingPlane(vector3 bottomL, vector3 topR)
{
	m_cpFront.v3BottomLeft = bottomL;
	m_cpFront.v3TopRight = topR;
}

void Camera::SetBackClippingPlane(vector3 bottomL, vector3 topR)
{
	m_cpBack.v3BottomLeft = bottomL;
	m_cpBack.v3TopRight = topR;
}

void Camera::UpdateViewMatrix()
{
	m_m4View = glm::lookAt(m_v3Target, m_v3Position, m_v3Up);
	/* OLD WAY OF DOING THINGS, BECAUSE I CAN READ DIRECTIONS */
	//// X
	//vector3 crossX = glm::cross(vector3(1.0f, 0.0f, 0.0f), m_v3Right);			// Axis of rotation for X
	//float dotX = glm::acos(glm::dot(vector3(1.0f, 0.0f, 0.0f), m_v3Right));		// Angle of rotation for X
	//
	//// Y
	//vector3 crossY = glm::cross(vector3(0.0f, 1.0f, 0.0f), m_v3Up);				// Axis of rotation for Y
	//float dotY = glm::acos(glm::dot(vector3(0.0f, 1.0f, 0.0f), m_v3Up));		// Angle of rotation for Y
	//
	//// Z
	//vector3 crossZ = glm::cross(vector3(0.0f, 0.0f, 1.0f), -m_v3Target);			// Axis of rotation for Z
	//float dotZ = glm::acos(glm::dot(vector3(0.0f, 0.0f, 1.0f), -m_v3Target));	// Angle of rotation for Z
	//
	//glm::quat quatX = glm::angleAxis(dotX, crossX);		// Quaternion holding X orientation
	//glm::quat quatY = glm::angleAxis(dotY, crossY);		// Quaternion holding Y orientation
	//glm::quat quatZ = glm::angleAxis(dotZ, crossZ);		// Quaternion holding Z orientation
	//
	//glm::quat orientation = quatX * quatY * quatZ;		// Sum of all orientations
	//
	//m_m4View = glm::translate(m_v3Position) * glm::mat4_cast(orientation);
}

void Camera::UpdateProjectionMatrix()
{
	if (m_bOrthographic) {
		m_m4Projection = glm::ortho(m_cpFront.v3BottomLeft.x, m_cpFront.v3TopRight.x, m_cpFront.v3BottomLeft.y, m_cpFront.v3TopRight.y, m_cpFront.v3BottomLeft.z, m_cpBack.v3BottomLeft.z);
	}
	else {
		m_m4Projection = glm::perspective(fov, 1080.0f / 768.0f, m_cpFront.v3BottomLeft.z, m_cpBack.v3BottomLeft.z);
	}
}