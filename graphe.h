#ifndef GRAPHE_H
#define GRAPHE_H
#include <iostream>
#include <fstream>
using namespace std;
class liste;

class graphe
{
    friend class liste;
    public:
    graphe();
    //construire un graphe donne par la file de ses successeurs
    graphe(int *fs, int *aps);
    //construire un graphe donne par sa matrice d'adjacence
    graphe(int **adj);
    virtual ~graphe();

    //affiche les succ de chaque sommet
    virtual void afficher() const;
    virtual void ajoutArc(int s1, int s2, int cout = 0);
    virtual void supprArc(int s1, int s2);
    virtual void ajoutSommet();
    virtual void supprSommet(int s);

    graphe& operator=(const graphe &g);
    int nbSommet() const;
    int* fs() const;
    int* aps() const;
    void setFs(int *fs);
    void setAps(int *aps);
    void fs_aps() const;
    int** fs2adj() const;
    liste& fs2liste() const;
    static graphe* lire(ifstream &is);
    static bool ecrire(graphe &g, ofstream &os);
    static int* fs2aps(int *fs);

protected:
    int *d_fs, *d_aps;
};

#endif // GRAPHE_H
