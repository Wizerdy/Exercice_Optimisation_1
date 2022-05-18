#include "GenerateurParticule.h"

GenerateurParticule::GenerateurParticule() {
	//printf("Gen new\n");
	_particlePool = std::queue<Particule*>();
	_tempVector = new Vector();
	_position = new Vector();
	_liste = std::vector<Particule*>();
}

GenerateurParticule::~GenerateurParticule() {
	//printf("Gen goodbye\n");
	for (Particule* particle : _liste) {
		if (particle != nullptr) {
			delete particle;
		}
	}

	while (!_particlePool.empty()) {
		delete _particlePool.front();
		_particlePool.pop();
	}

	delete _position;
	delete _tempVector;
}

void GenerateurParticule::Init(SDL_Renderer* screenRenderer, int nbParticulesDebut, int nbParticulesMax, int nbParticulesTotal, std::string modele, std::string couleur, int vieMin, int vieMax, const Vector& position, int tailleMin, int tailleMax, int force, int angleMax) {
	_screenRenderer = screenRenderer;
	_nbParticulesMax = nbParticulesMax;
	_nbParticulesRestantes = nbParticulesTotal;
	_modele = modele;
	_couleur = couleur;
	_vieMin = vieMin;
	_vieMax = vieMax;
	(*_position) = position;
	_tailleMin = tailleMin;
	_tailleMax = tailleMax;
	_force = force;
	_angleMax = angleMax;

	_currentLength = 0;

	for (Particule* particle : _liste) {
		if (particle != nullptr) {
			_particlePool.push(particle);
		}
	}

	_liste = std::vector<Particule*>(_nbParticulesMax);
	/*for (int i = 0; i < _nbParticulesMax; i++) {
		_liste[i] = nullptr;
	}*/

	for (int i = nbParticulesDebut; i < _nbParticulesMax; ++i) {
		_liste[i] = nullptr;
	}

	for (int i = 0; i < nbParticulesDebut; i++) {
		AjouterParticule();
		_nbParticulesRestantes--;
	}

}

bool GenerateurParticule::EstActif() {
	if (_nbParticulesRestantes > 0)
		return true;
	return false;
}

void GenerateurParticule::AjouterParticule() {
	//for (int i = 0; i < _nbParticulesMax; i++) {
	int nbPart = GetNbParticulesActives();
	if (nbPart < _nbParticulesMax) {
		int angle = 0;
		if (_angleMax != 0)
			angle = rand() % _angleMax;
		if (rand() % 2 == 1)
			angle = -angle;
		int vie = _vieMin;
		if (_vieMin != _vieMax)
			vie = _vieMin + rand() % (_vieMax - _vieMin);
		int taille = _tailleMin;
		if (_tailleMin != _tailleMax)
			taille = _tailleMin + rand() % (_tailleMax - _tailleMin);
		_tempVector->Set(-_force * sin(angle), _force * cos(angle));

		if (_particlePool.empty()) {
			_liste[nbPart] = new Particule(_screenRenderer, _modele, _couleur, vie, (*_position), (*_tempVector), taille);
		} else {
			_liste[nbPart] = _particlePool.front()->Init(_screenRenderer, _modele, _couleur, vie, (*_position), (*_tempVector), taille);
			_particlePool.pop();
		}

		++_currentLength;
	}
	//}
}

void GenerateurParticule::Update(int deltaTime) {
	//printf((State() + "\n").c_str());
	Particule* particule;
	int nbParticleActive = GetNbParticulesActives();
	for (int i = 0; i < _nbParticulesMax; i++) {
		particule = _liste[i];
		if (particule != nullptr) {
			particule->Update(deltaTime);
			if (particule->EstVivante() == false) {
				int lastParticle = nbParticleActive - 1;
				_liste[i] = _liste[lastParticle];
				_liste[lastParticle] = nullptr;
				_particlePool.push(particule);
				--_currentLength;
				--nbParticleActive;
			}
		}
	}
	if (nbParticleActive < _nbParticulesMax && EstActif()) {
		AjouterParticule();
		--_nbParticulesRestantes;
		++nbParticleActive;
	}
}

int GenerateurParticule::GetNbParticulesActives() {
	return _currentLength;
	/*int nb = 0;
	for (int i = 0; i < _nbParticulesMax; i++) {
		if (_liste[i] != nullptr) {
			++nb;
		}
	}
	return nb;*/
}

void GenerateurParticule::Render(SDL_Renderer* screenRenderer) {
	for (int i = 0; i < _nbParticulesMax; i++) {
		if (_liste[i] != nullptr) {
			_liste[i]->Render(screenRenderer);
		}
	}
}

std::string GenerateurParticule::State() {
	std::string output = "";
	output += "R:" + std::to_string(_nbParticulesRestantes);
	output += " M:" + std::to_string(_nbParticulesMax);
	output += " C:" + std::to_string(GetNbParticulesActives());
	return output;
}
