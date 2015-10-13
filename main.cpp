#include <stdio.h>
#include "Tester.h"
#include "MathUtils.h"

int main(int argc, char **argv)
{
	Tester t;
	t.InitTests();
	t.RunTests();
	
	float tx, ty;
	BMU::OrthogonalProjectionOfPointOnCircle(7.5f, 2.5f, 2.5f, 6.f, 3.f, tx, ty);
	
	printf("\n\n%.2f %.2f", tx, ty);
	
	return 0;
}
