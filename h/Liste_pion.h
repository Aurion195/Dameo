#ifndef DEF_LISTE_PION_H
#define DEF_LISTE_PION_H

#include <string>

class Liste_pion
{
 	int max ;
  	int debut ;
  	std::string * tab ;

  	public:
		Liste_pion(std::string* tab, int e) ;
		std::string choisirPion() ;
		void afficherPion() ;
} ;
#endif
