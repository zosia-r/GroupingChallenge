#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, double crossProb, double mutProb, CGroupingEvaluator& evaluator, int iterLim)
	: crossProb(crossProb), mutProb(mutProb), evaluator(evaluator), iterLim(iterLim), bestIndividual(0, 0, generator)
{
	random_device seed;
	generator.seed(seed());

	if (popSize % 2 != 0)
	{
		this->popSize = popSize + 1;
	}
	else
	{
		this->popSize = popSize;
	}

	population.reserve(popSize);

	for (int i = 0; i < popSize; i++)
	{
		population.push_back(Individual(evaluator.iGetNumberOfPoints(), evaluator.iGetUpperBound(), generator));
		population[i].evaluateFitness(evaluator);
	}
	bestIndividual = population[0];
	findBestIndividual();
}

void GeneticAlgorithm::run()
{
	for (int i = 0; i < iterLim; i++)
	{
		vector<Individual> newPopulation;
		cout << "Iteration " << i << ": best fitness = " << bestIndividual.getFitness() << endl;
		for (int j = 0; j < popSize / 2; j++)
		{
			Individual& parent1 = tournamentSelection();
			Individual& parent2 = tournamentSelection();
			pair<Individual, Individual> children = parent1.crossover(parent2, crossProb);
			children.first.mutate(mutProb);
			children.second.mutate(mutProb);
			newPopulation.push_back(children.first);
			newPopulation.push_back(children.second);
		}
		population = newPopulation;
		findBestIndividual();
	}
}

void GeneticAlgorithm::findBestIndividual()
{
	for (int i = 0; i < popSize; i++)
	{
		population[i].evaluateFitness(evaluator);
		if (population[i].getFitness() < bestIndividual.getFitness())
		{
			bestIndividual = population[i];
		}
	}
}

Individual& GeneticAlgorithm::tournamentSelection()
{
	uniform_int_distribution<int> distribution(0, popSize - 1);
	int index1;
	int index2;
	index1 = distribution(generator);
	index2 = distribution(generator);
	
	if (population[index1].getFitness() < population[index2].getFitness())
	{
		return population[index1];
	}
	
	return population[index2];
}

