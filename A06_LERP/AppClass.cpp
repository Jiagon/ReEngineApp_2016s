#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");			// Walleye model
	//m_pMeshMngr->LoadModel("Minecraft\\Creeper.bto", "Creeper");		// Creeper model

	fDuration = 1.0f;

	currentSphere = 0;
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan;
#pragma endregion

#pragma region Your Code goes here

	static DWORD timerSinceBoot = GetTickCount();				// timer since the computer started
	DWORD timerSinceStart = GetTickCount() - timerSinceBoot;	// current time
	float fTimer = timerSinceStart / 1000.0f;					// was in millis need it in secs

	m_pMeshMngr->PrintLine("");									// print an empty line
	m_pMeshMngr->PrintLine(std::to_string(fTimer));				// print the timer

	// CREATING LOCATIONS TO ALL SPHERES AND ADDING THEM TO RENDER LIST
	v3Spheres[0] = vector3(-4.0f, -2.0f, 5.0f);
	v3Spheres[1] = vector3(1.0f, -2.0f, 5.0f);
	v3Spheres[2] = vector3(-3.0f, -1.0f, 3.0f);
	v3Spheres[3] = vector3(2.0f, -1.0f, 3.0f);
	v3Spheres[4] = vector3(-2.0f, 0.0f, 0.0f);
	v3Spheres[5] = vector3(3.0f, 0.0f, 0.0f);
	v3Spheres[6] = vector3(-1.0f, 1.0f, -3.0f);
	v3Spheres[7] = vector3(4.0f, 1.0f, -3.0f);
	v3Spheres[8] = vector3(0.0f, 2.0f, -5.0f);
	v3Spheres[9] = vector3(5.0f, 2.0f, -5.0f);
	v3Spheres[10] = vector3(1.0f, 3.0f, -5.0f);

	// Adds every sphere to the mesh renderer
	for (int i = 0; i < numSpheres; i++) {
		m_pMeshMngr->AddSphereToRenderList(glm::translate(v3Spheres[i]) * glm::scale(vector3(0.1)), RERED, SOLID);
	}

	// Change the start / end spheres to the mod of the currentSphere
		//(you don't mod the current sphere because it's necessary for the percentage!)
	vector3 v3Start = v3Spheres[currentSphere % numSpheres];
	vector3 v3End = v3Spheres[(currentSphere + 1) % numSpheres];

	// Percentage = Map of fTimer (0, 2) to float (0, 1)
	float percentage = MapValue(fTimer, 0.0f, 2.0f, 0.0f, 1.0f);

	// Subtract the currentSphere to keep values between 0 and 1
	percentage -= currentSphere;

	// Lerp between the start and end vectors for percentage
	vector3 v3Current = glm::lerp(v3Start, v3End, percentage);
	m_pMeshMngr->PrintLine("Percentage: " + std::to_string(percentage), REGREEN);	// print out the percentage

	// Create the mat4 for WallEye and set the model to that mat's position
	matrix4 m4WallEye = glm::translate(v3Current);
	m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");

	// If the percentage reaches above 1.0f, increment the currentSphere, thereby resetting everything
	if (percentage >= 1.0f) {
		currentSphere++;
	}

#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);

#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}