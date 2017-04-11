#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion
#pragma region FEEL FREE TO USE THIS CLOCK
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 
#pragma endregion
#pragma region YOUR CODE GOES HERE
	m_m4Steve = glm::rotate(IDENTITY_M4, m_fSteve, vector3(0.0f, 0.0f, 1.0f));
	m_fSteve += 1.2f;

	float percentage = MapValue(static_cast<float>(dTotalTime / dDeltaTime), 0.0f, static_cast<float>(1.0f / dDeltaTime), 0.0f, 0.2f);
	percentage -= rotations;

	vector3 v3Start = vector3(0.0f, 0.0f, 0.0f);
	vector3 v3End = vector3(0.0f, 0.0f, 0.0f);

	if (forward) {
		v3End = vector3(0.0f, 5.0f, 0.0f);
		if (m_fSteve >= 360.0f) {
			rotations++;
			forward = false;
		}
	}
	else {
		v3Start = vector3(0.0f, 5.0f, 0.0f);
		if (m_fSteve >= 360.0f) {
			rotations++;
			forward = true;
		}
	}

	m_fSteve = static_cast<float>(fmod(m_fSteve, 360.0f));

	vector3 v3Current = glm::lerp(v3Start, v3End, percentage);

	m_m4Steve *= glm::translate(v3Current);

	//m_m4Steve = glm::mat4(1.0f); // same as m_m4Steve = IDENTITY_M4; setting the identity to steve
#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
<<<<<<< HEAD
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds: ");
=======
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
>>>>>>> 3a599dd642348e48a93f58a5cdd8a50114af0a2c
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS: ");
	m_pMeshMngr->PrintLine(std::to_string(nFPS), RERED);
	m_pMeshMngr->Print("Rotations: ");
	m_pMeshMngr->PrintLine(std::to_string(rotations), RERED);
#pragma endregion
}
