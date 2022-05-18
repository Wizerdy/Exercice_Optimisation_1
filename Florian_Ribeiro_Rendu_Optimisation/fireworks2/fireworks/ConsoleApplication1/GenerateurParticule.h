#pragma once

#include <queue>

#include "Particule.h"
#include "Vector.h"
#include "Pool.h"


class GenerateurParticule {
private:
	std::vector<Particule*> _liste;
	std::queue<Particule*> _particlePool;
	int _currentLength;
	int _nbParticulesMax;
	int _nbParticulesRestantes;
	std::string _modele;
	std::string _couleur;
	SDL_Renderer* _screenRenderer;

	// Particles
	Vector* _position;
	int _vieMin;
	int _vieMax;
	int _tailleMin;
	int _tailleMax;
	int _force;
	int _angleMax;

	Vector* _tempVector;

public:
	GenerateurParticule();
	~GenerateurParticule();

	void Init(SDL_Renderer* screenRenderer, int nbParticulesDebut, int nbParticulesMax, int nbParticulesTotal, std::string modele, std::string couleur,
		int vieMin, int vieMax, const Vector& position, int tailleMin, int tailleMax, int force, int angleMax);

	bool EstActif();

	void AjouterParticule();

	void Update(int deltaTime);

	int GetNbParticulesActives();

	void Render(SDL_Renderer* screenRenderer);

	std::string State();
};

