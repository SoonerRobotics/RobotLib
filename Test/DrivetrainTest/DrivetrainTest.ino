#include "Collection.h"
#include "BasicDrive.h"

BasicDrive basicDrive;

void setup()
{
	Collection<int> leftM(3), leftE(2), rightM(3), rightE(2);
	
	leftM.add(1); //pin numbers
	leftM.add(2);
	leftM.add(3);
	
	leftE.add(4);
	leftE.add(5);
	
	rightM.add(6);
	rightM.add(7);
	rightM.add(8);
	
	rightE.add(9);
	rightE.add(10);
	
	basicDrive.begin(leftM,leftE,rightM,rightE);
}

void loop()
{
	
}