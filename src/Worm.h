#ifndef  WORM_H_INCLUDED
#define WORM_H_INCLUDED

#include <cstdlib>
#include <vector>

class Worm
{
private:
	std::vector<std::pair<int, int>> _DNA;
	std::pair<double, double> _Velocity;
	std::pair<double, double> _Position;
	int _WormLength;
	int _currChromosome;
	double _ProficiencyMetric;
	std::pair<int, int> _desiredPos;
	bool _dead;

public:
	// initialize Worm at (0,50) with random generated DNA
	Worm();

	Worm(std::vector<std::pair<int, int>> newDNA);

	~Worm();

	//basically physics engine
	//Each item in DNA is a force and it gets added to Velocity and Position
	void update();

	//getters
	std::vector<std::pair<int, int>> getDNA();
	std::pair<double, double> getPosition();
	std::pair<double, double> getVelocity();
	double getPMetric();

	void drawWorm();

	void setPMetric(double dist, bool hitTarget);

	double getDistance(std::pair<double, double> P1, std::pair<double, double> P2);

	bool isDead();

	std::vector<std::pair<int, int>> Mate(Worm mate);

	void mutate();

};
#endif 

