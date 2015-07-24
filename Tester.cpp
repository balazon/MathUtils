#include "Tester.h"

Tester::Tester()
{
}

Tester::~Tester()
{
}


void Tester::InitTests()
{
	Test t1{ILines};
	t1.A = 1.f;
	t1.B = -2.f;
	t1.C = -2.f;
	t1.D = 1.f;
	t1.E = 2.f;
	t1.F = 8.f;
	t1.feasible = true;
	t1.x1 = 3.f;
	t1.y1 = 2.5f;
	AddTest(t1);
	
}

void Tester::AddTest(Test t)
{
	tests.push_back(t);
}

	
void Tester::RunTests()
{
	

}