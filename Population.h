#pragma once
//One big array of N elements of DNA
#include <vector>
class DNA;
class Population final
{
public:
	explicit Population(const std::string& targetPhrase,const float mutationRate,const int populationSize);
	~Population();

	// Calculate the fitness for all elements in the population
	void CalcFitness();

	// Generate a mating pool
	void NaturalSelection();

	// Create a new generation
	void Generate();

	DNA* AcceptReject(const float maxFitness);

	std::string GetBest();

	// Find the current fittest member of the population
	void Evaluate();

	bool IsFinished() const;

	int GetGenerations() const;

	// Compute the average fitness over the whole population
	float GetAverageFitness() const;

	std::string AllPhrases() const;

private:
	std::vector<DNA*> m_Population;
	//std::vector<DNA*> m_MatingPool;
	int  m_Generations;
	bool m_Finished;
	std::string m_Target;
	float m_MutationRate;
	float m_PerfectScore;
	std::string m_Best;
};