#pragma once

class DNA final
{
public:
	explicit DNA(const int num);
	~DNA();

	// Returns m_Genes
	std::string GetPhrase() const;

	// Fitness Function (returns floating point % of "correct" characters)
	void CalcFitness(const std::string& target);

	// Crossover
	DNA* Crossover(const DNA* partner);

	// Picks a new random character based on a mutation probability
	void Mutate(const float mutationRate);

	float GetFitness() const;
private:
	std::string m_Genes; // array of characters
	float m_Fitness; // fitness score
};
