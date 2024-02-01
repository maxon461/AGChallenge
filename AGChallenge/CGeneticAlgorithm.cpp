#include "CGeneticAlgorithm.h"

CIndividual* CGeneticAlgorithm::getBestSolution()
{
	double bestFitness = best->evaluateFitness();
	CIndividual* newBest = nullptr;
	for (size_t i = 0; i < popSize; i++)
	{
		double currFitness = population.at(i)->evaluateFitness();
		if (bestFitness < currFitness)
		{
			bestFitness = currFitness;
			newBest = population.at(i);
		}
	}

	if (newBest != nullptr)
	{
		delete best;
		best = newBest;
	}
	std::cout << best->evaluateFitness() << "\n";

    return best;
}

void CGeneticAlgorithm::vRunIteration()
{
	crossPopulation();
	mutatePopulation();
	evaluateFitnessForAll();
	//std::cout << getBestSolution()->getFitness() << "\n";
}

void CGeneticAlgorithm::crossPopulation()
{
	std::vector<CIndividual*> newPopulation;

	while (newPopulation.size() < popSize)
	{
		

		//find first parent
		CIndividual* parent1_1 = population.at(lRand(population.size()));
		CIndividual* parent1_2 = population.at(lRand(population.size()));


		CIndividual* parent1;

		if (parent1_1->evaluateFitness() > parent1_2->evaluateFitness())
			parent1 = parent1_1;
		else
			parent1 = parent1_2;



		//find second parent
		CIndividual* parent2_1 = population.at(lRand(population.size()));
		CIndividual* parent2_2 = population.at(lRand(population.size()));

		CIndividual* parent2;//TODO sep func


		{
			if (parent2_1->evaluateFitness() > parent2_2->evaluateFitness())
				parent2 = parent2_1;
			else
				parent2 = parent2_2;
		}



		
		
		//cross
		std::pair<CIndividual*, CIndividual*> pair(parent1->cross(parent2, crossProb));

		newPopulation.push_back(pair.first);
		newPopulation.push_back(pair.second);

	}



	
	
	//set new population
	for (size_t i = 0; i < population.size(); i++)
	{
		if (population.at(i) != best)  //  to not delete best solution
		{
			delete population.at(i);
		}
		
	}
	
	population = newPopulation;
}

void CGeneticAlgorithm::mutatePopulation()
{
	for (size_t i = 0; i < population.size(); i++)
		population.at(i)->mutate(mutProb);
}

void CGeneticAlgorithm::evaluateFitnessForAll()
{
	for (size_t i = 0; i < population.size(); i++)
		population.at(i)->evaluateFitness();
}
