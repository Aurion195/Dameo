#include "../h/Liste_pion.h"

#include <iostream>
#include <string>

using namespace std ;

/**
 * Créee une liste de pion contenant des pions dedans, si le joueur veux
 * ils pourront ajouter des pions de leurs propres choix
 */
Liste_pion::Liste_pion(string* TableauChoix_pion, int e)
{
	max = e ;
	debut = 0 ;

	tab = new string[max] ;

	int cpt = 0 ;
	for(int i = 0 ; i < max ; i++)
	{
		tab[i] = TableauChoix_pion[cpt] ;
		cpt++ ;
	}
}

/**
 * Affiche les pions avec leurs indice dessus, il faut choisir l'indice qui
 * correspond au pion que l'on veut
 */
string Liste_pion::choisirPion()
{
	bool acceptable = true ;
	int indice = 0 ;

	string t_dec = "" ;                           //Le choix de la taille
	string::size_type sz = 0 ;                    //La ou on va stocker les erreurs

		do {

			afficherPion() ;
			cout << "Entrer la valeur de votre pion  " ; cin >> t_dec ;

			try {
				indice = stoi(t_dec,&sz) ;
				if(t_dec.substr(sz) != "")  cout << "Pas la bonne valeur !" << endl ;
			}
			catch(const std::exception &e) {
				indice = 0 ;
				cout << "Erreur." << endl ;
			}

		} while(indice < 0 || indice > 5 || t_dec.substr(sz) != "") ;

	return tab[indice] ;
}

/**
 * Affiche la liste des pions
 */
void Liste_pion::afficherPion()
{
	for(int i = 0 ; i < max ; i++)
	{
		cout << i << " " ;
	}

	cout << endl ;

	for(int i = 0 ; i < max ; i++)
	{
		cout << tab[i] << " " ;
	}

	cout << endl ;
}

/**
 * Transforme en majuscule un string
 */
string majuscule(string tmp)
{
	string x = tmp ;
	x[0] = toupper(tmp[0]) ;
	return x ;
}