#include "Game.h"
#include <SDL.h>
#include <iostream>
#include <SDL_scancode.h>
#include "Font.h"
#include <time.h>
#include "GenerateurParticule.h"

Game::Game() {
	_tempVector = new Vector();
	_generatorPool = std::queue<GenerateurParticule*>();
	_generateurs = std::vector<GenerateurParticule*>();
}

Game::~Game() = default;

bool Game::Init(SDL_Renderer * screenRenderer) {
	_modele = 1;
	_couleur = "blanc";
	_isRunning = true;
	_screenRenderer = screenRenderer;
	srand(time(NULL));
	return true;
}

void Game::Update(int deltaTime) {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case SDL_QUIT:
			_isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				_isRunning = false;
				break;
			case SDLK_1:
				_couleur = "blanc";
				break;
			case SDLK_2:
				_couleur = "rouge";
				break;
			case SDLK_3:
				_couleur = "vert";
				break;
			case SDLK_4:
				_couleur = "bleu";
				break;
			case SDLK_9:
				_modele = 1;
				break;
			case SDLK_0:
				_modele = 2;
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == 1) {
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				CreerGenerateurParticule(mouseX, mouseY);
			}
			break;
		default:
			break;
		}
	}

	if (_isRunning) {
		for (GenerateurParticule* generateur : _generateurs) {
			generateur->Update(deltaTime);
			if (generateur->EstActif() == false) {
				_generatorPool.push(generateur);
				_generateurs.erase(std::find(_generateurs.begin(), _generateurs.end(), generateur));
			}
		}
	}
}

void Game::Render(SDL_Renderer * screenRenderer) {
	SDL_RenderClear(screenRenderer);
	if (_isRunning) {
		for (GenerateurParticule* generateur : _generateurs) {
			generateur->Render(screenRenderer);
		}
	}
}

void Game::Release() {
	for (GenerateurParticule* generator : _generateurs) {
		delete generator;
	}
	_generateurs.clear();
	while (!_generatorPool.empty()) {
		delete _generatorPool.front();
		_generatorPool.pop();
	}
}


bool Game::IsRunning() {
	return _isRunning;
}

void Game::CreerGenerateurParticule(int posX, int posY) {
	GenerateurParticule* generateur;
	if (_generateurs.size() == 5) {
		generateur = _generateurs[0];
		_generateurs.erase(_generateurs.begin());
	} else if (_generatorPool.empty()) {
		generateur = new GenerateurParticule();
	} else {
		generateur = _generatorPool.front();
		_generatorPool.pop();
	}

	_tempVector->Set(posX, posY);
	generateur->Init(_screenRenderer, rand() % 20, 20 + rand() % 80, 500 + rand() % 2500, "particle" + std::to_string(_modele), _couleur, rand() % 5, rand() % 15, (*_tempVector), 16, 64, 100 + rand() % 500, rand() % 90);
	//generateur->Init(_screenRenderer, 50, 70, 500, "particle" + std::to_string(_modele), _couleur,  2,  2, (*_tempVector), 16, 64, 100 + rand() % 500, rand() % 90);
	_generateurs.push_back(generateur);
}
