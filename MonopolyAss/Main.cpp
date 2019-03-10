#include <iostream>
#include "RandomNum.h"

int main()
{
	int seed = 5;
	int randomNumber[10];

	Random(randomNumber, seed);
	system("Pause");
}