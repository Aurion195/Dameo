#include "../h/Joueur_humain.h"
#include "Fonction_joueurH.cpp"

#include <iostream>

using namespace std ;

/**
 * Constructeur du joueur humain, qui va prendre en argument,
 * son nom, le pion, le nombre de pion, si c'est un ia, 
 * la couleur qu'il veut
 */
Joueur_humain::Joueur_humain(string nom, string p, int nb, bool ia, string color)
{
	this->nom_joueur = nom ;
	this->pion = p ;
	this->nb_pion = nb ;
	this->ia = ia ;
	this->color = color ;
}

/**
 * Affiche le joueur
 */
void Joueur_humain::afficherJoueur() 
{
	cout << "Nom : " << nom_joueur << endl ;
	cout << "Pion : " << pion << endl ;
	cout << "Nombre pion : " << nb_pion << endl ;
	cout << "IA : " << ia << endl ;
	cout << endl << endl  ;
}

/**
 * Cette fonction va créer un joueur en fonction du joueur
 * qu'il reçoit en argument
 */
Joueur_humain creerJoueur2(Liste_pion& P, int N, Joueur_humain& j)
{
	string nom_joueur = choixNom() ;
	string p2, color ;
	string c = j.getColor() ;
	string x = j.getPion() ;
	bool meme = true ;

	while(meme)
	{
		p2 = choixPion(P) ;
		if(p2 != x)
		{
			meme = false ;
		}
	}

	meme = true ;

	while(meme)
	{
		color = choixColor() ;

		if(c != color) meme = false ; 
	}

	int nb = choixNbPion(N) ;
	bool ia = choixIa() ;

	Joueur_humain y(nom_joueur, p2, nb, ia, color) ;
	return y ;
}

/**
 * Quand un joueur se fait manger un pion, le vector "mesJoueur"
 * dans lequel sont les 2 objet joueur, vont faire appel à cette fonction
 * afin de pouvoir perdre un pion
 */
void Joueur_humain::perdPion()
{
	nb_pion -= 1 ;
}

/**
 * Même principe que quand il perd un pion.
 */
void Joueur_humain::gagnePion()
{
	nb_pion += 1  ;
}

/**
 * Les fonctions suivante, sont les getteur et les setteur de la classe joueur
 * elles vont permettre d'accéder au données privée de la classe ou bien de 
 * les modifiers comme on l'entend
 */

string Joueur_humain::getPion()
{
	return pion ;
}


int Joueur_humain::getNbPion()
{
	return nb_pion ;
}


string Joueur_humain::getNom()
{
	return nom_joueur ;
}

bool Joueur_humain::getIa()
{
	return ia ;
}

void Joueur_humain::setPion(int nb)
{
	nb_pion = nb ;
}

string Joueur_humain::getColor()
{
	return color ;
}

Joueur_humain creerJoueur(Liste_pion& P, int N)
{
	string nom_joueur = choixNom() ;
	string y = choixPion(P) ;
	int nb = choixNbPion(N) ;
	bool ia = choixIa() ;
	string color = choixColor() ;
	Joueur_humain p(nom_joueur, y, nb, ia, color) ;
	return p ;
}