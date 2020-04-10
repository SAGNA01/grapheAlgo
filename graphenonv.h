#ifndef GRAPHENONV_H
#define GRAPHENONV_H
#include "graphe.h"

class graphenonv : public graphe
{
public:
    graphenonv();

    //création d'un grapheNONV à partir d'une matrice d'adjacence
    graphenonv(int **adj);
    //création d'un grapheNONV à partir de la file des successeurs
    graphenonv(int *fs, int *aps);
    virtual ~graphenonv();

    //ajout de l'arc entre s1 et s2 si celui-ci n'existe pas
    virtual void ajoutArc(int s1, int s2, int c = 0);
    //suppression de l'arc entre s1 et s2 si celui ci existe
    virtual void supprArc(int s1, int s2);

    //Codage dePrüfer
    //retourne false si le graphe n'est pas un arbre
    bool est_arbre(int *&d);
    //retourne la matrice d'adjacence correspondant au codage de Prüfer passé en paramètre
    static int** decodage(int *d);

private:
    //dedouble toutes les aretes du graphes si celles-ci n'existent pas
    //pour obtenir un graphe non-oriente
    void dedoublerAretes();
};

#endif // GRAPHENONV_H
