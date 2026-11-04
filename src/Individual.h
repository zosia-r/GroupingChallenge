#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "GroupingEvaluator.h"

#include <random>

using namespace NGroupingChallenge;

class Individual
{
public:
	Individual(int genotypeSize, int maxGen,  mt19937& generator);

	Individual(const Individual& other);
	Individual& operator=(const Individual& other);

	Individual(Individual&& other) noexcept;
	Individual& operator=(Individual&& other) noexcept;

	~Individual() = default;

	void evaluateFitness(CGroupingEvaluator& evaluator);
	std::vector<int>& mutate(double mutProb);
	std::pair<Individual, Individual> crossover(const Individual& other, double crossProb) const;

	const std::vector<int>& getGenotype() const { return genotype; }
	int getGenotypeSize() const { return genotypeSize; }
	double getFitness() const { return fitness; }

private:
	std::vector<int> genotype;
	int genotypeSize;
	int maxGen;

	double fitness;

	mt19937& generator;

	double getRandomProb() const;
};

#endif