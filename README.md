## Rendu Exercice Optimisation

J'ai surtout utilisé les pool pour limiter les allocations en mémoire.

### Pool :
+ Création d'une classe template "Pool" pour pouvoir gérer les pool plus facilement
  + Echec et abandon (temps d'essai : 30min)
+ Utilisation de std::queue pour les pool (parce que c'est opti :3)
+ Création d'une pool de Particule dans la classe GenerateurParticule.
+ Création d'une pool de GenerateurParticule dans la classe Game.
+ Utilisation d'une map static dans la classe Particule pour stocker les sprites communs.
  + Cela évite de créer un sprite pour chaque particule alors qu'il existe actuellement 10 sprites différents maximun.

### Vector :
+ Limiter la création de vector.
  + Création de vectors "temporaires" dans Game et GenereateurParticule au lieu de créer à chaque fois de nouveaux vecteur quand nécessaire.
  + Fonction "Set" dans la structure Vector pour changer ses valeurs sans en créer un nouveau.
  + Surcharge d'opérateur "=" entre Vector, et constructeur par copie pour la même raison que précedemment (et confort d'écriture).
  + Passage de Vector par référence dans l'Init de la classe GenerateurParticule et Particule.
  + Suppresion de la création superflue d'un Vector dans l'update de la classe Particule et remplacement par des float pour limiter les accès mémoires.

### GenerateurParticle :
+ Rework de la fonction "GetNbParticulesActives" en gardant la taille dans une variable "\_currentLength".
+ Suprresion de la "bulle" pour faire remonter la particule quand une particule n'est plus active dans l'Update.
  + Remplacement par un simple échange entre celle-ci et la dernière particule active.
+ Suppresion de la boucle superflue pour trouver la première Particule inactive.
  + utilisation du nombre actuel de Particules actives et de "l'effet bulle".
+ Allègement du nombre de boucle pour l'attribution de _nullptr_ dans la liste de Particules.
+ Passage des variables non nécessairement Public en Private.
+ Utilisation d'un std::vector<Particle*> plutôt qu'un Particle** pour pouvoir utiliser des boucles _foreach_.

### Game :
+ Les _switch_, c'est bien.
+ Les _foreach_ aussi.
