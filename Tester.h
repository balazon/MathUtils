#pragma once

#include "MathUtils.h"

struct Test
{
	
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

