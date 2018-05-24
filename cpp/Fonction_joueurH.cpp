#include "Liste_pion.cpp"

#include <iostream>
#include <string>

using namespace std ;

/**
 * Choisi le nom du joueur, elle est utile dans pour le constructeur du joueur
 */
string choixNom()
{
	bool correct = false ;
	string c = "" ;
	string nom = "" ;

	do {
			cout << "Entrer le nom de votre champion : " ; cin >> nom ;
			cout << "Vous avez choisi : " << nom << endl ;
			cout << "Ce choix vous convient-il ? O/n : " ; cin >> c ;
			if(c == "O") correct = true ;
	} while(!correct) ;

	return nom ;
}

/**
 * Utiliser la fonction choisirPion() de la classe Liste_pion, elle va afficher
 * la liste de pion et va le stocker dans un string
 */
string choixPion(Liste_pion& P)
{
	string x = P.choisirPion() ;

	return x ;
}

/**
 * Cette fonction, va calculer le nombre de pion en fonction de la taille du 
 * plateau choisi préalablement
 */
int choixNbPion(int taille_plateau)
{
	int nb = 0 ;

	while(taille_plateau >= 4)
	{
		nb += taille_plateau ;
		taille_plateau -= 2 ;
	}

	return nb ;
}

/**
 * Si le joueur est une IA ou non.
 */
bool choixIa()
{
	string choix ;
	do {
		cout << "Le joueur est-il une IA   O/n" << endl ;
		cin >> choix ;
	} while(choix != "O" && choix != "n") ;

	return(choix == "O" ? true : false) ;
}

/**
 * Permet de quitter le jeu de manière normale
 */
bool quitter()
{
	string quitte = " " ;

	do {
		cout << "Vouller vous quitter le jeu ? O/n" << endl ;
		cin >> quitte ;
	} while(quitte != "O" && quitte != "n") ;
	return(quitte == "O" ? true : false) ;
}

/**
 * Permet de choisir le joueur qui commence, sachant que le joueur 1 
 * est fortement avantagé par rapport à l'autre
 */
bool quiCommence()
{
	string debut = "" ;

	do 
	{
		cout << "Quel joueur commence ? 1/2" ; cin >> debut ;
	} while(debut != "1" && debut != "2") ;

	return(debut == "1" ? true : false) ;
}

/**
 * Permet de choisir la couleur que la personne veut pour ses pions
 */
string choixColor()
{
	string choix = "" ;

	do {
		cout << "1. Blue" << endl << "2. Jaune" << endl << "3. Verte " << endl << "4. Magenta" << endl ;
		cin >> choix ;
	} while(choix != "1" && choix != "2" && choix != "3" && choix != "4") ;

	return(choix == "1" ? "\033[34m" : choix == "2" ? "\033[33m" : choix == "3" ? "\033[32m" : "\033[35m") ;
}
