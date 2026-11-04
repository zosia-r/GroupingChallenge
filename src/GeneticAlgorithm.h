#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "GroupingEvaluator.h"
#include "Individual.h"

#include <iostream>

using namespace NGroupingChallenge;

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(int popSize, double crossProb, double mutProb, CGroupingEvaluator& evaluator, int iterLim);
	
	~GeneticAlgorithm() = default;

	void run();

	Individual& getBestIndividual() { return bestIndividual; }

private:
	int popSize;
	double crossProb;
	double mutProb;
	int numGroups;
	int numPoints;
	int iterLim;

	vector<Individual> population;
	Individual bestIndividual;
	CGroupingEvaluator& evaluator;
	mt19937 generator;

	void findBestIndividual();
	Individual& tournamentSelection();
};

#endif
