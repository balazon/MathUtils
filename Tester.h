#pragma once

#include "MathUtils.h"
#include <vector>
/*
bool IntersectLines(float A, float B, float C, float D, float E, float F, float& resX, float& resY);

void OrthogonalProjectionOfPointOnLine(float A, float B, float C, float tx, float ty, float& resX, float& resY);

bool QuadraticEquation(float a, float b, float c, float& x1, float& x2);

bool IntersectLineCircle(float A, float B, float C, float u, float v, float r, float& x1, float& y1, float& x2, float& y2);

bool IntersectCircleCircle(float u1, float v1, float r1, float u2, float v2, float r2, float& x1, float& y1, float& x2, float& y2);

void OrthogonalProjectionOfPointOnCircle(float u, float v, float r, float tx, float ty, float& resX, float& resY);

void AngleBisector(float A, float B, float C, float D, float E, float F, float& G, float& H, float& I);
*/
enum TestType {TT_ILines, TT_ProjectionPointLine, TT_QuadEquation, TT_ILineCircle, TT_ICircleCircle, TT_ProjectionPointCircle, TT_AngleBisector};

enum ResultType {RT_OnePoint, RT_TwoPoints, RT_TwoX, RT_Line};

ResultType GetResultType(TestType testType);

struct Test
{
	//test data
	
	TestType type;
	//lines: Ax + By = C, or quadratic equations
	float A, B, C, D, E, F;
	//circles: (x-u1)^2 + (y-v1)^2 = r1^2
	float u1, v1, r1, u2, v2, r2;
	//a point
	float px, py;
	
	//test's solution
	bool feasible;
	float x1, y1, x2, y2;
	float G, H, I;
	
	Test(TestType type);
	
	void SetLine(float A, float B, float C, int index);
	void SetCircle(float u, float v, float r, int index);
	void SetPoint(float px, float py);
	void SetQuadraticParams(float A, float B, float C, int index);
};

class Tester
{
public:
	Tester();
	~Tester();
	
	void InitTests();
	void AddTest(Test t);
	void RunTests();
	
private:
	
	
	std::vector<Test> tests;
};

