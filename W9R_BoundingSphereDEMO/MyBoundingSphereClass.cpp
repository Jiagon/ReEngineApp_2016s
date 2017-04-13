#include "MyBoundingSphereClass.h"

MyBoundingSphereClass::MyBoundingSphereClass(std::vector<vector3> vertexList)
{
	m_fRadius = 0.0f;
	m_v3CenterGlobal = vector3(0.0f);

	if (vertexList.size() < 1)
		return;

	vector3 v3Min = vertexList[0];
	vector3 v3Max = vertexList[0];

	for (int i = 1; i < vertexList.size(); i++)
	{
		if (v3Min.x > vertexList[i].x)
		{
			v3Min.x = vertexList[i].x;
		}
		else if (v3Max.x < vertexList[i].x)
		{
			v3Max.x = vertexList[i].x;
		}

		if (v3Min.y > vertexList[i].y)
		{
			v3Min.y = vertexList[i].y;
		}
		else if (v3Max.y < vertexList[i].y)
		{
			v3Max.y = vertexList[i].y;
		}

		if (v3Min.z > vertexList[i].z)
		{
			v3Min.z = vertexList[i].z;
		}
		else if (v3Max.z < vertexList[i].z)
		{
			v3Max.z = vertexList[i].z;
		}
	}

	m_v3CenterLocal = m_v3CenterGlobal = (v3Max + v3Min) / 2.0f;

	m_fRadius = glm::distance(m_v3CenterGlobal, v3Max);

	m_pMeshMngr = MeshManagerSingleton::GetInstance();

	m_bColliding = false;
}

void MyBoundingSphereClass::RenderSphere()
{
	vector3 v3Color = REGREEN;
	if (m_bColliding) {
		v3Color = RERED;
	}
	m_pMeshMngr->AddSphereToRenderList(
		glm::translate(m_v3CenterGlobal) *
		glm::scale(vector3(m_fRadius) * 2.0f), v3Color, WIRE);
}
void MyBoundingSphereClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (m_m4ToWorld == a_m4ToWorld) {
		return;
	}

	m_m4ToWorld = a_m4ToWorld;
	m_v3CenterGlobal = vector3(m_m4ToWorld * vector4(m_v3CenterLocal, 1.0f));
}

bool MyBoundingSphereClass::IsColliding(MyBoundingSphereClass * a_pOther)
{
	float fDistance = glm::distance(this->m_v3CenterGlobal, a_pOther->m_v3CenterGlobal);
	float fRadiiSum = this->m_fRadius + a_pOther->m_fRadius;
	return fDistance < fRadiiSum;

	return false;
}
