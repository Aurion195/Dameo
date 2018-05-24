#ifndef DEF_JOUEUR_HUMAIN_H
#define DEF_JOUEUR_HUMAIN_H

#include "string"

class Joueur_humain
{
	std::string nom_joueur ;
	std::string pion ;
	std::string color ;
	int nb_pion ;
	bool ia ;

	public:
		Joueur_humain(std::string nom, std::string p, int nb, bool a, std::string color) ;
		void afficherJoueur() ;
		std::string getNom() ;
		std::string getPion() ;
		int getNbPion() ;
		void perdPion() ;
		void setPion(int nb) ;
		void gagnePion() ;
		bool getIa() ;
		std::string getColor() ;
} ;
#endif
