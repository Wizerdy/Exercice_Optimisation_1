#pragma once
#include "Vector.h"
#include "Sprite.h"
#include <iostream>
#include <map>

class Particule
{
private:
	static std::unique_ptr<std::map<std::string, Sprite*>> _spritesLibrary;
	/*static int totCount;
	int index;*/

public:
	Vector* _position;
	Vector* _force;

	Sprite* sprite;
	int vie;
	int taille;

	int vieActuelle;

	const float GRAVITE = 980;

	Particule(SDL_Renderer* renderer, std::string _modele, std::string _couleur, int vie, const Vector& position, const Vector& _force, int taille);
	~Particule();

	Particule* Init(SDL_Renderer* renderer, std::string _modele, std::string _couleur, int vie, const Vector& position, const Vector& _force, int taille);

	void Update(int deltaTime);

	void Render(SDL_Renderer* screenRenderer);

	bool EstVivante();
};

