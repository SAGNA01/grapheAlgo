#ifndef GRAPHEOV_H
#define GRAPHEOV_H
#include "graphe.h"

using namespace std;

class grapheov : public graphe
{
public:
    grapheov();
    //création d'un graphe à partir de la file des successeurs
    grapheov(int *fs, int *aps, int **couts);
    virtual ~grapheov();


    //affichage avec la matrice des couts
    virtual void afficher() const;
    //ajout de l'arc entre s1 et s2 avec le cout c si celui-ci n'existe pas
    virtual void ajoutArc(int s1, int s2, int cout);
    //suppression de l'arc entre s1 et s2 si celui ci existe
    virtual void supprArc(int s1, int s2);
    //ajoute un sommet au graphe de numero nbSommet()+1 et redimensionne d_cout
    virtual void ajoutSommet();
    //supprime le sommet s et tous ses arcs si celui-ci existe et redimensionne d_cout
    virtual void supprSommet(int s);

    //retourne la matrice des couts du graphe courant
    int** Cout() const;
    //modification de la matrice des couts
    bool setCout(int **couts);

    //retourne le nb de pred de chaque sommet
    int* nb_pred() const;
    //retourne la matrice des distance
    int* dist(int s) const;
    //calcul du rang
    int* rang(int *&pilch, int *&prem) const;
    //retourne la file des pred
    int* fs2fp() const;
    //retourne le pred dans le chemin critique
    int* det_pred() const;
    //retourne le plus long chemin arrivant à s
    int* chemin(int s) const;

    //retourne faux si un sommet est inaccessible
    //d contient la distance min par rapport au sommet s
    bool Dijkstra(int s, int* &d, int* &pere) const;

    bool circuit(int* fs, int* aps, int* statut, int s);

    grapheov* Critique(int* &lc, int* &fpc, int*& appc, int*coutotal);
    void ordonnancement(int *&fs, int *&num);

    //retourn la file des pred a partir de la file des successeurs
    static int* fs2fp_(int *fs);

private:
    //matrice des couts
    int **d_cout;
    //recherche l'indice ds d tq ins[i] = true et d[i] minimal
    int dmin(bool* ins, int *d) const;
};

#endif // GRAPHEOV_H
