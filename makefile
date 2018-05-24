Dameo : cpp/Main.cpp cpp/Fonction.cpp Obj/Plateau_jeu.o Obj/Joueur_humain.o Obj/Liste_pion.o Obj/Fonction_plateau.o Obj/Fonction_joueurH.o
	g++ -std=c++11 cpp/Main.cpp -o Bin/Dameo

Obj/Liste_pion.o : h/Liste_pion.h cpp/Liste_pion.cpp
	g++ -c -std=c++11 cpp/Liste_pion.cpp -o Obj/Liste_pion.o

Obj/Fonction_plateau.o : cpp/Fonction_plateau.cpp
	g++ -c -std=c++11 cpp/Fonction_plateau.cpp -o Obj/Fonction_plateau.o

Obj/Fonction_joueurH.o : cpp/Fonction_joueurH.cpp
	g++ -c -std=c++11 cpp/Fonction_joueurH.cpp -o Obj/Fonction_joueurH.o

Obj/Plateau_jeu.o : h/Plateau_jeu.h cpp/Plateau_jeu.cpp cpp/IA.cpp
	g++ -c -std=c++11 cpp/Plateau_jeu.cpp -o Obj/Plateau_jeu.o

Obj/Joueur_humain.o : h/Joueur_humain.h cpp/Joueur_humain.cpp
	g++ -c -std=c++11 cpp/Joueur_humain.cpp -o Obj/Joueur_humain.o

clean:
	rm Obj/*.o

Mrpropper: clean
	rm -f Bin/Dameo
