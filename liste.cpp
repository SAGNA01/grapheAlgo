#include "liste.h"
#include "graphe.h"

using std::ostream;
using std::endl;

liste::liste() : d_tete(nullptr)
{	}

liste::liste(int nbSommet) : d_tete(nullptr)
{
    if (nbSommet == 0)
        d_tete = nullptr;
    else //creation de la liste principale
    {
        d_tete = new principale(1);

        principale *tmp = d_tete;

        for (int i = 2; i <= nbSommet; ++i)
        {
            tmp->d_suiv = new principale(i);
            tmp = tmp->d_suiv;
        }
    }
}

liste::liste(const graphe& g) : d_tete(nullptr)
{
    int nbSom = g.nbSommet();

    if (nbSom != 0)
    {
        //creation de la liste principale
        d_tete = new principale(1);

        principale *tmp = d_tete;

        for (int i = 2; i <= nbSom; ++i)
        {
            tmp->d_suiv = new principale(i);
            tmp = tmp->d_suiv;
        }

        //creation des listes secondaires
        int sommet = 1,
            k = 1,
            n = g.d_fs[k];

        principale *rech = d_tete;
        //sec *succ = d_tete->d_succ ;
        secondaire *succ;
        tmp = d_tete;

        //tq on a pas traite tous les sommets
        while (sommet <= nbSom)
        {
            bool prem = true;
            //tq le sommet courant a des successeurs
            while (n != 0)
            {
                //recherche du succ ds la liste princ
                for (int j = 1; j<n; ++j)
                    rech = rech->d_suiv;
                if (prem)
                {
                    tmp->d_succ = new secondaire(rech->d_info, rech);
                    succ = tmp->d_succ;
                    prem = false;
                }
                else
                {
                    //on cree le succ
                    succ->d_succ = new secondaire(rech->d_info, rech);
                    //on met a jour
                    succ = succ->d_succ;
                }
                n = g.d_fs[++k];
                rech = d_tete;
            }
            //on passe au sommet suivant
            ++sommet;
            tmp = tmp->d_suiv;
            n = g.d_fs[++k];
            //on traite maintenant les succ du sommet pointé par tmp
        }
    }
}

liste::~liste()
{
    if (d_tete != nullptr)
    {
        principale *tmp = d_tete;

        while (tmp != nullptr)
        {
            tmp = d_tete->d_suiv;
            delete d_tete;
            d_tete = tmp;
        }
    }
}

bool liste::affiche(ostream &ost) const
{
    if (!ost.good())
        return false;

    if (d_tete == nullptr)
    {
        ost << "Liste vide" << endl;
        return true;
    }

    principale *sommet = d_tete;
    secondaire *succ = d_tete->d_succ;
    while (sommet != nullptr)
    {
        ost << "Succ de " << sommet->d_info << " : ";
        while (succ != nullptr)
        {
            ost << succ->d_info << " ";
            succ = succ->d_succ;
        }
        ost << endl;

        sommet = sommet->d_suiv;
        if (sommet != nullptr)
            succ = sommet->d_succ;
        else
            succ = nullptr;

    }
    return true;

}

ostream& operator<<(ostream& ost, const liste& l)
{
    l.affiche(ost);
    return ost;
}

principale::principale(double info, principale *suiv, secondaire *succ) :
d_info(info), d_suiv(suiv), d_succ(succ)
{	}

principale::~principale()
{
    secondaire *tmp = d_succ;
    while (tmp != nullptr)
    {
        tmp = tmp->d_succ;
        delete d_succ;
        d_succ = tmp;
    }
}

secondaire::secondaire(double info, principale *som, secondaire *succ) :
d_info(info), d_succ(succ), d_som(som)
{}

