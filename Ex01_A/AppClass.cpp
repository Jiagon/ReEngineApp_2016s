#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	static float fTimer = 0.0f;//creates a timer
	static uint uClock = m_pSystem->GenClock();//ask the system for a new clock id
	float fDeltaTime = m_pSystem->LapClock(uClock);//lap the selected clock
	fTimer += fDeltaTime;//add the delta time to the current clock
#pragma endregion

#pragma region YOUR CODE GOES HERE

	static vector3 v3Start = vector3(0.0f, 0.0f, 0.0f);
	static vector3 v3End = vector3(0.0f, 3.0f, 0.0f);

	float fTotalTime = 1.0f;
	float fPercentage = MapValue(fTimer, 0.0f, fTotalTime / 2.0f, 0.0f, 1.0f);

	if (fPercentage > 1.0f) {
		/*vector3 v3Temp = v3Start;
		v3Start = v3End;
		v3End = v3Temp;*/

		std::swap(v3Start, v3End);
		fTimer = 0;
	}

	glm::quat q1 = glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
	glm::quat q2 = glm::angleAxis(-180.0f, vector3(0.0f, 0.0f, 1.0f));

	glm::quat q3 = glm::mix(q1, q2, fPercentage * 2.0f);

	vector3 v3Current = glm::lerp(v3Start, v3End, fPercentage);

	modelMatrix = glm::translate(v3Current) * ToMatrix4(q3);


	// My solution that wasn't fully implemented and doesn't quite work... ._.;
	/*glm::quat q1 = glm::quat(vector3(0.0f, 0.0f, 0.0f));
	glm::quat q2 = glm::quat(vector3(0.0f, 3.0f, 0.0f));

	float percent = MapValue(fTimer, 0.0f, 2.0f, 0.0f, 1.0f);

	vector3 v3Start = vector3(0.0f, 0.0f, 0.0f);
	vector3 v3End = vector3(0.0f, 3.0f, 0.0f);

	angle += fDeltaTime * 5;

	matrix4 m_qMove;

	if (!changeDir) {
		m_qMove = glm::translate(glm::mix(v3Start, v3End, percent));
	}
	else {
		m_qMove = glm::translate(glm::mix(v3End, v3Start, percent));
	}

	if (percent >= 1.0f) {
		fTimer = 0.0f;
		changeDir = !changeDir;
	}

	glm::quat q3 = glm::angleAxis(angle, vector3(0.0f, 0.0f, PI * 2));

	if (angle > 360) {
		angle = 0;
	}

	modelMatrix = m_qMove;
	modelMatrix *= ToMatrix4(q3);*/

#pragma endregion

#pragma region DOES NOT NEED CHANGES
	m_pMeshMngr->SetModelMatrix(modelMatrix, 0);//Set the model matrix to the model

	m_pMeshMngr->AddSkyboxToRenderList();//Adds a skybox to the renderlist
	m_pMeshMngr->AddInstanceToRenderList("ALL"); //Adds all loaded instances to the render list

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->PrintLine("Timer: ");
	m_pMeshMngr->PrintLine(std::to_string(fTimer), REGREEN);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

