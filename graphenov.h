#ifndef GRAPHENOV_H
#define GRAPHENOV_H
#include "graphe.h"


class graphenov : public graphe
{
public:
    graphenov();
    //création d'un grapheNONV à partir dde la file des successeurs
    graphenov(int *fs, int *aps, int **cout);
    virtual ~graphenov();

    //affichage avec la matrice des couts
    virtual void afficher() const;
    //ajout de l'arc entre s1 et s2 avec le cout c si celui-ci n'existe pas
    virtual void ajoutArc(int s1, int s2, int c);
    //suppression de l'arc entre s1 et s2 si celui ci existe
    virtual void supprArc(int s1, int s2);
    //ajoute un sommet de numero nbSommet au graphe ()+1 et redimensionne d_cout
    virtual void ajoutSommet();
    //supprime le sommet s et tous ses arcs si celui-ci existe et redimensionne d_cout
    virtual void supprSommet(int s);

    //retourne la matrice des couts du graphe courant
    int** Cout() const;
    //modification de la matrice des couts
    //renvoie false si la matrice des cout n'est pas de la bonne taille
    bool setCout(int **couts);


    //retourne faux si un sommet est inaccessible
    //d contient la distance min par rapport au sommet s
    bool Dijkstra(int s, int* &d, int* &pere) const;

    //créer la matrice d'adjacence
    void Kruskal(int **&arrete);

private:
    //dedouble toutes les aretes du graphes si celles-ci n'existent pas
    //pour obtenir un graphe non-oriente
    void dedoublerAretes();
    //recherche l'indice ds d tq ins[i] = true et d[i] minimal
    int dmin(bool* ins, int *d) const;

    //matrice des couts
    int **d_cout;
};

#endif // GRAPHENOV_H
