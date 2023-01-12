#include "pch.h"
#include "DNA.h"

#include "utils.h"

//The object that stores the genotype of our "organism"
//The DNA object for the shakespeare project is also an array of n characters, representing the fenotype
//The closer this DNA object gets to the target phrase, or target in general, the better the fenotype is
//this "closeness" is numerically represented by the fitness function


DNA::DNA(const int num) :
	m_Genes{},
	m_Fitness{}
{
	m_Genes.resize(num);
	for (size_t i = 0; i < num; i++)
	{
		m_Genes[i] = utils::RandomCharacter();
	}
}

DNA::~DNA()
{
	
}

std::string DNA::GetPhrase() const
{
	return m_Genes;
}

void DNA::CalcFitness(const std::string& target)
{
	int score{ 0 };
	for (size_t i = 0; i < m_Genes.size(); i++)
	{
		if (m_Genes[i] == target[i])
		{
			++score;
		}
	}

	m_Fitness = score / static_cast<float>(target.size());
	m_Fitness = powf(m_Fitness,2) + 0.01f;
}

DNA* DNA::Crossover(const DNA* partner)
{
	DNA* child{new DNA{static_cast<int>(m_Genes.size())}};
	const int midpoint{utils::RandomInteger(0,static_cast<int>(m_Genes.size()))};
	for (size_t i = 0; i < m_Genes.size(); i++)
	{
		if(i > midpoint)
			child->m_Genes[i] = m_Genes[i];
		else
			child->m_Genes[i] = partner->m_Genes[i];
	}
	return child;
}

void DNA::Mutate(const float mutationRate)
{
	for (size_t i = 0; i < m_Genes.size(); i++)
	{
		if(utils::RandomFloat() < mutationRate)
		{
			m_Genes[i] = utils::RandomCharacter();
		}
	}
}

float DNA::GetFitness() const
{
	return m_Fitness;
}
