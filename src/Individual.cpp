#include "Individual.h"

Individual::Individual(int genotypeSize, int maxGen, mt19937& generator)
	: genotypeSize(genotypeSize), maxGen(maxGen), fitness(-1.0), generator(generator)
{
	uniform_int_distribution<int> distribution(1, maxGen);
	for (int i = 0; i < genotypeSize; i++)
	{
		genotype.push_back(distribution(generator));
	}
}

Individual::Individual(const Individual& other)
	: genotype(other.genotype), genotypeSize(other.genotypeSize), maxGen(other.maxGen), fitness(other.fitness), generator(other.generator)
{

}

Individual& Individual::operator=(const Individual& other)
{
	if (this != &other)
	{
		this->genotypeSize = other.genotypeSize;
		this->genotype = other.genotype;
		this->maxGen = other.maxGen;
		this->fitness = other.fitness;
		this->generator = other.generator;
	}
	return *this;
}

Individual::Individual(Individual&& other) noexcept
	: genotype(other.genotype), genotypeSize(other.genotypeSize), maxGen(other.maxGen), fitness(other.fitness), generator(other.generator)
{
	other.genotype.clear();
	other.genotypeSize = 0;
	other.maxGen = 0;
	other.fitness = 0.0;
}

Individual& Individual::operator=(Individual&& other) noexcept
{
	if (this != &other)
	{
		this->genotypeSize = other.genotypeSize;
		this->genotype = other.genotype;
		this->fitness = other.fitness;
		this->maxGen = other.maxGen;
		this->generator = other.generator;

		other.genotype.clear();
		other.genotypeSize = 0;
		other.fitness = 0.0;
		other.maxGen = 0;
	}
	return *this;
}

double Individual::getRandomProb() const
{
	uniform_real_distribution<double> distribution(0.0, 1.0);
	return distribution(generator);
}

void Individual::evaluateFitness(CGroupingEvaluator& evaluator)
{
	fitness = evaluator.dEvaluate(genotype);
}

std::vector<int>& Individual::mutate(double mutProb)
{
	uniform_int_distribution<int> distribution(1, maxGen);
	for (int i = 0; i < genotypeSize; i++)
	{
		if (getRandomProb() < mutProb)
		{
			genotype[i] = distribution(generator);
		}
	}

	return genotype;
}

std::pair<Individual, Individual> Individual::crossover(const Individual& other, double crossProb) const
{
	if (getRandomProb() > crossProb)
	{
		return std::make_pair(*this, other);
	}

	Individual child1(genotypeSize, maxGen, generator);
	Individual child2(genotypeSize, maxGen, generator);

	uniform_int_distribution<int> distribution(0, genotypeSize - 1);
	int crossPoint = distribution(generator);

	for (int i = 0; i < crossPoint; i++)
	{
		child1.genotype[i] = genotype[i];
		child2.genotype[i] = other.genotype[i];
	}
	for (int i = crossPoint; i < genotypeSize; i++)
	{
		child1.genotype[i] = other.genotype[i];
		child2.genotype[i] = genotype[i];
	}

	return std::make_pair(child1, child2);
}

