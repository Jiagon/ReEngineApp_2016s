#include "MyBoundingBoxClass.h"

MyBoundingBoxClass::MyBoundingBoxClass(std::vector<vector3> vertexList)
{
	m_bColliding = false;
	m_fRadius = 0.0f;
	m_v3CenterGlobal = vector3(0.0f);

	if (vertexList.size() < 1)
		return;

	m_v3Min = vertexList[0];
	m_v3Max = vertexList[0];

	for (int i = 1; i < vertexList.size(); i++)
	{
		if (m_v3Min.x > vertexList[i].x)
		{
			m_v3Min.x = vertexList[i].x;
		}
		else if (m_v3Max.x < vertexList[i].x)
		{
			m_v3Max.x = vertexList[i].x;
		}

		if (m_v3Min.y > vertexList[i].y)
		{
			m_v3Min.y = vertexList[i].y;
		}
		else if (m_v3Max.y < vertexList[i].y)
		{
			m_v3Max.y = vertexList[i].y;
		}

		if (m_v3Min.z > vertexList[i].z)
		{
			m_v3Min.z = vertexList[i].z;
		}
		else if (m_v3Max.z < vertexList[i].z)
		{
			m_v3Max.z = vertexList[i].z;
		}
	}

	m_v3CenterLocal = m_v3CenterGlobal = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3Max);
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3Size = m_v3Max - m_v3Min;

	m_v3MaxG = m_v3Max;
	m_v3MinG = m_v3Min;

	m_v3MaxLargest = m_v3Max;
	m_v3MinLargest = m_v3Min;

	m_v3SizeLargest = m_v3MaxLargest - m_v3MinLargest;
	
	//m_v3Size.x = glm::distance(vector3(m_v3Min.x, 0.0, 0.0), vector3(m_v3Max.x, 0.0, 0.0));
	//m_v3Size.y = glm::distance(vector3(0.0, m_v3Min.y, 0.0), vector3(0.0, m_v3Max.y, 0.0));
	//m_v3Size.z = glm::distance(vector3(0.0, 0.0, m_v3Min.z), vector3(0.0, 0.0, m_v3Max.z));
}

void MyBoundingBoxClass::RenderSphere(vector3 pos)
{
	vector3 v3Color = REGREEN;

	if (true == m_bColliding)
		v3Color = RERED;

	// Personal cube
	m_pMeshMngr->AddCubeToRenderList(
		m_m4ToWorld *
		glm::translate(m_v3CenterLocal) *
		glm::scale(m_v3Size),
		v3Color, WIRE);

	// All-encompassing cube
	m_pMeshMngr->AddCubeToRenderList(
		glm::translate(pos)*
		glm::translate(m_v3CenterLocal) *
		glm::scale(m_v3SizeLargest),
		v3Color, WIRE);



	/*m_pMeshMngr->AddSphereToRenderList(
		glm::translate(m_v3CenterGlobal) *
		glm::scale(vector3(m_fRadius) * 2.0f), v3Color, WIRE);*/
}
void MyBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
{ 

	if (m_m4ToWorld == a_m4ToWorld)
		return;

	//for (int i = 0; i < 8; i++)
	/*{
		// ----------------------------------->>HERE
		if (m_v3MinG.x > m_v3MaxG.x) {
			m_v3MaxLargest.x = m_v3MaxG.x;
			m_v3MinLargest.x = m_v3MinG.x;
		}
		else {
			m_v3MaxLargest.x = m_v3MinG.x;
			m_v3MinLargest.x = m_v3MaxG.x;
		}

		if (m_v3MinG.y > m_v3MaxG.y) {
			m_v3MaxLargest.y = m_v3MaxG.y;
			m_v3MinLargest.y = m_v3MinG.y;
		}
		else {
			m_v3MaxLargest.y = m_v3MinG.y;
			m_v3MinLargest.y = m_v3MaxG.y;
		}

		if (m_v3MinG.z > m_v3MaxG.z) {
			m_v3MaxLargest.z = m_v3MaxG.z;
			m_v3MinLargest.z = m_v3MinG.z;
		}
		else {
			m_v3MaxLargest.z = m_v3MinG.z;
			m_v3MinLargest.z = m_v3MaxG.z;
		}
	}*/


	m_m4ToWorld = a_m4ToWorld;
	m_v3CenterGlobal = vector3(m_m4ToWorld * vector4(m_v3CenterLocal, 1.0f));
	m_v3MinG = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	m_v3MaxG = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));

	std::vector<vector3> vectorList;

	m_v3MaxLargest = m_v3MaxG;
	m_v3MinLargest = m_v3MinG;

	vectorList.push_back(vector3(m_v3MinG.x, m_v3MinG.y, m_v3MinG.z));
	vectorList.push_back(vector3(m_v3MinG.x, m_v3MinG.y, m_v3MaxG.z));
	vectorList.push_back(vector3(m_v3MinG.x, m_v3MaxG.y, m_v3MinG.z));
	vectorList.push_back(vector3(m_v3MinG.x, m_v3MaxG.y, m_v3MaxG.z));
	vectorList.push_back(vector3(m_v3MaxG.x, m_v3MinG.y, m_v3MinG.z));
	vectorList.push_back(vector3(m_v3MaxG.x, m_v3MinG.y, m_v3MaxG.z));
	vectorList.push_back(vector3(m_v3MaxG.x, m_v3MaxG.y, m_v3MinG.z));
	vectorList.push_back(vector3(m_v3MaxG.x, m_v3MaxG.y, m_v3MaxG.z));

	for (int i = 0; i < 8; i++)
	{
		if (m_v3MinLargest.x < vectorList[i].x)
		{
			m_v3MinLargest.x = vectorList[i].x;
		}
		else if (m_v3MaxLargest.x > vectorList[i].x)
		{
			m_v3MaxLargest.x = vectorList[i].x;
		}

		if (m_v3MinLargest.y < vectorList[i].y)
		{
			m_v3MinLargest.y = vectorList[i].y;
		}
		else if (m_v3MaxLargest.y > vectorList[i].y)
		{
			m_v3MaxLargest.y = vectorList[i].y;
		}

		if (m_v3MinLargest.z < vectorList[i].z)
		{
			m_v3MinLargest.z = vectorList[i].z;
		}
		else if (m_v3MaxLargest.z > vectorList[i].z)
		{
			m_v3MaxLargest.z = vectorList[i].z;
		}
	}

	m_v3SizeLargest = m_v3MaxLargest - m_v3MinLargest;
}
bool MyBoundingBoxClass::IsColliding(MyBoundingBoxClass* a_other)
{
	if (this->m_v3MaxG.x < a_other->m_v3MinG.x)
		return false;
	else if (this->m_v3MinG.x > a_other->m_v3MaxG.x)
		return false;

	if (this->m_v3MaxG.y < a_other->m_v3MinG.y)
		return false;
	else if (this->m_v3MinG.y > a_other->m_v3MaxG.y)
		return false;

	if (this->m_v3MaxG.z < a_other->m_v3MinG.z)
		return false;
	else if (this->m_v3MinG.z > a_other->m_v3MaxG.z)
		return false;

	return true;

	//float fDistance = glm::distance(this->m_v3CenterGlobal, a_other->m_v3CenterGlobal);
	//float fRadiiSum = this->m_fRadius + a_other->m_fRadius;
	//return fDistance < fRadiiSum;
	if (this->m_v3MinG.z > a_other->m_v3MaxG.z)
		return false;

	return true;
}

void MyBoundingBoxClass::SetColliding(bool input) { m_bColliding = input; }
void MyBoundingBoxClass::SetCenterLocal(vector3 input) { m_v3CenterLocal = input; }
void MyBoundingBoxClass::SetCenterGlobal(vector3 input) { m_v3CenterGlobal = input; }
void MyBoundingBoxClass::SetRadius(float input) { m_fRadius = input; }
bool MyBoundingBoxClass::GetColliding(void) { return m_bColliding; }
vector3 MyBoundingBoxClass::GetCenterLocal(void) { return m_v3CenterLocal; }
vector3 MyBoundingBoxClass::GetCenterGlobal(void) { return m_v3CenterGlobal; }
float MyBoundingBoxClass::GetRadius(void) { return m_fRadius; }
matrix4 MyBoundingBoxClass::GetModelMatrix(void) { return m_m4ToWorld; }

//std::vector<vector3> vectorList;
//
//vectorList.push_back(vector3(m_v3MinG.x, m_v3MinG.y, m_v3MinG.z));
//vectorList.push_back(vector3(m_v3MinG.x, m_v3MinG.y, m_v3MaxG.z));
//vectorList.push_back(vector3(m_v3MinG.x, m_v3MaxG.y, m_v3MinG.z));
//vectorList.push_back(vector3(m_v3MinG.x, m_v3MaxG.y, m_v3MaxG.z));
//vectorList.push_back(vector3(m_v3MaxG.x, m_v3MinG.y, m_v3MinG.z));
//vectorList.push_back(vector3(m_v3MaxG.x, m_v3MinG.y, m_v3MaxG.z));
//vectorList.push_back(vector3(m_v3MaxG.x, m_v3MaxG.y, m_v3MinG.z));
//vectorList.push_back(vector3(m_v3MaxG.x, m_v3MaxG.y, m_v3MaxG.z));
//
//for (int i = 0; i < 8; i++)
//{
//	if (m_v3MinLargest.x > vectorList[i].x)
//	{
//		m_v3MinLargest.x = vectorList[i].x;
//	}
//	else if (m_v3MaxLargest.x < vectorList[i].x)
//	{
//		m_v3MaxLargest.x = vectorList[i].x;
//	}
//
//	if (m_v3MinLargest.y > vectorList[i].y)
//	{
//		m_v3MinLargest.y = vectorList[i].y;
//	}
//	else if (m_v3MaxLargest.y < vectorList[i].y)
//	{
//		m_v3MaxLargest.y = vectorList[i].y;
//	}
//
//	if (m_v3MinLargest.z > vectorList[i].z)
//	{
//		m_v3MinLargest.z = vectorList[i].z;
//	}
//	else if (m_v3MaxLargest.z < vectorList[i].z)
//	{
//		m_v3MaxLargest.z = vectorList[i].z;
//	}
//}