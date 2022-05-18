#pragma once
#include <SDL_render.h>
#include "GenerateurParticule.h"
#include <string>
#include <vector>
#include <queue>

class IGameEntity;

class Game
{
private:
    bool _isRunning;
    
	std::vector<GenerateurParticule*> _generateurs;
	std::queue<GenerateurParticule*> _generatorPool;
	int _modele;
	std::string _couleur;
	SDL_Renderer* _screenRenderer;

	Vector* _tempVector;

public:
	Game();
	~Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;

	bool Init(SDL_Renderer* screenRenderer);
	void Release();

	void Update(int deltaTime);

	void Render(SDL_Renderer* screenRenderer);

	bool IsRunning();

	void CreerGenerateurParticule(int posX, int posY);
};

