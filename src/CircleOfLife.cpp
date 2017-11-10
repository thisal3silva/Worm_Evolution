#include "CircleOfLife.h"
#include "Worm.h"
#include <GL\freeglut.h>
#include <math.h>

CircleOfLife::CircleOfLife(int numPop)
{
	for (int i = 0; i < numPop; i++)
	{
		Population.push_back(Worm());
	}
}

CircleOfLife::~CircleOfLife()
{
}

void CircleOfLife::showPopulation()
{
	bool endCycle = Population[0].isDead();
	for (int i =0; i < Population.size(); i++)
	{
		Population[i].drawWorm();
		Population[i].update();
	}
	
	if (endCycle)
	{
		createReproductionPool();
		createNewPopulation();
	}
}

void CircleOfLife::createReproductionPool()
{
	for (int i = 0; i < Population.size(); i++)
	{
		for (int j = 0; j < Population[i].getPMetric(); j++)
		{
			Pool.push_back(Population[i]);
		}
	}
}

void CircleOfLife::createNewPopulation()
{
	for (int i = 0; i < Population.size(); i++)
	{
		Worm temp1 = Pool[rand() % Pool.size()];
		Worm temp2 = Pool[rand() % Pool.size()];

		Population[i] = temp1.Mate(temp2);
		if ((rand() % 100) < 5)
		{
			Population[i].mutate();
		}
	}
	Pool.clear();
}
