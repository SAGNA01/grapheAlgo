#include "graphenov.h"
#include<limits.h>

graphenov::graphenov() : graphe{}, d_cout{nullptr}
{}

graphenov::graphenov(int *fs, int *aps, int **cout) :
graphe{fs, aps}
{
    if (fs == nullptr || aps == nullptr)
    {
        d_cout = nullptr;
        return;
    }

    int n = nbSommet();
    d_cout = new int*[n + 1];
    d_cout[0] = new int[2];
    d_cout[0][0] = n;
    d_cout[0][1] = d_fs[0] - n;
    for (int i = 1; i <= n; ++i)
        d_cout[i] = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            d_cout[i][j] = cout[i][j];

    dedoublerAretes();
}

graphenov::~graphenov()
{
    int n = nbSommet();
    if (n != 0)
        for (int i = 0; i <= n; ++i)
            delete d_cout[i];
    delete d_cout;
}

void graphenov::afficher() const
{
    graphe::afficher();
    int n = nbSommet();

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (d_cout[i][j] == INT_MAX)
                cout << "-1" << " ";
            else
                cout << d_cout[i][j] << " ";
        }
        cout << endl;
    }
}

int** graphenov::Cout() const
{
    if (d_cout == nullptr)
        return nullptr;

    int n = nbSommet();
    int **c = new int*[n + 1];
    c[0] = new int[1];
    c[0][0] = n;
    for (int i = 1; i <= n; ++i)
        c[i] = new int[n + 1];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            c[i][j] = d_cout[i][j];

    return c;
}

bool graphenov::setCout(int **cout)
{
    if (cout == nullptr)
    {
        delete d_cout;
        d_cout = nullptr;
        return true;
    }

    int n = cout[0][0];
    if (n != nbSommet())
        return false;

    delete d_cout;
    d_cout = new int*[n + 1];
    d_cout[0] = new int[1];
    d_cout[0][0] = n;
    for (int i = 1; i <= n; ++i)
    {
        d_cout[i] = new int[n + 1];
        d_cout[i][0] = n + 1;
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            d_cout[i][j] = cout[i][j];
    return true;
}

void graphenov::ajoutArc(int s1, int s2, int c)
{
    graphe::ajoutArc(s1, s2);
    graphe::ajoutArc(s2, s1);

    int n = nbSommet();
    if (s1 == s2 || s1 > n || s2 > n || s1 < 1 || s2 < 1)
        return;

    d_cout[s1][s2] = d_cout[s2][s1] = c;
}

void graphenov::supprArc(int s1, int s2)
{
    graphe::supprArc(s1, s2);
    graphe::supprArc(s2, s1);

    int n = nbSommet();
    if (s1 == s2 || s1 > n || s2 > n || s1 < 1 || s2 < 1)
        return;

    d_cout[s1][s2] = d_cout[s2][s1] = INT_MAX;
}

void graphenov::ajoutSommet()
{
    int n = nbSommet();

    graphe::ajoutSommet();

    if (n == 0)
    {
        delete d_cout;

        d_cout = new int*[2];
        d_cout[0] = new int[1];
        d_cout[1] = new int[2];
        d_cout[0][0] = 1;
        d_cout[1][0] = 1;
        d_cout[1][1] = 0;

        return;
    }

    int **cout = new int*[n + 2];
    cout[0] = new int[1];
    for (int i = 1; i <= (n + 1); ++i)
        cout[i] = new int[n + 2];

    for (int i = 0; i <= (n + 1); ++i)
        cout[i][0] = n + 1;

    for (int i = 1; i <= (n + 1); ++i)
        for (int j = 1; j <= (n + 1); ++j)
        {
            if (j == n + 1 || i == n + 1)
                cout[i][j] = INT_MAX;
            else
                cout[i][j] = d_cout[i][j];
        }

    setCout(cout);
}

void graphenov::supprSommet(int s)
{
    graphe::supprSommet(s);

    if (d_fs == nullptr || d_aps == nullptr)
    {
        delete d_cout;
        d_cout = nullptr;
        return;
    }

    int n = nbSommet();
    if (s > n || s < 1)
        return;

    int **cout = new int*[n];
    cout[0] = new int[1];
    for (int i = 1; i <= (n - 1); ++i)
    {
        cout[i] = new int[n];
        cout[i][0] = n;
    }

    for (int i = 1, k = 1; i <= n, k <= (n - 1);)
    {
        if (i == s)
            ++i;
        for (int j = 1, l = 1; j <= n, l <= (n - 1);)
        {
            if (j == s)
                ++j;
            cout[k][l] = d_cout[i][j];
        }
    }




    setCout(cout);
}
void graphenov::dedoublerAretes()
{
    if (d_aps == nullptr || d_fs == nullptr)
        return;

    int sommet = 1;
    for (int i = 1; i <= d_fs[0]; ++i)
        if (d_fs[i] == 0)
            ++sommet;
        else
            ajoutArc(d_fs[i], sommet, d_cout[sommet][d_fs[i]]);
}


void graphenov::Kruskal(int **&arrete)
{
    int n = d_aps[0];
    int s;
    int *cfc = new int[n + 1];

    int *nb = new int[n + 1]; //le nombre de valeurs de la composante connexe
    int *ch = new int[n + 1]; //le chainage
    int *prem = new int[n + 1]; //le premier élement de la composante connexe

    arrete = new int*[n + 1];

    for (int i = 1; i <= n; i++)
    {
        nb[i] = 1;
        cfc[i] = i;
        prem[i] = i;
        ch[i] = 0;
        arrete[i] = new int[n];
        for (int j = 1; j <= n; j++)
        {
            arrete[i][j] = 0;
        }
    }


    int d_i, d_k, k;

    int min;

    bool changement = true;
    while (changement)
    {

        changement = false;
        min = INT_MAX;
        for (int i = 1; i <= n; i++)
        {

            for (int j = d_aps[i]; (k = d_fs[j])>0; j++)
                if ((cfc[i] != cfc[k]) && min>d_cout[i][k])
                {
                    //test

                    min = d_cout[i][k];
                    d_i = i;
                    d_k = k;
                    changement = true;
                }
        }
        if (changement)
        {
            arrete[d_i][d_k] = 1;
            arrete[d_k][d_i] = 1;

            //joindre mtn

            s = prem[d_k];

            cfc[s] = cfc[d_i];

            while (ch[s] != 0)
            {

                s = ch[s];

                cfc[s] = cfc[d_i];

            }

            ch[s] = prem[d_i];
            s = prem[d_i];
            while (ch[s] != 0)
            {
                prem[s] = prem[d_k];
                s = ch[s];
            }
            prem[s] = prem[d_k];

            prem[d_i] = prem[d_k];

            int p = prem[d_i];
            int cptt = 0;

            while (cptt<20 && ch[p] != 0)
            {

                cptt++;
                p = ch[p];
            }
        }
    }
}

bool graphenov::Dijkstra(int s, int* &d, int* &pere) const
{
    int MAXPOIDS = INT_MAX;
    int n = d_aps[0];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (d_cout[i][j]<0)
                return false;
        }
    }
    int j, x, u;
    d = new int[n + 1];
    d[0] = n;

    pere = new int[n + 1];
    pere[0] = n;
    bool* ins = new bool[n + 1];


    for (int i = 1; i <= n; ++i)
    {
        ins[i] = true;
        d[i] = d_cout[s][i];
        pere[i] = -1;
        if (d_cout[s][i] == INT_MAX)
            d[i] = MAXPOIDS;
    }
    d[s] = 0;
    pere[s] = 0;

    for (int k = d_aps[s], t; (t = d_fs[k])>0; k++)
    {
        pere[t] = s;
    }
    ins[s] = false;

    while (--n > 0)
    {
        j = dmin(ins, d);
        if (j == -1)
            return true;
        if (d[j] == MAXPOIDS)
        {
            d[s] = 0;
            return false;
        }

        ins[j] = false;
        for (int k = d_aps[j]; (u = d_fs[k]) > 0; k++) // Parcourt des successeurs
        {
            if ((ins[u]) && (d_cout[j][u] != MAXPOIDS))
            {
                x = d[j] + d_cout[j][u];
                if (x < d[u])
                {
                    d[u] = x;
                    pere[u] = j;
                }
            }
        }
    }
    d[s] = 0;
    return true;

}

int graphenov::dmin(bool* ins, int *d) const
{
    int n = d_aps[0];
    int s = -1;
    int min = INT_MAX;
    for (int i = 1; i <= n; ++i)
    {
        if (ins[i] == true)
        {
            if (d[i] < min)
            {
                min = d[i];
                s = i;
            }
        }
    }
    return s;
}

