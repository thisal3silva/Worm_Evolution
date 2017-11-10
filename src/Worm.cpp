#include <cstdlib>
#include <vector>
#include "Worm.h"
#include <GL\freeglut.h>
#include <math.h>

#define num_Chromosomes 200
#define desired_x 300
#define desired_y 500

Worm::Worm()
{
	_Position = std::make_pair(500, 500);
	_currChromosome = 0;
	_WormLength = 10;
	_desiredPos = std::make_pair(desired_x, desired_y);

	for (int i = 0; i < num_Chromosomes; i++)
	{
		_DNA.push_back(std::make_pair((rand() % 20) - 9, (rand() % 20) - 9));
	}
	_dead = false;
}

Worm::Worm(std::vector<std::pair<int, int>> newDNA)
{
	_DNA = newDNA;
	_Position = std::make_pair(500, 500);
	_currChromosome = 0;
	_WormLength = 10;
	_desiredPos = std::make_pair(desired_x, desired_y);
	_dead = false;
}

Worm::~Worm()
{}

void Worm::update()
{
	double distToTarget = getDistance(_desiredPos, _Position);
	bool nothitSide = _Position.first > 0 && _Position.first < 1000 && _Position.second > 0 && _Position.second < 1000;
	bool hitTarget = distToTarget <= 1;
	if(_DNA.size() > _currChromosome && !hitTarget && distToTarget >= 1 && nothitSide)
	{
		_Velocity.first += _DNA[_currChromosome].first / 10.0;
		_Velocity.second += _DNA[_currChromosome].second / 10.0;
		_Position.first += _Velocity.first;
		_Position.second += _Velocity.second;
	}
	else
	{
		setPMetric(distToTarget, hitTarget);
	}

	if (_DNA.size() < _currChromosome)
	{
		_dead = true;
	}

	_currChromosome += 1;
}


std::vector<std::pair<int, int>> Worm::getDNA()
{
	return _DNA;
}

std::pair<double, double> Worm::getPosition()
{
	return _Position;
}

std::pair<double, double> Worm::getVelocity()
{
	return _Velocity;
}

double Worm::getPMetric()
{
	return _ProficiencyMetric;
}

void Worm::drawWorm()
{
	glLineWidth(2);
	glColor3f(1, 0, 0);
	double angle = atan2(_Velocity.first, _Velocity.second) - (3.14*0.5);
	double wOffset = sin(angle) * _WormLength / 2.0;
	double hOffset = cos(angle) * _WormLength / 2.0;
	glBegin(GL_LINE_LOOP);
	glVertex2f(_Position.first - wOffset, _Position.second + hOffset);
	glVertex2f(_Position.first + wOffset, _Position.second - hOffset);
	glEnd();
}

void Worm::setPMetric(double dist, bool hitTarget)
{
	_ProficiencyMetric = 100 / dist;
	if (hitTarget)
	{
		_ProficiencyMetric *= num_Chromosomes*2/_currChromosome;
	}
}

double Worm::getDistance(std::pair<double, double> P1, std::pair<double, double> P2)
{
	return sqrt((P1.first - P2.first)*(P1.first - P2.first) + (P1.second - P2.second)*(P1.second - P2.second));
}

bool Worm::isDead()
{
	return _dead;
}

std::vector<std::pair<int, int>> Worm::Mate(Worm mate)
{
	int random_iter = rand() % num_Chromosomes;

	std::vector<std::pair<int, int>> temp;
	std::vector<std::pair<int, int>> mateDNA = mate.getDNA();

	temp.insert(temp.end(), _DNA.begin(), _DNA.begin()+random_iter);
	temp.insert(temp.end(), mateDNA.begin()+ random_iter, mateDNA.end());

	return temp;
}

void Worm:: mutate()
{
	for (int i = 0; i < _DNA.size(); i++)
	{
		if ((rand() % 100) < 5)
		{
			_DNA[i] = std::make_pair((rand() % 20) - 9, (rand() % 20) - 9);
		}
	}
}

