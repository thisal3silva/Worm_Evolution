#ifndef  CIRCLEOFLIFE_H_INCLUDED
#define CIRCLEOFLIFE_H_INCLUDED

#include <vector>

class Worm;

class CircleOfLife
{
private:
	std::vector<Worm> Population;
	std::vector<Worm> Pool;

public:

	CircleOfLife(int numPop);

	~CircleOfLife();

	void showPopulation();

	void createReproductionPool();

	void createNewPopulation();
};

#endif