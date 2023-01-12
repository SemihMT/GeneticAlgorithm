#include "pch.h"
#include "Population.h"

#include <algorithm>
#include <set>

#include "DNA.h"
#include "utils.h"

Population::Population(const std::string& targetPhrase, const float mutationRate, const int populationSize) :
	m_Population{},
	//m_MatingPool{},
	m_Generations{ 0 },
	m_Finished{ false },
	m_Target{ targetPhrase },
	m_MutationRate{ mutationRate },
	m_PerfectScore{ 1.f },
	m_Best{ "" }
{
	m_Population.resize(populationSize);
	for (int i{}; i < populationSize; ++i)
	{
		m_Population[i] = new DNA(static_cast<int>(m_Target.size()));
	}
	CalcFitness();
}

Population::~Population()
{
	for(int i{}; i < m_Population.size(); ++i)
	{
		delete m_Population[i];
	}
}

void Population::CalcFitness()
{
	for (int i{}; i < m_Population.size(); ++i)
	{
		m_Population[i]->CalcFitness(m_Target);
	}
}

void Population::NaturalSelection()
{


}

void Population::Generate()
{
	float maxFitness{ 0 };

	for (int i{ 0 }; i < m_Population.size(); ++i)
	{
		if (m_Population[i]->GetFitness() > maxFitness)
			maxFitness = m_Population[i]->GetFitness();
	}


	std::vector<DNA*> newPopulation{};
	newPopulation.resize(m_Population.size());
	for (int i{ 0 }; i < m_Population.size(); ++i)
	{
		auto partnerA{ AcceptReject(maxFitness) };
		auto partnerB{ AcceptReject(maxFitness) };
		DNA* child{ partnerA->Crossover(partnerB) };
		child->Mutate(m_MutationRate);
		newPopulation[i] = child;

	}

	for(int i{}; i < m_Population.size(); ++i)
	{
		delete m_Population[i];
	}

	m_Population = newPopulation;
	++m_Generations;

}

DNA* Population::AcceptReject(const float maxFitness)
{
	int beSafe{ 0 };
	while (true)
	{
		int index{ utils::RandomInteger(0,int(m_Population.size()) - 1) };
		DNA* partner{ m_Population[index] };
		float r{ utils::RandomFloat(0,maxFitness) };
		if (r < partner->GetFitness())
		{
			return partner;
		}
		++beSafe;

		if (beSafe > 10000)
			return nullptr;
	}

	return nullptr;
}

std::string Population::GetBest()
{
	return m_Best;
}

void Population::Evaluate()
{
	float worldRecord{ 0.0f };
	int index{ 0 };

	for (int i{ 0 }; i < m_Population.size(); ++i)
	{
		if (m_Population[i]->GetFitness() > worldRecord)
		{
			index = i;
			worldRecord = m_Population[i]->GetFitness();
		}

	}

	m_Best = m_Population[index]->GetPhrase();
	if (worldRecord >= m_PerfectScore)
	{
		m_Finished = true;
	}
}

bool Population::IsFinished() const
{
	return m_Finished;
}

int Population::GetGenerations() const
{
	return m_Generations;
}

float Population::GetAverageFitness() const
{
	float total{ 0 };
	for (int i{ 0 }; i < m_Population.size(); ++i)
	{
		total += m_Population[i]->GetFitness();
	}
	return total / static_cast<float>(m_Population.size());
}

std::string Population::AllPhrases() const
{
	std::string everything{ "" };
	int displayLimit{ std::min(static_cast<int>(m_Population.size()),50) };

	for (int i{}; i < displayLimit; ++i)
	{
		everything += m_Population[i]->GetPhrase() + "\n";
	}
	return everything;
}
