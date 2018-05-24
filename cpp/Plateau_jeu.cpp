#include "../h/Plateau_jeu.h"
#include "IA.cpp"
#include "Joueur_humain.cpp"

#include <iostream>
#include <fstream>
#include <algorithm>


using namespace std ;


/**
 * Constructeur du plateau de jeu
 */
Plateau_Jeu::Plateau_Jeu(int taille, Joueur_humain* joueur1, Joueur_humain* joueur2)
{
	N = taille ;

	ajouterJoueur(joueur1) ;
	ajouterJoueur(joueur2) ;

	Dameo = new string* [N] ;

	for(int i = 0 ; i < N ; i++)
	{
		Dameo[i] = new string[N] ;
		for(int j = 0 ; j < N ; j++)
		{
			Dameo[i][j] = "." ;
		}
	}

	mini = 0 ;
	maxi = 0 ;
}

/**
 * On va pouvoir changer l'ordre des joueurs en fonction de leurs choix
 */
void Plateau_Jeu::modifie(Joueur_humain* joueur1, Joueur_humain* joueur2)
{
	mesJoueurs.clear() ;
	ajouterJoueur(joueur1) ;
	ajouterJoueur(joueur2) ;
}

/**
 * Destructeur du plateau, apeller à chaque fois que l'on quitte le jeu
 * afin de libérer la mémoire
 */
Plateau_Jeu::~Plateau_Jeu()
{
	for(int i = 0 ; i < N ; i++)
	{
		delete [] Dameo[i] ;
	}

	delete [] Dameo ;

	mesJoueurs.clear() ;
}

/**
 * Prend une instance de joueur comme argument et l'ajoute dans le vecteur
 * de joueur humain du plateau, cela va permettre à la classe Plateau_Jeu
 * d'avoir accès au fonction Joueur_humain
 */
void Plateau_Jeu::ajouterJoueur(Joueur_humain* joueur)
{
	mesJoueurs.push_back(joueur) ;
}

/**
 * Dés qu'un joueur atteint 0 point ou alors que les deux on un seul pion
 * renvoi vrai, sinon ça veut dire que le jeu continue de jouer
 */
bool Plateau_Jeu::gagnePlateau()
{
	int nb1 = mesJoueurs[0]->getNbPion() ;
	int nb2 = mesJoueurs[1]->getNbPion() ;

	return(nb1 == 1 || nb2 == 1 ? true : false) ;
}

/**
 * Vérifie que le pion du tableau est une dame, afin de pouvoir l'afficher
 * de la couleur du joueur
 */
bool Plateau_Jeu::dame(int i, int j, string p1, string& mp)
{
	string m = p1 ;
	m[0] = toupper(p1[0]) ;

	if(Dameo[i][j] == m)
	{
		mp = m ;
		return true ;
	}
	return false ;
}

/**
 * Le joueur va choisir la couleur au début du jeu, cette fonction
 * va permertre d'afficher les couleurs du joueur avec les pions
 * que vous avez choisi
 */
void Plateau_Jeu::afficherColor(int i, int j)
{
	string mp ;
	string p1 = mesJoueurs[0]->getPion() ;
	string p2 = mesJoueurs[1]->getPion() ;
	string c1 = mesJoueurs[0]->getColor() ;
	string c2 = mesJoueurs[1]->getColor() ;

	if(dame(i,j,p1,mp))
	{
		cout << c1 << mp << "\033[0m" ;
	}
	else if(dame(i,j,p2,mp))
	{
		cout << c2 << mp << "\033[0m" ;
	}
	else
	{
		if(Dameo[i][j] == p1) cout << c1 << p1 << "\033[0m" ;
		else if(Dameo[i][j] == p2) cout << c2 << p2 << "\033[0m" ;
		else cout << "." ;
	}

}

/**
 * Affiche le plateau de jeu en fonction de la taille du plateau, affiche ensuite les 
 * indices des colonnes du plateau et termine après par afficher les joueurs.
 */
void Plateau_Jeu::afficherPlateau()
{
	cout << endl << endl << "   Voici votre table de jeu ! " << endl << endl ;

	for(int i = 0 ; i < N ; i++)
	{
		for(int j = 0 ; j < N ; j++)
		{
			afficherColor(i,j) ;
			cout << "  " ;
		}
		cout << "        |        " << i << "       " ;
		cout << endl ;
	}

	cout << endl ;

	for(int i = 0 ; i < N ; i++)
	{
		if(i < 10)  cout << i << "  " ;
		else cout << i << " " ;
	}

	cout << endl << endl ; ;

	mesJoueurs[0]->afficherJoueur() ;
	mesJoueurs[1]->afficherJoueur() ;
}

/**
 * Remplit le plateau en fonction de la taille qui a été choisi
 * Cette fonction va mettre les pions des joueurs dans les cases
 * du platau de jeu
 */
void Plateau_Jeu::remplirPlateau()                                                                     
{
	string P1 = mesJoueurs[0]->getPion() ;
	string P2 = mesJoueurs[1]->getPion() ;

	for(int i = 0 ; i < N ; i++)
	{
		for(int j = 0 ; j < N ; j++)
		{
			if(N/2-1 == i || N/2 == i)
			{
				while(j < N)
				{
					Dameo[i][j] = "." ;
					j++ ;
				}
			}
			else if(i == 0 || i == N-1)
			{
				if(i < N/2)
				{
					Dameo[i][j] = P1 ;
				}
				else
				{
					Dameo[i][j] = P2 ;
				}
			}
			else
			{
				while(j < N)
				{
					if(i < N/2)
					{
						if(j < i || j > N-1-i)
						{
							Dameo[i][j] = "." ;
						}
						else
						{
							Dameo[i][j] = P1 ;
						}
					}
					else
					{
						if(j < N-(i+1) || j > N-(N-(i+1))-1)
						{
							Dameo[i][j] = "." ;
						}
						else
						{
							Dameo[i][j] = P2 ;
						}
					}
					j++ ;
				}
			}
		}
	}
}

/**Fonction qui va permettre de charger le plateau à partir d'une sauvegarde
 * Cette fonction va prendre en argument un string, ainsi qu'un x et un y
 * qui seront les coordonnées du pion, elle va donc le mettre sur le 
 * plateau
 */ 
void Plateau_Jeu::remplirPlateauSauvegardePlateau(string z, int x, int y)
{
	Dameo[x][y] = z ;
}

/**
 * Va parcourir la 1er ligne du plateau ainsi que la dernière et va la transformer 
 * en majuscule :
 * - si le pion du j2 est dans la ligne 0,
 * - si le pion du j1 est dans la ligne N-1.
 * Elle renvoi vrai si il y a au-moins une dame
 */
bool Plateau_Jeu::verifyDame()
{
	int i = 0 ;

	for(int i = 0 ; i < N ; i++)
	{
		if(Dameo[0][i] == mesJoueurs[1]->getPion()) 
		{
			Dameo[0][i] = majuscule(mesJoueurs[1]->getPion()) ;
			i++ ;
		}

		if(Dameo[N-1][i] == mesJoueurs[0]->getPion())
		{
			Dameo[N-1][i] = majuscule(mesJoueurs[0]->getPion()) ;
			i++ ;
		}
	}

	return(i > 0 ? true :false) ;
}

/**
 * Reçoit les coordonnées de départ d'un pion et celle de retour
 * elle va faire des vérifications pour savoir ou se situe le pion
 * par rapport au 1er et au 2eme pion en fonction de la valeur des
 * pions x1, y1, y1, y2.
 */
bool Plateau_Jeu::mangePion(int x1, int x2, int y1, int y2, bool J1, bool dame)
{
	string p1 = Dameo[x1][y1] ;
	string mp1 = p1 ;

	if(dame)
	{
		mp1[0] = toupper(p1[0]) ;
		p1 = mp1 ;
	}

	if(x1 == x2)
	{
		if(y1 < y2)
		{
			Dameo[x1][y1] = "." ;
			Dameo[x1][y1+1] = "." ;
			Dameo[x1][y2] = p1 ;

			if(J1) mesJoueurs[1]->perdPion() ;
			else mesJoueurs[0]->perdPion() ;
		}
		else
		{
			Dameo[x1][y1] = "." ;
			Dameo[x1][y1-1] = "." ;
			Dameo[x1][y2] = p1 ;

			if(J1) mesJoueurs[1]->perdPion() ;
			else mesJoueurs[0]->perdPion() ;
		}
	}
	else
	{
		if(x1 < x2)
		{
			Dameo[x1][y1] = "." ;
			Dameo[x1+1][y1] = "." ;
			Dameo[x2][y1] = p1;

			if(J1) mesJoueurs[1]->perdPion() ;
			else mesJoueurs[0]->perdPion() ;
		}
		else
		{
			Dameo[x1][y1] = "." ;
			Dameo[x1-1][y1] = "." ;
			Dameo[x2][y1] = p1 ;

			if(J1) mesJoueurs[1]->perdPion() ;
			else mesJoueurs[0]->perdPion() ;
		} 
	}
}

/**
 * Vérifie en 1er si tu mange un pion, si le boolean = true, elle fait appel
 * à la fonction mangePion(),
 * Si elle ne peut pas manger, elle déplace simplement le pion
 */
void Plateau_Jeu::deplacementJoueur(int x1, int x2, int y1, int y2, bool mangerPion, bool J1, bool dame)
{
	if(mangerPion)
	{
		mangePion(x1,x2,y1,y2,J1,dame) ;
	}
	else
	{
		string p1 = Dameo[x1][y1] ;
		Dameo[x1][y1] = "." ;
		Dameo[x2][y2] = p1 ;
	}
}

/**
 * Renvoi la taille du plateau
 */
int Plateau_Jeu::getTaille()
{
	return N ;
}

/**
 * Renvoi le plateau de jeu
 */
string** Plateau_Jeu::getPlateau()
{
	return Dameo ;
}

/**
 * Renvoi le vector des joueurs
 */
vector<Joueur_humain*> Plateau_Jeu::getJoueur()
{
	return mesJoueurs ;
}

/**
 * Calcule tous les coups possibles pour chaque pion ou dame, elle vérifie 
 * toutes les possibilités et ne mets dans le vector de vector de int que 
 * les coups qui sont dit "sûr".
 * Si dans les possibilités il y a un pion qui va manger un autre pion, elle
 * supprime toutes les autres possibilités et n'affiche que celle-là.
 * 
 * Par conséquent si un autre pion peut manger plus de pion que le précédent elle
 * supprime aussi le coup "manger", si le coup pemet de manger le même nombre
 * pion elle l'ajoute dans le vector
 */
vector<vector<int>> Plateau_Jeu::coupPossible(bool J1, bool& mangePion)
{
	int increment, cpt, nb, manger, max ;
	increment = cpt = nb = 0 ;
	manger = -1 ;
	max = 0 ;
	string pa, pn, mpa, mpn ;

	if(J1)
	{
		increment = 1 ;
		pa = mesJoueurs[0]->getPion() ;
		mpa = pa ;
		mpa[0] = toupper(pa[0]) ;
		pn = mesJoueurs[1]->getPion() ;
		mpn = pn ;
		mpn[0] = toupper(pn[0]) ;
	}
	else
	{
		increment = -1 ;
		pa = mesJoueurs[1]->getPion() ;
		mpa = pa ;
		mpa[0] = toupper(pa[0]) ;
		pn = mesJoueurs[0]->getPion() ;
		mpn = pn ;  
		mpn[0] = toupper(pn[0]) ;
	}

	vector<vector<int>> tmp ;
	vector<vector<int>> t;

	for(int i = 0 ; i < N ; i++)
	{
		for(int j = 0 ; j < N ; j++)
		{
			int a = i - 1 ;
			int b = i + 1 ;
			int y = j - 1 ;
			int z = j + 1 ;

			if(a < 0) a = 0 ;
			if(b == N) b = N-1 ;
			if(y < 0) y = 0 ;
			if(z == N) z = N-1 ; 

			t.clear() ;
			t.push_back(vector<int>()) ;

			nb = -1 ;

			if(Dameo[i][j] == pa)
			{
				bool dame = false ;
				if(Dameo[a][j] == pn || Dameo[i][y] == pn || Dameo[i][z] == pn || Dameo[b][j] == pn || 
					Dameo[a][j] == mpn || Dameo[i][y] == mpn || Dameo[i][z] == mpn || Dameo[b][j] == mpn)
				{
					mange(t, i, j,true, true, true, true, nb, max, J1, manger,mangePion,dame) ;
					if(mangePion) compare(tmp,t,nb,max) ;
				}
				if(manger == -1 && (Dameo[a][j] == pa || Dameo[a][y] == pa || Dameo[a][z] == pa || Dameo[a][j] == "."
					|| Dameo[a][y] == "." || Dameo[a][z] == "." || Dameo[a][j] == mpa || Dameo[a][y] == mpa || Dameo[a][z] == mpa))
				{
					sautePion(tmp,i,j,J1) ;
				}
			}

			if(Dameo[i][j] == mpa)
			{
				if(Dameo[a][j] == pn || Dameo[i][y] == pn || Dameo[i][z] == pn || Dameo[b][j] == pn || 
					Dameo[a][j] == mpn || Dameo[i][y] == mpn || Dameo[i][z] == mpn || Dameo[b][j] == mpn)
				{
					bool dame = true ;
					mange(t, i, j,true, true, true, true, nb, max, J1, manger,mangePion,dame) ;

					if(mangePion) compare(tmp,t,nb,max) ;

				}
				if(manger == -1 && (Dameo[a][j] == pa || Dameo[a][y] == pa || Dameo[a][z] == pa || Dameo[a][j] == "."
					|| Dameo[a][y] == "." || Dameo[a][z] == "." || Dameo[a][j] == mpa || Dameo[a][y] == mpa || Dameo[a][z] == mpa))
				{
					deplacementDame(tmp,i,j,J1) ;
				}
			}
		}
	}

	return tmp ;
}

/**
 * Calcule les coups normaux et les envoi dans un vector, il s'agit là des
 * déplacements de base pour un pion
 */
void Plateau_Jeu::sautePion(vector<vector<int>>& tmp, int x1, int y1, bool J1)
{
	int increment = 0 ;
	string pa, pn, mpa, mpn ;
	int cpt ;

	if(J1)
	{
		increment = 1 ;
		pa = mesJoueurs[0]->getPion() ;
		mpa[0] = toupper(pa[0]) ;
		pn = mesJoueurs[1]->getPion() ;
		mpn[0] = toupper(pn[0]) ;
	}
	else
	{
		increment = -1 ;
		pa = mesJoueurs[1]->getPion() ;
		mpa[0] = toupper(pa[0]) ;
		pn = mesJoueurs[0]->getPion() ;
		mpn[0] = toupper(pn[0]) ;
	}

	if(x1 >= 0 && x1 < N)
	{
		int test = x1 ;
		int test2 = y1 ;
		
			while((Dameo[x1][y1] == pa || Dameo[x1][y1] == mpa) && x1 >=0 && x1 < N &&y1 < N-1)
			{
				x1 += increment ;
				y1++ ;
			}

			if(Dameo[x1][y1] == ".")
			{
				tmp.push_back(vector<int>()) ;
				int n = tmp.size()-1 ;
				tmp[n].push_back(test) ;
				tmp[n].push_back(test2) ;
				tmp[n].push_back(x1) ;
				tmp[n].push_back(y1) ;
			}

			x1 = test ;
			y1 = test2 ;

			while((Dameo[x1][y1] == pa || Dameo[x1][y1] == mpa )&& x1 >= 0 && x1 < N && y1 >= 0)
			{
				x1 += increment ;
				y1-- ;
			}

			if(Dameo[x1][y1] == ".")
			{
				tmp.push_back(vector<int>()) ;
				int n = tmp.size()-1 ;
				tmp[n].push_back(test) ;
				tmp[n].push_back(test2) ;
				tmp[n].push_back(x1) ;
				tmp[n].push_back(y1) ;
			}

			x1 = test ;
			y1 = test2 ;

		while((Dameo[x1][y1] == pa || Dameo[x1][y1] == mpa ) && (x1 < N || x1 > 0))
		{
			x1 += increment ;
		}

			if(Dameo[x1][y1] == ".")
			{
				tmp.push_back(vector<int>()) ;
				int n = tmp.size()-1 ;
				tmp[n].push_back(test) ;
				tmp[n].push_back(test2) ;
				tmp[n].push_back(x1) ;
				tmp[n].push_back(y1) ;
			}

			this->verifyDame() ;
	}
}

/**
 * Calcule les coups pour une dame et les envoi dans le vector de coup possibles
 */
void Plateau_Jeu::deplacementDame(vector<vector<int>>& tmp, int x1, int y1, bool J1)
{
	string pa, pn, mpa, mpn ;
	int cpt ;

	int absicce = x1 ;
	int ordonne = y1 ;

	if(J1)
	{
		pa = mesJoueurs[0]->getPion() ;
		mpa = pa ;
		mpa[0] = toupper(pa[0]) ;
		pn = mesJoueurs[1]->getPion() ;
		mpn = pn ;
		mpn[0] = toupper(pn[0]) ;
	}
	else
	{
		pa = mesJoueurs[1]->getPion() ;
		mpa = pa ;
		mpa[0] = toupper(pa[0]) ;
		pn = mesJoueurs[0]->getPion() ;
		mpn = pn ;
		mpn[0] = toupper(pn[0]) ;
	}

	int n = tmp.size()-1 ;

	while(x1 < N && (Dameo[x1][y1] == "." || Dameo[x1][y1] == pa || Dameo[x1][y1] == mpa))
	{ 
		if(Dameo[x1][y1] == ".")
		{
			tmp.push_back(vector<int>()) ;
			int n = tmp.size()-1 ;
			tmp[n].push_back(absicce) ;
			tmp[n].push_back(ordonne) ;
			tmp[n].push_back(x1) ;
			tmp[n].push_back(y1) ;
		}

		x1++ ;
	}

	x1 = absicce ;
	y1 = ordonne ;

	while(x1 >= 0 && (Dameo[x1][y1] == "." || Dameo[x1][y1] == pa || Dameo[x1][y1] == mpa))
	{ 
		if(Dameo[x1][y1] == ".")
		{
			tmp.push_back(vector<int>()) ;
			int n = tmp.size()-1 ;
			tmp[n].push_back(absicce) ;
			tmp[n].push_back(ordonne) ;
			tmp[n].push_back(x1) ;
			tmp[n].push_back(y1) ;
		}

		x1-- ;
	}

	x1 = absicce ;
	y1 = ordonne ;
	
	while(y1 >= 0 && (Dameo[x1][y1] == "." || Dameo[x1][y1] == pa || Dameo[x1][y1] == mpa))
	{ 
		if(Dameo[x1][y1] == ".")
		{
			tmp.push_back(vector<int>()) ;
			int n = tmp.size()-1 ;
			tmp[n].push_back(absicce) ;
			tmp[n].push_back(ordonne) ;
			tmp[n].push_back(x1) ;
			tmp[n].push_back(y1) ;
		}
		
		y1-- ;
	}

	x1 = absicce ;
	y1 = ordonne ;
	
	while(y1 < N && (Dameo[x1][y1] == "." || Dameo[x1][y1] == pa || Dameo[x1][y1] == mpa))
	{ 
		if(Dameo[x1][y1] == ".")
		{
			tmp.push_back(vector<int>()) ;
			int n = tmp.size()-1 ;
			tmp[n].push_back(absicce) ;
			tmp[n].push_back(ordonne) ;
			tmp[n].push_back(x1) ;
			tmp[n].push_back(y1) ;
		}
		
		y1++ ;
	}

	x1 = absicce ;
	y1 = ordonne ;
	
	while((x1 < N && y1 < N) && (Dameo[x1][y1] == "." || Dameo[x1][y1] == pa || Dameo[x1][y1] == mpa))
	{ 
		if(Dameo[x1][y1] == ".")
		{
			tmp.push_back(vector<int>()) ;
			int n = tmp.size()-1 ;
			tmp[n].push_back(absicce) ;
			tmp[n].push_back(ordonne) ;
			tmp[n].push_back(x1) ;
			tmp[n].push_back(y1) ;
		}
	
		x1++ ;
		y1++ ;
	}

	x1 = absicce ;
	y1 = ordonne ;
	
	while((x1 < N && y1 >= 0) && (Dameo[x1][y1] == "." || Dameo[x1][y1] == pa || Dameo[x1][y1] == mpa))
	{ 
		if(Dameo[x1][y1] == ".")
		{
			tmp.push_back(vector<int>()) ;
			int n = tmp.size()-1 ;
			tmp[n].push_back(absicce) ;
			tmp[n].push_back(ordonne) ;
			tmp[n].push_back(x1) ;
			tmp[n].push_back(y1) ;
		}
		
		x1++ ;
		y1-- ;
	}

	x1 = absicce ;
	y1 = ordonne ;
	
	while((x1 >= 0 && y1 < N) && (Dameo[x1][y1] == "." || Dameo[x1][y1] == pa || Dameo[x1][y1] == mpa))
	{ 
		if(Dameo[x1][y1] == ".")
		{
			tmp.push_back(vector<int>()) ;
			int n = tmp.size()-1 ;
			tmp[n].push_back(absicce) ;
			tmp[n].push_back(ordonne) ;
			tmp[n].push_back(x1) ;
			tmp[n].push_back(y1) ;
		}
		
		x1-- ;
		y1++ ;
	}

	x1 = absicce ;
	y1 = ordonne ;
	
	while((x1 >= 0 && y1 >= 0) && (Dameo[x1][y1] == "." || Dameo[x1][y1] == pa || Dameo[x1][y1] == mpa))
	{ 
		if(Dameo[x1][y1] == ".")
		{
			tmp.push_back(vector<int>()) ;
			int n = tmp.size()-1 ;
			tmp[n].push_back(absicce) ;
			tmp[n].push_back(ordonne) ;
			tmp[n].push_back(x1) ;
			tmp[n].push_back(y1) ;
		}
		
		x1-- ;
		y1-- ;
	}
}

/**
 * Quand un pion peut manger, la fonction coupPossible() fait appel à cette fonction
 * Elle prend en argument un nouveau vector<vector<int>> t, on va stocker dans ce vector
 * tous les coups possibles pour ce pion
 * 
 * Si les fonction mangeUp, mangeDown, mangeLeft et mangeRigth renvoi vrai, on ajoute
 * le coup dans le vector et on renvoi par récursivité en déplacant le pion
 * 
 * Si la récursivité échoue et qu'on ne peut manger plus aucun pion, elle termine avec ce
 * vector et copie les coups sur dans un autre au cas ou on peut en manger un autre
 * avec les même coups
 */
void Plateau_Jeu::mange(vector<vector<int>>& t, int x1, int y1,bool up, bool down, bool droite, bool gauche, int& nb, int& max, bool J1, int& manger, bool& mangePion, bool dame)
{
	if(J1)
	{
		if(x1 == N-1) dame = true ;
	}
	else
	{
		if(x1 == 0) dame = true ;
	}

	int n, cpt, x, y, increment ;
	n = cpt = increment = 0 ;

	if(J1) increment = 1 ;
	else increment = -1 ;
	bool man = false ;

	if(x1 >= 0 && x1 < N && y1 >=0 && y1 < N)
	{
		if(mangeLeft(x1,y1,J1) && droite)
		{
			man = true ;
			mangePion = true ;
			manger++ ;
			ajouterCoup(t,x1,y1,x1,y1-2,nb,max) ;
			mange(t,x1,y1-2,true,true,droite,false,nb,max,J1,manger,mangePion,dame) ;
		}

		if(mangeRigth(x1,y1,J1) && gauche)
		{
			man = true ;
			mangePion = true ;
			manger++ ;
			ajouterCoup(t,x1,y1,x1,y1+2,nb,max) ;
			mange(t,x1,y1+2,true,true,false,gauche,nb,max,J1,manger,mangePion,dame) ;
		}

		if(mangeUp(x1,y1,J1) && up)
		{
			int increment = 0 ;
			if(J1) increment = 1 ;
			else increment = -1 ;

			man = true ;
			mangePion = true ;
			down = false ;
			manger++ ;
			ajouterCoup(t,x1,y1,x1+(2*increment),y1,nb,max) ;
			mange(t,x1+(2*increment),y1,up,false,true,true,nb,max,J1,manger,mangePion,dame) ;
		}

		if(dame && mangeDown(x1,y1,J1) && down)
		{
			int increment2 = 0 ;
			if(J1) increment2 = -1 ;
			else increment2 = 1 ;

			man = true ;
			up = false ;
			mangePion = true ;
			manger++ ;
			ajouterCoup(t,x1,y1,x1+(2*increment2),y1, nb, max) ;
			mange(t,x1+(2*increment2),false,down,y1,true,true,nb,max,J1,manger,mangePion,dame) ;
		}

		if(nb > -1 && !man)
		{
			t.push_back(vector<int>()) ;
			int n = t.size() - 2 ;
			int cpt = t.size() - 1 ;
			if(n > -1)
			{
				for(int i = 0 ; i < nb*4 ; i++)
				{
					t[cpt].push_back(t[n][i]) ;
				}
			}
		}
	}
}

/**
 * Vérifie si tu peux manger en allant par en haut
 * renvoi vrai si tu peux manger
 */
bool Plateau_Jeu::mangeUp(int x1, int y1, bool J1)
{
	string pn, mpn ;
	int increment ;
	if(J1)
	{
		increment = 1 ;
		pn = mesJoueurs[1]->getPion() ;
		mpn = pn ;
		mpn[0] = toupper(pn[0]) ;
	}
	else
	{
		increment = -1 ;
		pn = mesJoueurs[0]->getPion() ;
		mpn = pn ;
		mpn[0] = toupper(pn[0]) ;
	}

	if(x1+increment < N && x1+increment >= 0)
	{
		if(Dameo[x1+increment][y1] == pn || Dameo[x1+increment][y1] == mpn)
		{
			if(x1+(2*increment) < N && x1+(2*increment) >= 0)
			{
				if(Dameo[x1+2*increment][y1] == ".")
				{
					return true ;
				}
			}
		}
	}

	return false ;
}

/**
 * Vérifie si tu peux manger en allant par en bas, cette fonction est faîte
 * pour les dames
 * renvoi vrai si tu peux manger
 */
bool Plateau_Jeu::mangeDown(int x1, int y1, bool J1)
{
	string pn, mpn ;
	int increment = 0 ;

	if(J1)
	{
		increment = -1 ;
		pn = mesJoueurs[1]->getPion() ;
		mpn = pn ;
		mpn[0] = toupper(pn[0]) ;
	}
	else
	{
		increment = 1 ;
		pn = mesJoueurs[0]->getPion() ;
		mpn = pn ;
		mpn[0] = toupper(pn[0]) ;
	}

	if(x1+increment >= 0 && x1+increment < N)
	{
		if(Dameo[x1+increment][y1] == pn || Dameo[x1+increment][y1] == mpn)
		{
			if(x1+(2*increment) >= 0)
			{
				if(Dameo[x1+(2*increment)][y1] == ".")
				{
					return true ;
				}
			}
		}
	}

	return false ;
}

/**
 * Vérifie si tu peux manger en allant par à gauche
 * renvoi vrai si tu peux manger
 */
bool Plateau_Jeu::mangeLeft(int x1, int y1, bool J1)
{
	string pn, mpn ;

	if(J1)
	{
		pn = mesJoueurs[1]->getPion() ;
		mpn = pn ;
		mpn[0] = toupper(pn[0]) ;
	}
	else
	{
		pn = mesJoueurs[0]->getPion() ;
		mpn = pn ;
		mpn[0] = toupper(pn[0]) ;
	}

	if(y1-1 >= 0)
	{
		if(Dameo[x1][y1-1] == pn || Dameo[x1][y1-1] == mpn)
		{
			if(y1-2 >= 0)
			{
				if(Dameo[x1][y1-2] == ".")
				{
					return true ;
				}
			}
		}
	}

	return false ;
}

/**
 * Vérifie si tu peux manger en allant par à droite
 * renvoi vrai si tu peux manger
 */
bool Plateau_Jeu::mangeRigth(int x1, int y1, bool J1)
{
	string pn, mpn ;

	if(J1)
	{
		pn = mesJoueurs[1]->getPion() ;
		mpn = pn ;
		mpn[0] = toupper(pn[0]) ;
	}
	else
	{
		pn = mesJoueurs[0]->getPion() ;
		mpn = pn ;
		mpn[0] = toupper(pn[0]) ;
	}

	if(y1+1 < N)
	{
		if(Dameo[x1][y1+1] == pn || Dameo[x1][y1+1] == mpn)
		{
			if(y1+2 < N)
			{
				if(Dameo[x1][y1+2] == ".")
				{
					return true ;
				}
			}
		}
	}

	return false ;
}

/**
 * Ajoute les coups dans le vector t, et incrémente le compteur de coups
 * nb
 */
void Plateau_Jeu::ajouterCoup(vector<vector<int>>& t, int x1, int y1, int x, int y, int& nb, int& max)
{
	nb++ ;
	int n = t.size()-1 ;
	t[n].push_back(x1) ;
	t[n].push_back(y1) ;
	t[n].push_back(x) ;
	t[n].push_back(y) ;
}

/**
 * Cette fonction va comparer les coups possibles en mangeant un pion, si les coups dans
 * tmp sont inférieur au coups dans t, elle va tout supprimer dans tmp et mettre les coups
 * de t. Seulement si c'est supérieur.
 * 
 * Cependant si c'est égal, elle ajoute juste les nouveaux coups au vector
 */
void Plateau_Jeu::compare(vector<vector<int>>& tmp, vector<vector<int>>& t, int& nb, int& max)
{
	int n, m ;

	for(int i = 0 ; i < t.size() ; i++)
	{
		if(t[i].size() > max)
		{
			max = t[i].size() ;
			tmp.clear() ;
			tmp.push_back(vector<int> ()) ;
			n = tmp.size()-1 ;

			for(int j = 0 ; j < max ; j++)
			{
				tmp[n].push_back(t[i][j]) ;
			}
		}
		else if(t[i].size() == max)
		{
			tmp.push_back(vector<int>()) ;
			n = tmp.size()-1 ;

			for(int j = 0 ; j < max ; j++)
			{
				tmp[n].push_back(t[i][j]) ;
			}
		}
	}
}

/**
 * Affiche tous les déplacements possibles contenus dans le vector tmp
 */
void Plateau_Jeu::affiche(vector<vector<int>> tmp)
{
	int t = 0 ;
	for(int i = 0 ; i < tmp.size() ; i++)
	{
		int cpt = 0 ;
		t++ ;
		cout <<  i << " : " ;
		for(int k = 0 ; k < tmp[i].size() ; k++)
		{
			if(cpt == 0) cout << " [ " ;
			cout << tmp[i][k] << " " ;
			cpt++ ;
			if(cpt == 2) cout << " ->  " ;
			if(cpt == 4)
			{
				cout << " ]   " ;
				cpt = 0 ;
			}
		}
			
		if(t == 5)
		{
			t = 0 ;
			cout << endl << endl ;
		}
	}

		cout << endl ;
}