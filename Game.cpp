#include "pch.h"
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "Population.h"


Game::Game(const Window& window)
	:m_Window{ window }

{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	// Create a population with a target phrase, mutation rate, and population max
	setup();
	m_pText = new Texture("Test", "Resources/DOTMATRI.TTF", 25, Color4f{ 1,1,1,1 });
	//m_upText = std::make_unique<Texture>("Unique ptr Text", "Resources/DOTMATRI.TTF", 25, Color4f{ 1,1,1,1 });
}

void Game::Cleanup()
{
	delete m_pText;
	
}

void Game::Update(float elapsedSec)
{
	if (!m_Population->IsFinished())
	{
		m_Population->NaturalSelection();
		m_Population->Generate();
		m_Population->CalcFitness();
		std::string answer{ m_Population->GetBest() };

		std::cout << answer << "\n";
		m_Population->Evaluate();
	}

	m_upToBe = std::make_unique<Texture>(m_Population->GetBest(),"Resources/DOTMATRI.TTF", 40, Color4f{ 1,1,1,1 });
	m_upGenerations = std::make_unique<Texture>("Generations: " + std::to_string(m_Population->GetGenerations()),"Resources/DOTMATRI.TTF", 25, Color4f{ 1,1,1,1 });
	m_upMutationRate = std::make_unique<Texture>("Average Fitness: " + std::to_string(m_Population->GetAverageFitness()),"Resources/DOTMATRI.TTF", 25, Color4f{ 1,1,1,1 });
	m_upPopSize = std::make_unique<Texture>("Max Population: " + std::to_string(m_PopMax),"Resources/DOTMATRI.TTF", 25, Color4f{ 1,1,1,1 });
	}

void Game::Draw() const
{
	ClearBackground();
	m_upToBe->Draw( Point2f{(m_Window.width / 2) - m_upToBe->GetWidth()/2,m_Window.height/2 - m_upToBe->GetHeight()/2});
	m_upGenerations->Draw(Point2f{(m_Window.width / 2) - m_upToBe->GetWidth()/2,m_Window.height/2 - m_upToBe->GetHeight()/2 - m_upGenerations->GetHeight() - 20});
	m_upMutationRate->Draw(Point2f{(m_Window.width / 2) - m_upToBe->GetWidth()/2,m_Window.height/2 - m_upToBe->GetHeight()/2 + m_upMutationRate->GetHeight()+25});
	m_upPopSize->Draw(Point2f{(m_Window.width / 2) - m_upToBe->GetWidth()/2,m_Window.height/2 - m_upToBe->GetHeight()/2 - m_upGenerations->GetHeight() - m_upPopSize->GetHeight() - 20});
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground() const
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Game::setup()
{
	m_TargetPhrase = "To be or not to be";
	m_PopMax = 400;
	m_MutationRate = 0.03f;
	m_Population = std::make_unique<Population>( m_TargetPhrase,m_MutationRate,m_PopMax );
}

void Game::displayInfo()
{
}


