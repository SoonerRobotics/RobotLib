#include "Collection.h"
#include "BasicDrive.h"

BasicDrive drivetrain;

void setup()
{
	Collection<int> leftM(2), leftE(2), rightM(2), rightE(2);
	
	leftM.add(1);
	leftM.add(2);
	
	leftE.add(3);
	leftE.add(4);
	
	rightM.add(5);
	rightM.add(6);
	
	rightE.add(7);
	rightE.add(8);
	
	drivetrain.begin(leftM,leftE,rightM,rightE);
}

void loop()
{

}