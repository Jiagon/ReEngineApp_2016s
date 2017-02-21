#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	/*
	Adds a triangle base on the three vectors
	*/
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> point;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	point.push_back(vector3(0, 0, a_fHeight / 2));

	/*point.push_back(vector3 (-fValue, -fValue, fValue)); //0
	point.push_back(vector3 (fValue, -fValue, fValue)); //1
	point.push_back(vector3 (fValue, fValue, fValue)); //2*/
	//vector3 point3(-fValue, fValue, fValue); //3

	// Add points for bottom triangles
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta) * a_fRadius, sin(theta) * a_fRadius, -a_fHeight / 2));
		theta += steps;
	}

	// Add point for height
	point.push_back(vector3(0, 0, a_fHeight));

	// Bottom triangles and top connecting triangles
	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i + 1], point[i]);
		AddTri(point[a_nSubdivisions + 1], point[i], point[i + 1]);
	}

	// Last triangle and connecting triangle
	AddTri(point[0], point[1], point[a_nSubdivisions]);
	AddTri(point[a_nSubdivisions + 1], point[a_nSubdivisions], point[1]);


	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> point;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);
	// Add point for bottom
	point.push_back(vector3(0, 0, -a_fHeight / 2));

	// Add points for bottom triangles
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta) * a_fRadius, sin(theta) * a_fRadius, -a_fHeight / 2));
		theta += steps;
	}
	// Add points for top triangles
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta) * a_fRadius, sin(theta) * a_fRadius, a_fHeight / 2));
		theta += steps;
	}

	// Add point for top
	point.push_back(vector3(0, 0, a_fHeight / 2));

	// Bottom triangles and top connecting triangles
	for (int i = 1; i < a_nSubdivisions; i++) {
		AddTri(point[0], point[i + 1], point[i]);
		AddTri(point[(a_nSubdivisions * 2) + 1], point[i + a_nSubdivisions], point[i + a_nSubdivisions + 1]);
	}

	// Last triangle and connecting triangle on bottom
	AddTri(point[0], point[1], point[a_nSubdivisions]);
	//AddTri(point[a_nSubdivisions + 1], point[a_nSubdivisions], point[1]);

	// Last triangle and connecting triangle on top
	AddTri(point[(a_nSubdivisions * 2) + 1], point[a_nSubdivisions * 2], point[a_nSubdivisions + 1]);

	// Side quads connecting top and bottom
	for (int i = 0; i <= a_nSubdivisions; i++) {
		AddQuad(point[i], point[i + 1], point[i + a_nSubdivisions], point[i + a_nSubdivisions + 1]);
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> point;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	// Add points for bottom outside points: 0 - (a_nSubdivisions - 1)
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta) * a_fOuterRadius, sin(theta) * a_fOuterRadius, -a_fHeight / 2));
		theta += steps;
	}

	// Add points for bottom inside points: a_nSubdivisions - ((a_nSubdivisions * 2) - 1)
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta) * a_fInnerRadius, sin(theta) * a_fInnerRadius, -a_fHeight / 2));
		theta += steps;
	}

	// Add points for top outside points: (a_nSubdivisions * 2) - ((a_nSubdivisions * 3) - 1)
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta) * a_fOuterRadius, sin(theta) * a_fOuterRadius, a_fHeight / 2));
		theta += steps;
	}

	// Add points for top inside points: (a_nSubdivisions * 3) - ((a_nSubdivisions * 4) - 1)
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta) * a_fInnerRadius, sin(theta) * a_fInnerRadius, a_fHeight / 2));
		theta += steps;
	}


	// Connect bottom outside points with bottom inside points
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		// Create bottom base
		AddQuad(point[i + 1], point[i], point[i + a_nSubdivisions + 1], point[i + a_nSubdivisions]);
		// Create top base
		AddQuad(point[i + (a_nSubdivisions * 2)], point[i + (a_nSubdivisions * 2) + 1], point[i + (a_nSubdivisions * 3)], point[i + (a_nSubdivisions * 3) + 1]);

		// Create outer sides
		AddQuad(point[i], point[i + 1], point[i + (a_nSubdivisions * 2)], point[i + (a_nSubdivisions * 2) + 1]);
		// Create inner sides
		AddQuad(point[i + a_nSubdivisions + 1], point[i + a_nSubdivisions], point[i + (a_nSubdivisions * 3) + 1], point[i + (a_nSubdivisions * 3)]);
	}

	// Manually add last quads
		// Last bottom base
	AddQuad(point[0], point[a_nSubdivisions - 1], point[a_nSubdivisions], point[(a_nSubdivisions * 2) - 1]);
		// Last top base
	AddQuad(point[(a_nSubdivisions * 3) - 1], point[a_nSubdivisions * 2], point[(a_nSubdivisions * 4) - 1], point[a_nSubdivisions * 3]);
		// Last outer side
	AddQuad(point[a_nSubdivisions - 1], point[0], point[(a_nSubdivisions * 3) - 1], point[a_nSubdivisions * 2]);
		// Last inner side
	AddQuad(point[a_nSubdivisions], point[(a_nSubdivisions * 2) - 1], point[a_nSubdivisions * 3], point[(a_nSubdivisions * 4) - 1]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1

	std::vector<vector3> point;
	float tLeft = 0;
	float tRight = 0;
	float pLeft = 0;
	float pRight = 0;

	float littleR = a_fOuterRadius - a_fInnerRadius;
	float bigR = a_fInnerRadius + littleR;

	for (int i = 0; i < a_nSubdivisionsA; i++) {
		pLeft = (2 * PI * i) / a_nSubdivisionsA;
		pRight = (2 * PI * (i + 1)) / a_nSubdivisionsA;

		for (int j = 0; j < a_nSubdivisionsB; j++) {
			tLeft = (2 * PI * j) / a_nSubdivisionsB;
			tRight = (2 * PI * (j + 1)) / a_nSubdivisionsB;
			point.push_back(vector3((bigR + (littleR * cos(tLeft))) * cos(pLeft), (bigR + (littleR * cos(tLeft))) * sin(pLeft), littleR * sin(tLeft)));
			point.push_back(vector3((bigR + (littleR * cos(tLeft))) * cos(pRight), (bigR + (littleR * cos(tLeft))) * sin(pRight), littleR * sin(tLeft)));
			point.push_back(vector3((bigR + (littleR * cos(tRight))) * cos(pLeft), (bigR + (littleR * cos(tRight))) * sin(pLeft), littleR * sin(tRight)));
			point.push_back(vector3((bigR + (littleR * cos(tRight))) * cos(pRight), (bigR + (littleR * cos(tRight))) * sin(pRight), littleR * sin(tRight)));

			AddQuad(point[0], point[1], point[2], point[3]);

			point.pop_back();
			point.pop_back();
			point.pop_back();
			point.pop_back();
		}
	}


	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 20)
		a_nSubdivisions = 20;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> point;
	// Theta and Phi values for the left and right sides, respectively
	float tLeft = 0;
	float tRight = 0;
	float pLeft = 0;
	float pRight = 0;

	// Loop for every subdivision that exists
	for (int i = 0; i < a_nSubdivisions; i++) {
		// Reset the values of the Phi variables b
		pLeft = (PI * i) / a_nSubdivisions;
		pRight = (PI * (i + 1)) / a_nSubdivisions;

		for (int j = 0; j < a_nSubdivisions; j++) {
			tLeft = (2 * PI * j) / a_nSubdivisions;
			tRight = (2 * PI * (j + 1)) / a_nSubdivisions;
			point.push_back(vector3(a_fRadius * cos(tLeft) * sin(pLeft), a_fRadius * sin(tLeft) * sin(pLeft), a_fRadius * cos(pLeft)));
			point.push_back(vector3(a_fRadius * cos(tLeft) * sin(pRight), a_fRadius * sin(tLeft) * sin(pRight), a_fRadius * cos(pRight)));
			point.push_back(vector3(a_fRadius * cos(tRight) * sin(pLeft), a_fRadius * sin(tRight) * sin(pLeft), a_fRadius * cos(pLeft)));
			point.push_back(vector3(a_fRadius * cos(tRight) * sin(pRight), a_fRadius * sin(tRight) * sin(pRight), a_fRadius * cos(pRight)));

			AddQuad(point[0], point[1], point[2], point[3]);

			point.pop_back();
			point.pop_back();
			point.pop_back();
			point.pop_back();
		}
	}


	//Your code ends here
	CompileObject(a_v3Color);
}