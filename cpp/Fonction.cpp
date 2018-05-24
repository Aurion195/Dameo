#include "Fonction_plateau.cpp"

#include <iostream>

using namespace std ;

bool Jeu(Plateau_Jeu& Dameo, Joueur_humain& joueur1, Joueur_humain& joueur2, string S, int x)
{
	system("clear") ;
	bool gagne = false ;
	bool mangerPion = false ;
	bool J1 ;
	int maxI, nbPion, profondeur, alpha, beta ;
	maxI = nbPion = 0 ;
	profondeur = x ;
	
	while(!gagne)
	{
		J1 = true ;
		bool c = Dameo.verifyDame() ;
		vector<Joueur_humain*> x = Dameo.getJoueur() ;
		Dameo.afficherPlateau() ;

		if(x[0]->getIa())
		{
			vector<vector<int>> tmp = Dameo.coupPossible(true, mangerPion) ;
			Dameo.minMax(J1,profondeur,maxI) ;
			cout << maxI << endl ;
			int n = tmp[maxI].size() ;
			int t = 0 ;
			do {
				int x1 = tmp[maxI][t] ;
				t++ ;
				int y1 = tmp[maxI][t] ;
				t++ ;
				int x2 = tmp[maxI][t] ;
				t++ ;
				int y2 = tmp[maxI][t] ;
				t++ ;

				Dameo.deplacementJoueur(x1, x2, y1, y2, mangerPion, J1,true) ;

			} while(t < n) ;
		}
		else
		{
			choixDeplacementPion(Dameo, true) ;
		}

		maxI = 0 ;
		J1 = false ;
		mangerPion = false ;
		Dameo.afficherPlateau() ;
		c = Dameo.verifyDame() ;

		if(x[1]->getIa())
		{
			vector<vector<int>> tmp = Dameo.coupPossible(false, mangerPion) ;
			Dameo.minMax(J1,profondeur,maxI) ;
			int n = tmp[maxI].size() ;
			int t = 0 ;

			do {
				int x1 = tmp[maxI][t] ;
				t++ ;
				int y1 = tmp[maxI][t] ;
				t++ ;
				int x2 = tmp[maxI][t] ;
				t++ ;
				int y2 = tmp[maxI][t] ;
				t++ ;

			 Dameo.deplacementJoueur(x1, x2, y1, y2, mangerPion, J1,true) ;
			}while(t < n) ;
		}
		else
		{
			choixDeplacementPion(Dameo,false) ;
		}


		if(sauvegarde())
		{
			sauvegardePlateau(Dameo, S, profondeur) ;
			cout << "Le jeu à été sauvegardé !" << endl ;
			if(quitter())  break ;
		}
		else
		{
			cout << "Pensez à sauvegarder de temps en temps ;)" << endl ;
		}
				
		gagne = Dameo.gagnePlateau() ;
		
		if(gagne)
		{
			if(joueur1.getNbPion() == 0) cout << "Le joueur 2 " << joueur2.getNom() << " à gagner ! Gloire et honneur !!!!" << endl ;
			else if(joueur2.getNbPion() == 0) cout << "Le joueur 1 " << joueur1.getNom() << " à gagner ! Gloire et honneur !!!!" << endl ;
			else
			{
				cout << "Egalité !" << endl ;
			}
		}
	}

	return gagne ;
}