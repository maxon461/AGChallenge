#pragma once
#include <vector>
#include <random>
#include "Evaluator.h"

class CIndividual
{
private:
	std::vector<int> solution;
	CLFLnetEvaluator &cEvaluator;
	double fitness;
	//TODO bool Evaluated;

	void randomFill(std::vector<int>& solution);
public:

	CIndividual(CLFLnetEvaluator& cEvaluator) : cEvaluator(cEvaluator) , fitness(0.0){
		randomFill(solution);
	}

	CIndividual(CLFLnetEvaluator& cEvaluator, std::vector<int> &solution) : cEvaluator(cEvaluator) , solution(solution),  fitness(0.0) {}

	~CIndividual() {
		solution.clear();
	}

	std::pair<CIndividual*, CIndividual*> cross(CIndividual* parent2, double crossProb);

	std::vector<int>* getSolution();

	double evaluateFitness();

	void mutate(double mutProb);

};

