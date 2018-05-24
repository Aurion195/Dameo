#include "Plateau_jeu.cpp"

#include <iostream>
#include <fstream>

using namespace std ;

/**
 * Fonction qui va initialiser la taille du plateau, elle ne peut recevoir qu'un int
 * du coup si jamais il reçoit un string, on fait un try & catch
 */
int initialisationPlateau()
{
		bool acceptable = true ;
		int taille = 0 ;

		string t_dec = "" ;                           //Le choix de la taille
		string::size_type sz = 0 ;                    //La ou on va stocker les erreurs

		do {

			cout << "Entrer une valeur comprise entre 6 et 16, pair : " ; cin >> t_dec ;

			try {
				taille = stoi(t_dec,&sz) ;
				if(t_dec.substr(sz) != "")  cout << "Pas la bonne valeur !" << endl ;
			}
			catch(const std::exception &e) {
				taille = 0 ;
				cout << "Erreur." << endl ;
			}

		} while(taille < 6 || taille > 16 || t_dec.substr(sz) != "" || (taille%2) != 0) ;

		return taille ;
}

/**
 * Menu de démarage du jeu
 */
int messageBienvenu()
{
	string choix = "";

	do {
		system("clear") ;

		cout << "------------------------------------------" << endl ;
		cout << " Bienvenu dans le jeu Dameo    " << endl ;
		cout << " Soyez sans pitié avec vos adversaire ! " << endl ;
		cout << "Que voulez-vous faire ? : " << endl ;
		cout << "1. Nouvelle Partie " << endl ;
		cout << "2. Charger Partie " << endl ;
		cout << "3. Règle du jeu" << endl ;
		cout << "4. Quitter" << endl ;
		cin >> choix ;
	} while(choix != "1" && choix != "2" && choix != "3" && choix != "4") ;

	return(choix == "1" ? 1 : choix == "2" ? 2 : choix == "3" ? 3 : 4) ;
}

/**
 * Permet de choisir la profondeur de l'IA en fonction du niveau de difficulté voulu
 * Cette fonction est appellé uniquement si au-moins l'un des deux joueurs est une 
 * IA, sinon elle ne s'active pas
 * Les niveau de profondeur ont été choisi par l'auteur du projet
 */
int choixProfondeur()
{
	string choix = "" ;

	do {
		cout << "Veuillez choisir un niveau de dificulté pour votre IA :" << endl ;
		cout << "1. Facile" << endl << "2. Moyen" << endl << "3. Difficile" << endl ;
		cin >> choix ;
	} while(choix != "1" && choix != "2" && choix != "3") ;

	return(choix == "1" ? 2 : choix == "2" ? 3 : 4) ;
}

/**
 * Demande si le jeu veut être sauvegardé ou pas.
 */
bool sauvegarde()
{
	string dec = "" ;

	do
	{
		cout << "Voullez-vous sauvegarder ? O/n   " ;
		cin >> dec ;
	} while(dec != "O" && dec != "n") ;

	return(dec == "O" ? true : false) ;
}

/**
 * Permet la sauvegarde du jeu, ne prend que les joueurs ainsi que le plateau
 * à chaque fois que le joueur veut sauvegarder, la fonction va écraser les
 * données contenus dans le fichier texte et envoi les nouvelles données dedans
 */
bool sauvegardePlateau(Plateau_Jeu& Dameo, string S, int profondeur)
{
	string ** tab = Dameo.getPlateau() ;
	vector <Joueur_humain*> zob = Dameo.getJoueur() ;

		ofstream fichier(S, ios::out | ios::trunc) ;

		if(fichier)
		{
			fichier << Dameo.getTaille() << "\n" << zob[0]->getNom() << "\n" << zob[0]->getPion() << "\n" << zob[0]->getNbPion() << "\n" << zob[0]->getIa() << "\n" << zob[0]->getColor() << endl ;
			fichier << zob[1]->getNom() << "\n" << zob[1]->getPion() << "\n" << zob[1]->getNbPion() << "\n" << zob[1]->getIa()  << "\n" << zob[1]->getColor() << endl ;
			fichier << profondeur << endl ;
			
			for(int i = 0 ; i < Dameo.getTaille() ; i++)
			{
				for(int j = 0 ; j < Dameo.getTaille() ; j++)
				{
					fichier << tab[i][j] << " " ;
				}
				fichier << endl ;
			}

			fichier.close() ;
		}
		else
		{
			cout << "Pas de fichier existant" << endl ;
		}

		return true ;
}

/**
 * Permet de choisir le pion que l'on veut
 */
void choixPion(int& x1, int& y1, string p1)
{
	cout << "Entrer le pion que vous voulez deplacer : " ;
	cin >> x1 ;
	cin >> y1 ;
}

/**
 * Cette fonction va calculer les coups, les mets dans un vector de vector de int,
 * affiche le vector, et demande à l'utilisateur de saisir le vector de coup qu'il
 * veut jouer.
 */
void choixDeplacementPion(Plateau_Jeu& Dameo, bool J1)
{
	bool dame = false ;
	bool mangerPion = false ;
	int x1, x2, y1, y2, a, b, min, max, t, N ; 
	t = min = x1 = x2 = y1 = y2 = a = b = 0 ;
	N = Dameo.getTaille() ;
	vector<Joueur_humain*> x = Dameo.getJoueur() ;
	vector<vector<int>> tmp ;


	tmp = Dameo.coupPossible(J1,mangerPion) ;

	Dameo.affiche(tmp) ;
	max = tmp.size()-1 ;
	string t_dec = "" ;
	string::size_type sz = 0 ;

	do {
		cout << "Entrer la valeur de déplacement : " ; cin >> t_dec ;

		try {
			a = stoi(t_dec,&sz) ;
			if(t_dec.substr(sz) != "")  cout << "Erreur." << endl ;
		}
		catch(const std::exception &e) {
			a = 0 ;
			cout << "Erreur." << endl ;
		}
	} while(a < min || a > max || t_dec.substr(sz) != "") ;

	do {
		x1 = tmp[a][t] ;
		t++ ;
		y1 = tmp[a][t] ;
		t++ ;
		x2 = tmp[a][t] ;
		t++ ;
		y2 = tmp[a][t] ;
		t++ ;

		if(J1)
		{
			if(x1 == N-1) dame = true ;
		}
		else
		{
			if(x1 == 0) dame = true ;
		}

		Dameo.deplacementJoueur(x1, x2, y1, y2, mangerPion, J1,dame) ;
	} while(t < tmp[a].size()) ;
}