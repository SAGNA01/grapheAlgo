#ifndef LISTE_H
#define LISTE_H

#include <iostream>

using std::ostream;

class graphe;
class principale;
class secondaire;

class liste
{
    public:

    //liste vide
    liste();
    //liste principale de nbSommet
    liste(int nbSommet);
    //liste correspodant au graphe g
    liste(const graphe& g);
    ~liste();

    bool affiche(ostream &os) const;

    private:
        principale* d_tete;
    };

    ostream& operator<<(ostream& os, const liste& l);

    //liste principale des sommets
    class principale
    {
        friend class liste;

    public:
        principale(double info, principale *suiv = NULL, secondaire *succ = NULL);
        ~principale();

    private:
        double d_info; //numéro du sommet
        principale *d_suiv; //sommet suivant dans la liste princ
        secondaire *d_succ; //successeur
    };

    //liste secondaire des succ
    class secondaire
    {
        friend class principale;
        friend class liste;

    public:
        secondaire(double info, principale* som = NULL, secondaire *succ = NULL);

    private:
        double d_info; //numéro du succ
        secondaire * d_succ; //successeur suivant
        principale* d_som; //sommet

};

#endif // LISTE_H
