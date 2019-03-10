#include "RandomNum.h"

void Random(int random[], int seed)
{
	srand(seed);
	for (int i = 0; i < 10; i++)
	{
		cout << RandomGen() << endl;
		random[i] = RandomGen();
	}

}

int RandomGen()
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);
}
