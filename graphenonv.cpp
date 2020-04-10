#include "graphenonv.h"


grapheNONV::grapheNONV() : graphe{}
{}

grapheNONV::grapheNONV(int **adj) : graphe{adj}
{
    dedoublerAretes();
}

grapheNONV::grapheNONV(int *fs, int *aps) :graphe{fs, aps}
{
    dedoublerAretes();
}

grapheNONV::~grapheNONV()
{}

void grapheNONV::ajoutArc(int s1, int s2, int c)
{
    graphe::ajoutArc(s1, s2);
    graphe::ajoutArc(s2, s1);
}

void grapheNONV::dedoublerAretes()
{
    if (d_aps == nullptr || d_fs == nullptr)
        return;

    int sommet = 1;

    for (int i = 1; i <= d_fs[0]; ++i)
        if (d_fs[i] == 0)
            ++sommet;
        else
            ajoutArc(d_fs[i], sommet, 0);
}

void grapheNONV::supprArc(int s1, int s2)
{
    graphe::supprArc(s1, s2);
    graphe::supprArc(s2, s1);
}

bool grapheNONV::est_arbre(int *&d)
{
    if (d_fs == nullptr || d_aps == nullptr)
    {
        return false;
    }
    int n = d_aps[0];
    int m = d_fs[0] - n;
    int k, cpt, d_k;
    d = new int[n];

    int compteur = 1;

    if (m != 2 * (n - 1))
        return false;

    d[0] = n - 2;

    bool *visite = new bool[n + 1];

    for (int i = 1; i <= n; i++)
        visite[i] = false;


    int i = 1;


    while (i <= n)
    {
        cpt = 0;
        if (visite[i] == false)
            for (int j = d_aps[i]; (k = d_fs[j])>0; j++)
            {
                if (visite[k] == false)
                {
                    cpt++;
                    d_k = k;
                }
            }

        if (cpt == 1)
        {
            d[compteur] = d_k;
            compteur++;
            visite[i] = true;
            i = 1;
        }
        i++;
    }

    return (compteur == n);
}

int** grapheNONV::decodage(int *d)
{

    int n = d[0];
    int *visite = new int[n + 3];
    n = n + 2;

    int**adj = new int*[n + 1];
    adj[0] = new int[1];
    adj[0][0] = n;
    adj[0][1] = 2 * (n - 1);
    for (int i = 1; i <= n; ++i)
    {
        adj[i] = new int[n + 1];
        adj[i][0] = n;
        for (int j = 1; j <= n; ++j)
        {
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i <= n; i++)
    {
        visite[i] = 0;
    }
    int nn = n - 2;
    int cpt = 0, cpt_d = 1;
    int l = 1;

    while (l <= n&&cpt_d <= nn)
    {
        if (visite[l] == 0)
        {
            for (int j = 1; j <= nn; j++)
            {
                if (d[j] == l)
                {
                    cpt++;
                }
            }

            if (cpt == 0)
            {
                adj[l][d[cpt_d]] = 1;
                adj[d[cpt_d]][l] = 1;
                visite[l] = 1;
                d[cpt_d] = 0;
                cpt_d++;
                l = 1;
                cpt = 0;

            }
            else
            {
                cpt = 0;
                l++;
            }

        }
        else
        {
            l++;
        }
    }


    for (int i = 1; i <= n; i++)
    {
        if (visite[i] == 0)
        {
            for (int j = i + 1; j <= n; j++)
            {
                if (visite[j] == 0)
                {
                    adj[i][j] = 1;
                    adj[j][i] = 1;
                    break;
                }
            }
            break;

        }
    }

    return adj;
}
