#include "GaussianGroupingEvaluatorFactory.h"
#include "GroupingEvaluator.h"
#include "GeneticAlgorithm.h"

#include <iostream>

using namespace NGroupingChallenge;

int main()
{
	CGaussianGroupingEvaluatorFactory evaluatorFactory(5, 100, 5);

	evaluatorFactory
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0);

	CGroupingEvaluator* evaluator = evaluatorFactory.pcCreateEvaluator(0);


	int popSize = 1000;
	double crossProb = 0.8;
	double mutProb = 0.017;
	int iterLim = 1000;

	GeneticAlgorithm ga(popSize, crossProb, mutProb, *evaluator, iterLim);
	
	ga.run();

	Individual bestIndividual = ga.getBestIndividual();

	std::cout << "\n\nBEST FITNESS: " << bestIndividual.getFitness() << "\n\nSOLUTION: ";

	const std::vector<int>& genotype = bestIndividual.getGenotype();

	for (int i = 0; i < genotype.size(); i++)
	{
		std::cout << "\npoint " << i << ": group " << genotype[i];
	}

	delete evaluator;

	return 0;
}