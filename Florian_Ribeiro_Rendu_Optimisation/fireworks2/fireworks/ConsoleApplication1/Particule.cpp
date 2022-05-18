#include "Particule.h"
#include <iostream>
#include <SDL_image.h>

std::unique_ptr<std::map<std::string, Sprite*>> Particule::_spritesLibrary = std::make_unique<std::map<std::string, Sprite*>>(std::map<std::string, Sprite*>());

Particule::Particule(SDL_Renderer* renderer, std::string _modele, std::string _couleur, int vie, const Vector& position, const Vector& force, int taille) {
	_position = new Vector();
	_force = new Vector();
	Init(renderer, _modele, _couleur, vie, position, force, taille);
}

Particule::~Particule() {

}

Particule* Particule::Init(SDL_Renderer* renderer, std::string _modele, std::string _couleur, int vie, const Vector& _position, const Vector& _force, int taille) {
	(*this->_position) = _position;
	(*this->_force) = _force;
	this->vie = vie * 1000;
	this->vieActuelle = 0;
	this->taille = taille;

	std::string spriteName = _modele + "-" + _couleur;

	if ((*_spritesLibrary).find(spriteName) == (*_spritesLibrary).end()) {
		SDL_Texture* spriteImage = nullptr;
		SDL_Surface* loadedSurface = IMG_Load(("fireworks/" + spriteName + ".png").c_str());
		if (loadedSurface == NULL) {
			printf("Unable to load image %s! SDL_image Error: %s\n", ("fireworks/" + _modele + "-" + _couleur + ".png").c_str(), IMG_GetError());
		} else {
			spriteImage = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (spriteImage == NULL) {
				printf("Unable to create texture from %s! SDL Error: %s\n", ("fireworks/" + _modele + "-" + _couleur + ".png").c_str(), SDL_GetError());
			}

			SDL_FreeSurface(loadedSurface);
		}
		sprite = new Sprite(spriteImage);
		(*_spritesLibrary).emplace(spriteName, sprite);
	} else {
		sprite = (*_spritesLibrary).at(spriteName);
	}
	return this;
}

void Particule::Update(int deltaTime) {
	vieActuelle = vieActuelle + deltaTime;
	float x = _position->x;
	float y = _position->y;
	x = x + _force->x * deltaTime / 1000;
	y = y + _force->y * deltaTime / 1000;
	//gravité
	_force->y = _force->y + deltaTime * GRAVITE / 1000;
	//rebond
	if (y + taille / 2 >= 720) {
		y = 720 - (y - 720);
		_force->y = 0 - _force->y * 0.8;
	}
	_position->Set(x, y);
}

void Particule::Render(SDL_Renderer* screenRenderer) {
	unsigned char alpha = 0;
	if (vie > vieActuelle)
		alpha = (255 * (vie - vieActuelle)) / vie;
	sprite->Render(screenRenderer, _position->x, _position->y, taille, taille, alpha);
}

bool Particule::EstVivante() {
	if (vie > vieActuelle)
		return true;
	return false;
}
