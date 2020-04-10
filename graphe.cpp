#include "graphe.h"
#include "liste.h"
#include "grapheOV.h"
#include "grapheNOV.h"
#include "grapheNONV.h"
#include "grapheONV.h"
#include<typeinfo>

graphe::graphe() : d_fs{nullptr}, d_aps{nullptr}
{}
graphe::graphe(int *fs, int *aps) : d_fs{nullptr}, d_aps{nullptr}
{
    if (fs == nullptr || aps == nullptr)
            return;

        int n = fs[0];
        int m = aps[0];
        d_fs = new  int[n + 1];
        d_aps = new int[m + 1];

        for (int i = 0; i <= n; ++i)
            d_fs[i] = fs[i];
        for (int i = 0; i <= m; ++i)
            d_aps[i] = aps[i];

}

graphe::graphe(int **adj) : d_fs(nullptr), d_aps(nullptr)
{
    if (adj == nullptr)
        return;

    int n = adj[0][0];
    int m = adj[0][1];

    d_fs = new int[n + m + 1];
    d_aps = new int[n + 1];

    d_fs[0] = n + m;
    d_aps[0] = n;

    int cptfs = 1;

    for (int i = 1; i <= n; ++i)
    {
        d_aps[i] = cptfs;
        for (int j = 1; j <= n; ++j)
        {
            if (adj[i][j] == 1)
                d_fs[cptfs++] = j;
        }
        d_fs[cptfs++] = 0;
    }
}

graphe::~graphe()
{
    delete d_fs;
    delete d_aps;
}

graphe& graphe::operator=(const graphe &g)
{
    return *(new graphe(g.d_fs, g.d_aps));
}

int graphe::nbSommet() const
{
    if (d_aps == nullptr)
        return 0;

    return d_aps[0];
}

int* graphe::fs() const
{
    if (d_fs == nullptr)
        return nullptr;

    int n = d_fs[0];
    int *nfs = new int[n + 1];

    for (int i = 0; i <= n; ++i)
        nfs[i] = d_fs[i];

    return nfs;
}

int* graphe::aps() const
{
    if (d_aps == nullptr)
        return nullptr;

    int n = d_aps[0];
    int *naps = new int[n + 1];
    for (int i = 0; i <= n; ++i)
        naps[i] = d_aps[i];
    return naps;
}

void graphe::fs_aps() const
{
    if (d_fs == nullptr || d_aps == nullptr)
    {
        cout << "Graphe vide" << endl;
        return;
    }
    int n = d_aps[0],
        m = d_fs[0];
    for (int i = 1; i <= n; ++i)
        cout << d_aps[i] << " ";
    cout << endl;
    for (int i = 1; i <= m; ++i)
        cout << d_fs[i] << " ";
    cout << endl;
}

void graphe::setFs(int *fs)
{
    delete d_fs;

    if (fs == nullptr)
    {
        d_fs = nullptr;
        return;
    }

    int n = fs[0];
    d_fs = new int[n + 1];

    for (int i = 0; i <= n; ++i)
        d_fs[i] = fs[i];
}

void graphe::setAps(int *aps)
{
    delete d_aps;

    if (aps == nullptr)
    {
        d_aps = nullptr;
        return;
    }

    int n = aps[0];
    d_aps = new int[n + 1];

    for (int i = 0; i <= n; ++i)
        d_aps[i] = aps[i];
}

void graphe::afficher() const
{
    if (d_aps == nullptr || d_fs == nullptr)
    {
        cout << "graphe courant vide" << endl;
        return;
    }

    int m = d_aps[0];
    for (int i = 1; i <= m; ++i)
    {
        cout << "Succ de " << i << " : ";
        for (int k = d_aps[i], j; (j = d_fs[k]) > 0; ++k)
            cout << j << " ";

        cout << "\n";
    }

}

void graphe::ajoutArc(int s1, int s2, int c)
{
    int nbSom = nbSommet();

    if (s1 == s2 || s1 > nbSom || s2 > nbSom || s1 == 0 || s2 == 0)
        return;

    //on cherche si s2 est deja succ de s1
    int i = d_aps[s1], n = d_fs[i];
    while (n != 0 && n != s2)
    {
        i++;
        n = d_fs[i];
    }
    //si n==0 => s2 n'est pas succ de s1 donc on l'ajoute a ses succ
    if (n == 0)
    {
        int n = d_fs[0] + 1;
        int *fs = new int[n + 1];

        memcpy(fs, d_fs, (d_aps[s1]) * sizeof(int));
        fs[d_aps[s1]] = s2;
        memcpy(fs + d_aps[s1] + 1, d_fs + d_aps[s1], (n - d_aps[s1])*sizeof(int));

        delete d_fs;

        d_fs = fs;
        d_fs[0] = n;

        int m = d_aps[0];
        for (int i = s1 + 1; i <= m; d_aps[i++]++);
    }
}

void graphe::supprArc(int s1, int s2)
{
    int nbSom = nbSommet();

    if (s1 == s2 || s1 > nbSom || s2 > nbSom || s1 == 0 || s2 == 0)
        return;

    int i = d_aps[s1], n = d_fs[i];
    while (n != 0 && n != s2)
    {
        i++;
        n = d_fs[i];
    }

    if (n == 0)
        //s2 n'est pas succ de s1
        return;

    n = d_fs[0];
    int *fs = new int[n];

    memcpy(fs, d_fs, i * sizeof(int));
    memcpy(fs + i, d_fs + i + 1, (n - i - 1)*sizeof(int));

    delete d_fs;

    d_fs = fs;
    d_fs[0] = n - 1;

    int m = d_aps[0];
    for (int i = s1 + 1; i <= m; d_aps[i++]--);
}

void graphe::ajoutSommet()
{
    int *fs, *aps;

    if (d_aps == nullptr || d_fs == nullptr)
    {
        aps = new int[2];
        aps[0] = 1;
        aps[1] = 1;

        fs = new int[2];
        fs[0] = 1;
        fs[1] = 0;
    }
    else
    {
        int n = d_aps[0],
            m = d_fs[0];

        fs = new int[m + 2];
        aps = new int[n + 2];

        memcpy(fs, d_fs, (m + 1)*sizeof(int));
        fs[0] = d_fs[0] + 1;
        fs[m + 1] = 0;

        memcpy(aps, d_aps, (n + 1)*sizeof(int));
        aps[0] = d_aps[0] + 1;
        aps[n + 1] = m + 1;
    }

    setFs(fs);
    setAps(aps);
}

void graphe::supprSommet(int s)
{
    if (d_fs == nullptr || d_aps == nullptr)
        return;

    int n = d_aps[0],
        m = d_fs[0];

    //si le sommet n'est pas dans le graphe on ne fait rien
    if (s > n || s == 0)
        return;

    //si on supprime le dernier sommet on vide fs et aps
    if (n == 1)
    {
        delete d_fs;
        d_fs = nullptr;
        delete d_aps;
        d_aps = nullptr;
        return;
    }

    int diff;
    //on supprime le dernier sommet
    if (s == n)
        diff = m - d_aps[n] + 1;
    //on supprime un autre sommet
    else
        diff = d_aps[s + 1] - d_aps[s];

    int *aps = new int[n],
        *fs = new int[m - diff + 1];

    if (s != n)
    {
        memcpy(fs, d_fs, d_aps[s] * sizeof(int));
        memcpy(fs + d_aps[s], d_fs + d_aps[s + 1], (m - d_aps[s + 1] + 1)*sizeof(int));
    }
    else
        //on supprime le dernier sommet
        memcpy(fs, d_fs, sizeof(int)*(m - diff + 1));

    fs[0] = m - diff;
    aps[0] = n - 1;
    aps[1] = 1;

    //on compte le nombre de fois que s est sucesseur d'un sommet
    int cpt = 0, n2 = fs[0];

    for (int i = 1; i <= n2; ++i)
        if (fs[i] == s)
            cpt++;


    int *fs2 = new int[n2 - cpt + 1];
    fs2[0] = n2 - cpt;

    //on suppr s lorsqu il est successeur d un sommet
    for (int i = 1, j = 1; i <= n2 - cpt, j <= m - diff;)
    {
        if (fs[j] == s)
            ++j;
        else
        {
            fs2[i] = fs[j];
            ++i;
            ++j;
        }
    }

    //le numero de tous les sommet de numero superieur a s est diminue de 1
    for (int i = 1; i <= n2 - cpt; ++i)
        if (fs2[i] != 0)
            if (fs2[i] > s)
                fs2[i] --;

    //on reconstruit aps
    int sommet = 1;
    for (int i = 1; i <= n2 - cpt; ++i)
    {
        if (fs2[i] == 0)
            aps[++sommet] = i + 1;
    }

    setFs(fs2);
    setAps(aps);

}

liste& graphe::fs2liste() const
{
    return *(new liste(*this));
}

int** graphe::fs2adj() const
{
    int **adj;

    int n = d_aps[0];
    int m = d_fs[0];
    adj = new int*[n + 1];
    adj[0] = new int[2];
    adj[0][0] = n;
    adj[0][1] = m - n; // nb d'arcs
    int cpt = 1;
    for (int i = 1; i <= n; ++i)
    {
        adj[i] = new int[n + 1];
        for (int j = 1; j <= n; ++j)
            adj[i][j] = 0;

        while (d_fs[cpt] != 0)
            adj[i][d_fs[cpt++]] = 1;

        ++cpt;
    }
    return adj;
}

graphe* graphe::lire(std::ifstream &is)
{
    if (!is.good())
        return nullptr;

    //on lit le type de graphe
    int n2;
    is >> n2;

    if (n2<1 || n2>4)
        return nullptr;

    int n, m, cpt = 2;
    is >> n >> m;

    int *fs = new int[n + 1];
    fs[0] = n;

    int *aps = new int[m + 1];
    aps[0] = m;
    aps[1] = 1;

    for (int i = 1; i <= n; ++i)
    {
        is >> fs[i];

        if (fs[i] == 0 && cpt <= m)
        {
            aps[cpt] = i + 1;
            ++cpt;
        }
    }

    if (n2 == 1)
        return new grapheONV(fs, aps);
    else if (n2 == 4)
        return new grapheNONV(fs, aps);
    //si graphe value on lit la matrice des couts
    else if (n2 == 2 || n2 == 3)
    {
        int **cout = new int*[m + 1];
        cout[0] = new int[1];
        cout[0][0] = m;
        for (int i = 1; i <= m; ++i)
        {
            cout[i] = new int[m + 1];
            cout[i][0] = m;
        }

        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= m; ++j)
            {
                int n;
                is >> n;
                cout[i][j] = n;
            }

        if (n2 == 3)
            return new grapheNOV(fs, aps, cout);
        if (n2 == 2)
            return new grapheOV(fs, aps, cout);

    }
    return nullptr;
}

bool graphe::ecrire(graphe& g, std::ofstream &ost)
{
    if (!ost.is_open())
        return false;

    int n2=0;

    if (typeid(g) == typeid(grapheONV))
    {
        n2 = 1;
        ost << n2;
    }
    else if (typeid(g) == typeid(grapheOV))
    {
        n2 = 2;
        ost << n2;
    }
    else if (typeid(g) == typeid(grapheNOV))
    {
        n2 = 3;
        ost << n2;
    }
    else if (typeid(g) == typeid(grapheNONV))
    {
        n2 = 4;
        ost << n2;
    }

    ost << ' ';

    int *d_fs = g.fs(),
        *d_aps = g.aps();

    int n = d_fs[0],
        m = d_aps[0];

    ost << n << ' ' << m;
    for (int i = 1; i <= n; ++i)
        ost << ' ' << d_fs[i];
    ost << endl;

    if (n2 == 3 || n2 == 2)
    {
        int **d_cout;

        if (n2 == 3)
            d_cout = static_cast<grapheNOV*>(&g)->Cout();
        if (n2 == 2)
            d_cout = static_cast<grapheOV*>(&g)->Cout();

        n = d_cout[0][0];
        m = d_cout[0][1];
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
                ost << d_cout[i][j] << ' ';
                ost << endl;
        }
    }

    return true;
}

int* graphe::fs2aps(int *fs)
{
    int n = fs[0], cpt = 0;

    for (int i = 1; i <= n; ++i)
        if (fs[i] == 0)
            ++cpt;

    int *aps = new int[cpt + 1];
    aps[0] = cpt;
    aps[1] = 1;

    cpt = 2;

    for (int i = 1; i <= n; ++i)
        if (fs[i] == 0)
            aps[cpt++] = i + 1;

    return aps;
}

