#include "Fonction.cpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>


using namespace std ;

int main()
{
		int profondeur = 0 ;
		debut : 
		int choix = messageBienvenu() ;
		bool continu = true ;

		if(choix == 1)
		{
			int N = initialisationPlateau() ;

			string TableauChoix_pion[5] = {"x","o","t","q","l"} ;
			Liste_pion P(TableauChoix_pion, 5) ;

			Joueur_humain joueur1 = creerJoueur(P, N);
			Joueur_humain joueur2 = creerJoueur2(P, N, joueur1);

			Plateau_Jeu Dameo(N, &joueur1, &joueur2) ;

			if(joueur1.getIa() || joueur2.getIa()) profondeur = choixProfondeur() ;

			if(quiCommence()) Dameo.modifie(&joueur1, &joueur2) ;
			else
			{
				Dameo.modifie(&joueur2, &joueur1) ;
			}

			Dameo.remplirPlateau() ;

			string S = "Sauvegarde/" ;
			S = S + joueur1.getNom() + "." + joueur2.getNom() ;
			S = S +".txt" ;

			ofstream fichier(S.c_str(), ios::out) ;

			if(fichier)
			{ 
				if(sauvegarde())
				{
					sauvegardePlateau(Dameo, S, profondeur)  ;

					fichier.close() ;
				}
			}
			else
			{
				cout << "Pas de fichier existant" << endl ;
			}

			Jeu(Dameo, joueur1, joueur2, S, profondeur) ;
		}
		else if(choix == 2)
		{
			int N = 0 ;
			string nom, nom2, pion, pion2, color, color2 ;
			bool ia, ia2 ;
			int nb, nb2, profondeur ;

			string S = "Sauvegarde/" ;
			string tmp = "" ;
			system("ls Sauvegarde") ;
			cout << "Marquer la sauvegarde que vous-voullez : " ; cin >> tmp ;
			S = S + tmp ;

			ifstream fichier(S.c_str(), ios::in) ;

			if(fichier)
			{
				fichier >> N >> nom >> pion >> nb >> ia >> color >> nom2 >> pion2 >> nb2 >> ia2 >> color2 >> profondeur ;

				Joueur_humain joueur1(nom, pion, nb, ia, color) ;
				Joueur_humain joueur2(nom2, pion2, nb2, ia2, color2) ;

				Plateau_Jeu Dameo(N, &joueur1, &joueur2) ;

				string x ;
			
				for(int i = 0; i < N; i++) 
				{
					for(int j = 0; j < N; j++) 
					{
						fichier >> x;
						Dameo.remplirPlateauSauvegardePlateau(x, i, j) ;
					}
				}

				fichier.close() ;

				Jeu(Dameo, joueur1, joueur2, S, profondeur) ;

			}
			else
			{
				cout << "Pas de fichier existantyeyjyj !" << endl ;
				goto debut ;
			}
		}
		else if(choix == 3)
		{
			system("evince ../Regle/Regle.pdf") ;
			goto debut ;
		}
		else
		{
			cout << "Merci et a bientôt !" << endl ;
		}
		
		return 0 ;
}
