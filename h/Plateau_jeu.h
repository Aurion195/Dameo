#ifndef DEF_PLATEAU_JEU_H
#define DEF_PLATEAU_JEU_H

#include "Joueur_humain.h"

#include <string>
#include <vector>

class Plateau_Jeu
{
	int N ;
	std::string **Dameo ;
	std::vector<Joueur_humain*> mesJoueurs ;
	int mini ;
	int maxi ;

	public:
		/* Voici toutes les fonctions de base du plateau, qui vont permettre le jeu
		** habituel, du plateau
		*/
		Plateau_Jeu(int taille, Joueur_humain* joueur1, Joueur_humain* joueur2) ;
		~Plateau_Jeu() ;
		void ajouterJoueur(Joueur_humain* joueur) ;
		void modifie(Joueur_humain* joueur1, Joueur_humain* joueur2) ;
		void remplirPlateau() ;
		void afficherColor(int i, int j) ;
		void remplirPlateauSauvegardePlateau(std::string z, int x, int y) ;
		void afficherPlateau() ;
		void affiche(std::vector<std::vector<int>> tmp) ;
		void deplacementJoueur(int x1, int x2, int y1, int y2, bool mangerPion, bool J1,bool dame) ;
		bool mangePion(int i, int j, int a, int u, bool J1, bool dame) ;
		bool dame(int i, int j, std::string p1, std::string& mp) ;
		bool gagnePlateau() ;
		int alphaBeta(bool J1, int profondeur, int alpha, int beta) ;


		/* Voici les get et set des fonctions qui vont permettre d'avoir les variables
		** de type private, ou bien de les modifiers
		*/
		std::string **getPlateau() ;
		int getTaille() ;
		std::vector<Joueur_humain*> getJoueur() ;
		std::string** setPlateau(std::string** tab) ;


		/* Voici les fonctions necessaires à l'IA, elle va utiliser toutes les fonctions de 
		** la classe Plateau_Jeu afin de renvoyer le meilleur coup possible pour l'IA
		*/
		void dejouer(int x2, int y2, int x1, int y1, bool mangerPion, bool J1) ;
		void dejouerManger(int x2, int y2, int x1, int y1, bool J1) ;
		void minMax(bool J1, int profondeur, int& maxI) ;
		void restaure(int nb, bool J1) ;
		int min(int profondeur,bool J1) ;
		int max(int profondeur,bool J1) ;
		int evaluation(std::vector<std::vector<int>> tmp, bool mangerPion, bool J1) ;

		/* Voici les fonctions qui vont calculer tous les coups possibles pour tous les joueurs
		** elles vont permettre de donner dans un tableau de vecteur, de vecteur, de vecteur de int
		** tous les chemins possibles pour le joueur
		*/
		std::vector<std::vector<int>> coupPossible(bool J1, bool& mangePion) ;
		bool verifyDame() ;

		private:
			void sautePion(std::vector<std::vector<int>> &tmp, int x1, int y1, bool J1) ;
			void mange(std::vector<std::vector<int>>&t, int x1, int y1,bool up, bool down, bool droite, bool gauche, int& nb, int& max, bool J1, int& mange, bool& mangePion, bool dame) ;
			void deplacements(std::vector<std::vector<int>>&tmp, int x1, int y1, int& cpt, bool J1) ;
			void deplacementDame(std::vector<std::vector<int>>& tmp, int x1, int y1, bool J1) ;
			bool mangeUp(int x1, int y1, bool J1) ;
			bool mangeDown(int x1, int y1, bool J1) ;
			bool mangeLeft(int x1, int y1, bool J1) ;
			bool mangeRigth(int x1, int y1, bool J1) ;
			void ajouterCoup(std::vector<std::vector<int>>& t, int x, int y, int x1, int y1, int& nb, int& max) ;
			void compare(std::vector<std::vector<int>>& tmp, std::vector<std::vector<int>>& x, int& nb, int& max) ;
			
} ;
#endif
