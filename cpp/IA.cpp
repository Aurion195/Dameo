#include "../h/Plateau_jeu.h"

#include <iostream>
#include <algorithm>

using namespace std ;

/**
 * Toutes les fonctions contenus dans ce fichier .cpp, sont des fonctions qui sont utilisé 
 * uniquement pour l'IA.
 */

int Plateau_Jeu::alphaBeta(bool J1, int profondeur, int alpha, int beta)
{
	int m, s1, s2, eval ;
	s1 = s2 = m = 0 ;
	int x1, x2, y1, y2 ;
	bool mangerPion = false ; 
	bool c = this->verifyDame() ;
	vector<vector<int>> tmp = this->coupPossible(J1,mangerPion) ;

	if (profondeur >= 0)
	{
		for(int i = 0 ; i < tmp.size() ; i++)
		{
			m = s1 = x1 = y1 = x2 = y2 = 0 ;
			int t = 0 ;

			do {
				x1 = tmp[i][t] ;
				t++ ;
				y1 = tmp[i][t] ;
				t++ ;
				x2 = tmp[i][t] ;
				t++ ;
				y2 = tmp[i][t] ;
				t++ ;

				this->deplacementJoueur(x1,x2,y1,y2,mangerPion,J1,true) ;
			} while(t < tmp[i].size()-1) ;

			//cout << x1 << y1 << "	-> " << x2 << y2 << endl ;
			int score = -alphaBeta(!J1, profondeur-1, -beta, -alpha) ;

			if(mangerPion)
			{
				t = 0 ;
				reverse(tmp[i].begin(), tmp[i].end()) ;
				do {
					y1 = tmp[i][t] ;
					t++ ;
					x1 = tmp[i][t] ;
					t++ ;
					y2 = tmp[i][t] ;
					t++ ;
					x2 = tmp[i][t] ;
					t++ ;
					this->dejouer(x2,y2,x1,y1,mangerPion,J1) ;
				} while(t < tmp[i].size()) ;
			}
			else
			{
				t = 0 ;
				do {
					x1 = tmp[i][t] ;
					t++ ;
					y1 = tmp[i][t] ;
					t++ ;
					x2 = tmp[i][t] ;
					t++ ;
					y2 = tmp[i][t] ;
					t++ ;
					this->dejouer(x2,y2,x1,y1,mangerPion,J1) ;
				} while(t < tmp[i].size()) ;
			}

			if (score > alpha)
			{
				alpha = score ;
				if (alpha >= beta) 
				{
					//cout << "hehehehehe je te coupe !" << endl ;
					break ;
				}
			}
		}
	}

	if(profondeur == 0) return alpha ;
	return evaluation(tmp, mangerPion, J1) ;
}
/**
 * Cette fonction sert à déjouer un coup qui est dit "manger", elle va prendre en argument
 * les coordonées du point d'origine et du point final pour les remplacer.
 */

void Plateau_Jeu::dejouerManger(int x1, int y1, int x2, int y2, bool J1)
{
	string p1, p2 ;

	if(J1)
	{
		p1 = mesJoueurs[0]->getPion() ;
		p2 = mesJoueurs[1]->getPion() ;
	}
	else
	{
		p1 = mesJoueurs[1]->getPion() ;
		p2 = mesJoueurs[0]->getPion() ;
	}

	if(x1 == x2)
	{
		if(y1 < y2)
		{
			Dameo[x1][y2] = "." ;

			if(J1) 
			{
				mesJoueurs[1]->gagnePion() ;
				Dameo[x1][y2-1] = p2 ;
				Dameo[x1][y1] = p1 ;
			}
			else 
			{
				mesJoueurs[0]->gagnePion() ;
				Dameo[x1][y2-1] = p2 ;
				Dameo[x1][y1] = p1 ;
			}
		}
		if(y1 > y2)
		{
			Dameo[x1][y2] = "." ;

			if(J1) 
			{
				mesJoueurs[1]->gagnePion() ;
				Dameo[x1][y2+1] = p2 ;
				Dameo[x1][y1] = p1 ;
			}
			else 
			{
				mesJoueurs[0]->gagnePion() ;
				Dameo[x1][y2+1] = p2 ;
				Dameo[x1][y1] = p1 ;
			}
		}
	}
	if(y1 == y2)
	{
		if(x1 < x2)
		{
			Dameo[x2][y1] = "." ;

			if(J1) 
			{
				mesJoueurs[1]->gagnePion() ;
				Dameo[x2-1][y1] = p2 ;
				Dameo[x1][y1] = p1 ;
			}
			else 
			{
				mesJoueurs[0]->gagnePion() ;
				Dameo[x2-1][y1] = p2 ;
				Dameo[x1][y1] = p1 ;
			}
		}
		if(x1 > x2)
		{
			Dameo[x2][y1] = "." ;

			if(J1) 
			{
				mesJoueurs[1]->gagnePion() ;
				Dameo[x2+1][y1] = p2 ;
				Dameo[x1][y1] = p1 ;
			}
			else 
			{
				mesJoueurs[0]->gagnePion() ;
				Dameo[x2+1][y1] = p2 ;
				Dameo[x1][y1] = p1 ;
			}
		} 
	}
}

/**
 * Dans notre IA, on utilise le même plateau de jeu pour tous, pour garder le maximun de 
 * mémoire posible afin que le temps necessaire soit le plus petit possible pour exécuter
 * le coup.
 * 
 * Par conséquent quand on joue un coup, il faut le déjouer à la fin de l'appel de la 
 * fonction suivante, il faut donc savoir si c'est un coup dit "normal" ou un coup
 * dit "manger", dans le dernier cas, on fait appel à la fonction dejouerManger()
 */

void Plateau_Jeu::dejouer(int x2, int y2, int x1, int y1, bool mangerPion, bool J1)
{
	if(mangerPion)
	{
		dejouerManger(x2,y2,x1,y1,J1) ;
	}
	else
	{
		Dameo[x2][y2] = '.' ;

		if(J1)
		{
			Dameo[x1][y1] = mesJoueurs[0]->getPion() ;
		}
		else
		{
			Dameo[x1][y1] = mesJoueurs[1]->getPion() ;
		}
	}
}

/**
 * A la fin de l'arbre de récursivité de l'IA, quand la profondeur max a été atteinte
 * on évalue le coup en fonction de différents critères :
 * - combien de pion on a manger
 * - combien de pion on se fait manger
 * - si on a une dame ou pas
 */
int Plateau_Jeu::evaluation(vector<vector<int>> tmp, bool mangerPion, bool J1)
{
	int eval = 0 ;

	if(mangerPion)
	{
		eval += tmp[0].size()*200 ;
	}
	
	string p1, p2 ;
	
	if(J1)
	{
		p1 = mesJoueurs[0]->getPion() ;
		p2 = mesJoueurs[1]->getPion() ;
	}
	else
	{
		p1 = mesJoueurs[1]->getPion() ;
		p2 = mesJoueurs[0]->getPion() ;
	}

	for(int i = 0 ; i < N ; i++)
	{
		if(Dameo[0][i] == p2) eval += 100 ;
		if(Dameo[N-1][i] == p1) eval -= 200 ;
	}

	return eval ;
}

/**
 * La fonction max de l'IA, est la fonction qui est propre au joueur qui vient de lancer
 * le coup, elle va chercher à Maximiser le coup et à renvoyer les coups qui vont être
 * maximiser.
 */
int Plateau_Jeu::max(int profondeur, bool J1)
{
	int s2 = 0 ;
	bool mangerPion = false ; 
	bool c = this->verifyDame() ;
	vector<vector<int>> tmp = this->coupPossible(J1,mangerPion) ;

	if(profondeur > 0)
	{
		for(int i = 0 ; i < tmp.size() ; i++)
		{
			int t = 0 ;
			int x1, x2, y1, y2 ;
			do {
				x1 = tmp[i][t] ;
				t++ ;
				y1 = tmp[i][t] ;
				t++ ;
				x2 = tmp[i][t] ;
				t++ ;
				y2 = tmp[i][t] ;
				t++ ;

				this->deplacementJoueur(x1,x2,y1,y2,mangerPion,J1,true) ;
			} while(t < tmp[i].size()-1) ;

			int s1 = this->min(profondeur-1,!J1) ;
			if(s2 > s1) s2 = s1 ;
				//afficherPlateau() ;
			//affiche(tmp) ;
			if(mangerPion)
			{
				t = 0 ;
				reverse(tmp[i].begin(), tmp[i].end()) ;
				do {
					y1 = tmp[i][t] ;
					t++ ;
					x1 = tmp[i][t] ;
					t++ ;
					y2 = tmp[i][t] ;
					t++ ;
					x2 = tmp[i][t] ;
					t++ ;
					this->dejouer(x2,y2,x1,y1,mangerPion,J1) ;
				} while(t < tmp[i].size()) ;
			}
			else
			{
				t = 0 ;
				do {
					x1 = tmp[i][t] ;
					t++ ;
					y1 = tmp[i][t] ;
					t++ ;
					x2 = tmp[i][t] ;
					t++ ;
					y2 = tmp[i][t] ;
					t++ ;
					this->dejouer(x2,y2,x1,y1,mangerPion,J1) ;
				} while(t < tmp[i].size()) ;
			}
		}
	}

	int m = evaluation(tmp,mangerPion,J1) ;
	return +s2+m ;
}

/**
 * La fonction min de l'IA est la fonction qui va jouer les coups de l'adversaire, elle 
 * va créer le vecteur de coup possible pour tous les pions et les analyser un par un
 * a chaque coup, elle va le jouer, faire appel à la fonction suivante, prendre le retour
 * et après déjouer le coup qui a été fait
 */
int Plateau_Jeu::min(int profondeur,bool J1)
{
	int x1, x2, y1, y2, s2, s1, t ;
	t = s1 = s2 = 0 ;
	bool mangerPion = false ;
	bool c = this->verifyDame() ;
	vector<vector<int>> tmp = this->coupPossible(J1,mangerPion) ;

	if(profondeur > 0)
	{
		for(int i = 0 ; i < tmp.size() ; i++)
		{
			t = 0 ;
			do {
				x1 = tmp[i][t] ;
				t++ ;
				y1 = tmp[i][t] ;
				t++ ;
				x2 = tmp[i][t] ;
				t++ ;
				y2 = tmp[i][t] ;
				t++ ;

				this->deplacementJoueur(x1,x2,y1,y2,mangerPion,J1,true) ;
			} while(t < tmp[i].size()) ;

			s1 = this->max(profondeur-1,!J1) ;
			if(s2 < s1) s2 = s1 ;
		 // afficherPlateau() ;
		 // affiche(tmp) ;
			if(mangerPion)
			{
				t = 0 ;
				reverse(tmp[i].begin(), tmp[i].end()) ;
				do {
					y1 = tmp[i][t] ;
					t++ ;
					x1 = tmp[i][t] ;
					t++ ;
					y2 = tmp[i][t] ;
					t++ ;
					x2 = tmp[i][t] ;
					t++ ;
					this->dejouer(x2,y2,x1,y1,mangerPion,J1) ;
				} while(t < tmp[i].size()) ;
			}
			else
			{
				t = 0 ;
				do {
					x1 = tmp[i][t] ;
					t++ ;
					y1 = tmp[i][t] ;
					t++ ;
					x2 = tmp[i][t] ;
					t++ ;
					y2 = tmp[i][t] ;
					t++ ;
					this->dejouer(x2,y2,x1,y1,mangerPion,J1) ;
				} while(t < tmp[i].size()) ;
			}
		}
	}

	int m = evaluation(tmp,mangerPion,J1) ;
	return -s1-m ;
}

/**
 * C'est la fonction de départ de l'IA, elle va calculer tous les coups disponibles,
 * les envoyer à la fonction suivante tant que la profondeur ne sera pas attteinte.
 * Elle va garder en mémoire le meilleur coup possible, ainsi que l'indice du vector
 * de point.
 */
void Plateau_Jeu::minMax(bool J1, int profondeur,int& maxI)
{
	bool c = this->verifyDame() ;
	int res = -10000000 ;
	bool mangerPion = false ;
	int alpha = -1000000 ;
	int beta = 1000000000 ;
	vector<vector<int>> tmp = this->coupPossible(J1,mangerPion) ;

	for(int i = 0 ; i < tmp.size() ; i++)
	{
		int t = 0 ;
		int m = 0 ;
		int x1, x2, y1, y2 ;
		do {
			x1 = tmp[i][t] ;
			t++ ;
			y1 = tmp[i][t] ;
			t++ ;
			x2 = tmp[i][t] ;
			t++ ;
			y2 = tmp[i][t] ;
			t++ ;

			deplacementJoueur(x1,x2,y1,y2,mangerPion,J1,true) ;
		} while(t < tmp[i].size()-1) ;

		m = -alphaBeta(!J1, profondeur-1, -beta, -alpha) ;
		//m = (this->min(profondeur-1,!J1)) ;
		if(mangerPion)
		{
			t = 0 ;
			reverse(tmp[i].begin(), tmp[i].end()) ;
			do {
				y1 = tmp[i][t] ;
				t++ ;
				x1 = tmp[i][t] ;
				t++ ;
				y2 = tmp[i][t] ;
				t++ ;
				x2 = tmp[i][t] ;
				t++ ;
				this->dejouer(x2,y2,x1,y1,mangerPion,J1) ;
			} while(t < tmp[i].size()) ;
		}
		else
		{
			t = 0 ;
			do {
				x1 = tmp[i][t] ;
				t++ ;
				y1 = tmp[i][t] ;
				t++ ;
				x2 = tmp[i][t] ;
				t++ ;
				y2 = tmp[i][t] ;
				t++ ;
				this->dejouer(x2,y2,x1,y1,mangerPion,J1) ;
			} while(t < tmp[i].size()) ;
		}

		if(m > res )
		{
			res = m ;
			maxI = i ;
		}

		cout << res << "  ->  " << x1 << " " << y1 << " " << x2 << " " << y2 << endl ;
	}
}

/**
 * Restaure le nombre de pion de chaque personnage
 */
void Plateau_Jeu::restaure(int nb, bool J1)
{
	return(J1 ? mesJoueurs[0]->setPion(nb) : mesJoueurs[1]->setPion(nb)) ;
}