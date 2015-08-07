#include "Tester.h"

#include <cmath>
#include <iostream>

#define EPS (0.001)


ResultType GetResultType(TestType testType)
{
	switch(testType)
	{
		case TT_ILines:
		return RT_OnePoint;
		case TT_ProjectionPointLine:
		return RT_OnePoint;
		case TT_QuadEquation:
		return RT_TwoX;
		case TT_ILineCircle:
		return RT_TwoPoints;
		case TT_ICircleCircle:
		return RT_TwoPoints;
		case TT_ProjectionPointCircle:
		return RT_OnePoint;
		case TT_AngleBisector:
		return RT_Line;
		default :
		throw "Test type's result not defined";
	}
}

Test::Test(TestType type) : type{type}
{
	
}

void Test::SetLine(float A, float B, float C, int index)
{
	if(index == 0)
	{
		this->A = A;
		this->B = B;
		this->C = C;
	}
	else
	{
		this->D = A;
		this->E = B;
		this->F = C;
	}
}

void Test::SetQuadraticParams(float A, float B, float C, int index)
{
	SetLine(A,B,C,index);
}

void Test::SetCircle(float u, float v, float r, int index)
{
	if(index == 0)
	{
		u1 = u;
		v1 = v;
		r1 = r;
	}
	else
	{
		u2 = u;
		v2 = v;
		r2 = r;
	}
}
void Test::SetPoint(float px, float py)
{
	this->px = px;
	this->py = py;
}

Tester::Tester()
{
}

Tester::~Tester()
{
}


void Tester::InitTests()
{
	Test t1{TT_ILines};
	t1.SetLine(1.f, -2.f, -2.f, 0);
	t1.SetLine(1.f, 2.f, 8.f, 1);
	t1.feasible = true;
	t1.x1 = 3.f;
	t1.y1 = 2.5f;
	AddTest(t1);
	
	Test t2{TT_ProjectionPointLine};
	t2.SetPoint(6.5f, 3.f);
	t2.SetLine(3.f, 2.f, 6.f, 0);
	t2.feasible = true;
	t2.x1 = 2.f;
	t2.y1 = 0.f;
	AddTest(t2);
	
	Test t3{TT_QuadEquation};
	t3.SetQuadraticParams(1.f, -6.f, 11.f, 0);
	t3.feasible = false;
	AddTest(t3);
	
	Test t4{TT_QuadEquation};
	t4.SetQuadraticParams(1.f, 2.f, 0.f, 0);
	t4.feasible = true;
	t4.x1 = 0.f;
	t4.x2 = -2.f;
	AddTest(t4);
	
	Test t5{TT_ILineCircle};
	t5.SetLine(0.f, 1.f, 4.f, 0);
	t5.SetCircle(4.f, 0.f, 2.f, 0);
	t5.feasible = false;
	AddTest(t5);
	
	Test t6{TT_ILineCircle};
	t6.SetLine(.5f, 1.f, -7.f, 0);
	t6.SetCircle(5.f, -7.f, 5.f, 0);
	t6.feasible = true;
	t6.x1 = 0.f;
	t6.y1 = -7.f;
	t6.x2 = 8.f;
	t6.y2 = -11.f;
	AddTest(t6);
	
	Test t7{TT_ICircleCircle};
	t7.SetCircle(5.f, -7.f, 5.f, 0);
	t7.SetCircle(1.f, -3.f, 1.f, 1);
	t7.feasible = true;
	t7.x1 = 2.f;
	t7.y1 = -3.f;
	t7.x2 = 1.f;
	t7.y2 = -4.f;
	AddTest(t7);
	
	Test t8{TT_ICircleCircle};
	t8.SetCircle(5.f, -7.f, 5.f, 0);
	t8.SetCircle(-3.f, -4.f, 3.f, 1);
	t8.feasible = false;
	AddTest(t8);
	
	
	Test t9{TT_ProjectionPointCircle};
	t9.SetCircle(3.f, 2.f, sqrtf(2.f), 0);
	t9.SetPoint(7.f, -2.f);
	t9.feasible = true;
	t9.x1 = 4.f;
	t9.y1 = 1.f;
	AddTest(t9);
	
	
	Test t10{TT_AngleBisector};
	t10.SetLine(1.f, 0.f, 0.f, 0);
	t10.SetLine(0.f, 1.f, 0.f, 1);
	t10.feasible = true;
	t10.G = -1.f;
	t10.H = 1.f;
	t10.I = 0.f;
	AddTest(t10);
	
	Test t11{TT_AngleBisector};
	
	t11.SetLine(-.5f, 1.f, 0.f, 0);
	t11.SetLine(-.5f, -1.f, 0.f, 1);
	t11.feasible = true;
	t11.G = 0.f;
	t11.H = 1.f;
	t11.I = 0.f;
	AddTest(t11);
	
	Test t12{TT_AngleBisector};
	t12.SetLine(-2.f , 1.f, -10.f, 0);
	t12.SetLine(2.f, -1.f, 2.f, 1);
	t12.feasible = true;
	t12.G = -2.f;
	t12.H = 1.f;
	t12.I = -6.f;
	AddTest(t12);
}

void Tester::AddTest(Test t)
{
	tests.push_back(t);
}

	
void Tester::RunTests()
{
	int testCount = tests.size();
	int passedTest = 0;
	int testIndex = 0;
	for(Test t : tests)
	{
		testIndex++;
		float x1, y1, x2, y2;
		x1 = y1 = x2 = y2 = 0;
		float G, H, I;
		bool feasible;
		
		if(t.type == TT_ILines)
		{
			feasible = IntersectLines(t.A, t.B, t.C, t.D, t.E, t.F, x1, y1);
		}
		else if(t.type == TT_ProjectionPointLine)
		{
			feasible = true;
			OrthogonalProjectionOfPointOnLine(t.A, t.B, t.C, t.px, t.py, x1, y1);
		}
		else if(t.type == TT_QuadEquation)
		{
			feasible = QuadraticEquation(t.A, t.B, t.C, x1, x2);
		}
		else if(t.type == TT_ILineCircle)
		{
			feasible = IntersectLineCircle(t.A, t.B, t.C, t.u1, t.v1, t.r1, x1, y1, x2, y2);
		}
		else if(t.type == TT_ICircleCircle)
		{
			feasible = IntersectCircleCircle(t.u1, t.v1, t.r1, t.u2, t.v2, t.r2, x1, y1, x2, y2);
		}
		else if(t.type == TT_ProjectionPointCircle)
		{
			feasible = true;
			OrthogonalProjectionOfPointOnCircle(t.u1, t.v1, t.r1, t.px, t.py, x1, y1);
		}
		else if(t.type == TT_AngleBisector)
		{
			feasible = true;
			float l1rec = 1.f / sqrtf(t.A * t.A + t.B * t.B);
			float l2rec = 1.f / sqrtf(t.D * t.D + t.E * t.E);
			AngleBisector(t.A * l1rec, t.B * l1rec, t.C * l1rec, t.D * l2rec, t.E * l2rec, t.F * l2rec, G, H, I);
		}
		
		ResultType resultType = GetResultType(t.type);
		
		const char* str_feasible = "feasible";
		const char* str_not_feasible = "not feasible";
		
		bool numbersMatch;
		
		if(resultType == RT_OnePoint)
		{
			std::cout << "Test " << testIndex << ": " << (t.feasible ? str_feasible : str_not_feasible);
			if(t.feasible)
				std::cout << ", solution at: ("<< t.x1 << "," << t.y1 << ")\n";
			else
				std::cout << "\n";
			
			std::cout << "Lib result: " << (feasible ? str_feasible : str_not_feasible);
			if(feasible)
				std::cout << ", solution at: ("<< x1 << "," << y1 << ")\n\n";
			else
				std::cout << "\n\n";
			
			numbersMatch = fabs(x1 - t.x1) < EPS && fabs(y1 - t.y1) < EPS;
		}
		else if(resultType == RT_TwoPoints)
		{
			std::cout << "Test " << testIndex << ": " << (t.feasible ? str_feasible : str_not_feasible);
			if(t.feasible)
				std::cout << ", solution at: ("<< t.x1 << "," << t.y1 << "), (" << t.x2 << "," << t.y2 << ")\n";
			else
				std::cout << "\n";
				
			std::cout << "Lib result: " << (feasible ? str_feasible : str_not_feasible);
			if(feasible)
				std::cout << ", solution at: ("<< x1 << "," << y1 << "), (" << x2 << "," << y2 << ")\n\n";
			else
				std::cout << "\n\n";
				
			numbersMatch = fabs(x1 - t.x1) < EPS && fabs(y1 - t.y1) < EPS && fabs(x2 - t.x2) < EPS && fabs(y2 - t.y2) < EPS;
			if(!numbersMatch)
			{
				numbersMatch = fabs(x1 - t.x2) < EPS && fabs(y1 - t.y2) < EPS && fabs(x2 - t.x1) < EPS && fabs(y2 - t.y1) < EPS;
			}
		}
		else if(resultType == RT_TwoX)
		{
			std::cout << "Test " << testIndex << ": " << (t.feasible ? str_feasible : str_not_feasible);
			if(t.feasible)
				std::cout << ", solution at: ("<< t.x1 << "," << t.x2 << ")\n";
			else
				std::cout << "\n";
				
			std::cout << "Lib result: " << (feasible ? str_feasible : str_not_feasible);
			if(feasible)
				std::cout << ", solution at: ("<< x1 << "," << x2 << ")\n\n";
			else
				std::cout << "\n\n";
			
			numbersMatch = fabs(x1 - t.x1) < EPS && fabs(x2 - t.x2) < EPS;
			if(!numbersMatch)
			{
				numbersMatch = fabs(x1 - t.x2) < EPS && fabs(x2 - t.x1) < EPS;
			}
		}
		else if(resultType == RT_Line)
		{
			std::cout << "Test " << testIndex << ": " << (t.feasible ? str_feasible : str_not_feasible);
			if(t.feasible)
				std::cout << ", solution: "<< t.G << " * x + " << t.H << " * y = " << t.I << "\n";
			else
				std::cout << "\n";
				
			std::cout << "Lib result: " << (feasible ? str_feasible : str_not_feasible);
			if(feasible)
				std::cout << ", solution: "<< G << " * x + " << H << " * y = " << I << "\n\n";
			else
				std::cout << "\n\n";
			//normalizing
			float l1rec = 1.f / sqrtf(G * G + H * H);
			float l2rec = 1.f / sqrtf(t.G * t.G + t.H * t.H);
			G *= l1rec;
			H *= l1rec;
			I *= l1rec;
			t.G *= l2rec;
			t.H *= l2rec;
			t.I *= l2rec;
			if (G * t.G < 0)
			{
				G *= -1.f;
				H *= -1.f;
				I *= -1.f;
			}
			
			numbersMatch = fabs(G - t.G) < EPS && fabs(H - t.H) < EPS && fabs(I - t.I) < EPS ;
		}
			
		if(!t.feasible && !feasible)
		{
			passedTest++;
			continue;
		}
		if(t.feasible != feasible)
		{
			continue;
		}
		if(numbersMatch)
		{
			passedTest++;
		}
		
	}
	
	std::cout << passedTest << " out of " << testCount << " tests passed : ";
	if(passedTest == testCount)
	{
		std::cout << "PASS";
	}
	else
	{
		std::cout << "FAIL";
	}
	std::cout << std::endl;

}