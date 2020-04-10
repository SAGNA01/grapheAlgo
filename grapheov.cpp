#include "grapheov.h"
#include"grapheonv.h"
#include<limits.h>
using namespace std;

grapheov::grapheov() : graphe{}, d_cout{nullptr}
{}
grapheov::grapheov(int *fs, int *aps, int **couts) : graphe{fs, aps}{
    if (fs == nullptr || aps == nullptr) {
            d_cout = nullptr;
            return;
        }

        int n = nbSommet();
        d_cout = new  int*[n + 1];
        d_cout[0] = new int[1];
        d_cout[0][0] = n;
        for (int i = 1; i <= n; ++i)
            d_cout[i] = new int[n + 1];
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                d_cout[i][j] = couts[i][j];
}

grapheov::~grapheov(){
    int n = nbSommet();
    if (n != 0)
        for (int i = 0; i <= n; ++i)
            delete d_cout[i];
    delete d_cout;
}

void grapheov::afficher() const{
    graphe::afficher();
    int n = nbSommet();
    std::cout<< endl;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (d_cout[i][j] == INT_MAX)
                std::cout << "-1" << " ";
            else
                std::cout << d_cout[i][j] << " ";
        }
        std::cout << endl;
    }
}


void grapheov::ajoutArc(int s1, int s2, int c)
{
    graphe::ajoutArc(s1, s2, 0);

    int n = nbSommet();
    if (s1 == s2 || s1 > n || s2 > n || s1 < 1 || s2 < 1)
        return;

    d_cout[s1][s2] = c;
}

void grapheov::supprArc(int s1, int s2)
{
    graphe::supprArc(s1, s2);

    int n = nbSommet();
    if (s1 == s2 || s1 > n || s2 > n || s1 < 1 || s2 < 1)
        return;

    d_cout[s1][s2] = INT_MAX;
}

void grapheov::ajoutSommet()
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
        d_cout[1][1] = INT_MAX;

        return;
    }

    int **couts = new int*[n + 2];
    couts[0] = new int[1];
    for (int i = 1; i <= (n + 1); ++i)
        couts[i] = new int[n + 2];

    for (int i = 0; i <= (n + 1); ++i)
        couts[i][0] = n + 1;

    for (int i = 1; i <= (n + 1); ++i)
        for (int j = 1; j <= (n + 1); ++j)
        {
            if (j == n + 1 || i == n + 1)
                couts[i][j] = INT_MAX;
            else
                couts[i][j] = d_cout[i][j];
        }

    setCout(couts);
}

void grapheov::supprSommet(int s)
{
    graphe::supprSommet(s);

    if (d_fs == nullptr || d_aps == nullptr)
    {
        delete d_cout;
        d_cout = nullptr;
        return;
    }

    int n = nbSommet() + 1;
    if (s > n || s < 1)
        return;

    int **couts = new int*[n];
    couts[0] = new int[1];
    couts[0][0] = n;
    for (int i = 1; i <= n; ++i)
    {
        couts[i] = new int[n];
        couts[i][0] = n;
    }

    int k = 0;
    int l = 0;

    for (int i = 1; i <= n; ++i)
    {
        if (i != s)
        {
            ++k;
            for (int j = 1; j <= n; ++j)
            {
                if (j != s)
                {
                    ++l;
                    d_cout[k][l] = d_cout[i][j];
                }
            }
            l = 0;
        }
    }
    d_cout[0][0] --;
    setCout(couts);
}

int** grapheov::Cout() const
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
        for (int j = 0; j <= n; ++j)
            c[i][j] = d_cout[i][j];

    return c;
}

bool grapheov::setCout(int **couts){
    if (couts == nullptr)
    {
        delete d_cout;
        d_cout = nullptr;
        return true;
    }

    int n = couts[0][0];
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
        for (int j = 1; j <= n; ++j)
            d_cout[i][j] = couts[i][j];
    return true;
}

int* grapheov::nb_pred() const{
    int n = d_aps[0];
    int *ddi = new int[n + 1];

    for (int i = 0; i <= n; ++i)
        ddi[i] = 0;

    for (int i = 1; i <= d_fs[0]; ++i)
        ddi[d_fs[i]]++;

    ddi[0] = n;
    return ddi;
}

int* grapheov::dist(int s) const
{
    int n = d_aps[0], v = 0, t = 0, q = 1, p = 1;
    int *d = new int[n + 1];
    d[0] = n;
    for (int i = 1; i <= n; ++i)
        d[i] = -1;
    d[s] = 0;
    int* fa = new int[n + 1];
    fa[0] = n;
    fa[1] = s;
    //Le bloc courant est compris entre t+1 et q
    while (t<q)
    {
        v++;
        for (int k = t + 1; k <= q; ++k)
        {
            int l = d_aps[fa[k]];
            while (d_fs[l] != 0)
            {
                if (d[d_fs[l]] == -1)
                {
                    d[d_fs[l]] = v;
                    p++;
                    fa[p] = d_fs[l];
                }
                l++;
            }
        }
        t = q;
        q = p;
    }
    delete[] fa;

    return d;
}

int* grapheov::rang(int *&pilch, int *&prem) const
{
    int n = d_aps[0];
    int s, k, t, h;
    pilch = new int[n + 1];
    prem = new int[n + 1];
    int *rang = new int[n + 1];
    for (int i = 0; i <n + 1; ++i)
        rang[i] = -1;
    rang[0] = n;

    pilch[0] = 0;

    int* ddi = nb_pred();

    pilch[0] = 0;

    for (int i = 1; i <= n; ++i) //Empiler là ou ddi est nul
    {
        if (ddi[i] == 0)
        {
            pilch[i] = pilch[0];
            pilch[0] = i;
        }
    }
    k = -1; // rang
    s = pilch[0]; // 1e element
    prem[0] = s;
    while (pilch[0] != 0)
    {
        k++; //rang courant
        pilch[0] = 0; // préparer rang suivant
        while (s > 0) // sommet du bloc courant
        {
            rang[s] = k;
            h = d_aps[s]; // récupérer l'adresse du 1e successeur
            t = d_fs[h]; // récupérer la valeur du sommet du successeur de s
            while (t > 0) // tant qu'il y a des successeurs au sommet s
            {
                ddi[t]--;
                if (ddi[t] == 0)
                {
                    pilch[t] = pilch[0];
                    pilch[0] = t;
                }
                h++;
                t = d_fs[h];
            }
            s = pilch[s];
        }
        s = pilch[0];
        prem[k + 1] = s;
    }
    return rang;
}

int* grapheov::fs2fp() const
{
    int *ddi = nb_pred();
    int n = ddi[0], m = d_fs[0];
    int *app = new int[n + 1],
        *fp = new int[m + 1];

    fp[0] = m;
    app[0] = n;
    app[1] = 1;

    for (int i = 2; i <= n; ++i)
        app[i] = app[i - 1] + ddi[i - 1] + 1;

    int j = 1;

    for (int i = 1; i <= m; ++i)
        if (d_fs[i] == 0)
            ++j;
        else
            fp[app[d_fs[i]]++] = j;

    for (int i = n; i >= 1; --i)
    {
        fp[app[i]] = 0;
        app[i] = app[i - 1] + 1;

    }
    app[1] = 1;

    return fp;
}

int grapheov::dmin(bool* ins, int *d) const
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

bool grapheov::Dijkstra(int s, int* &d, int* &pere) const
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



bool grapheov::circuit(int* fs, int* aps, int* statut, int s)
{
    statut[s] = 1;
    for (int i = aps[s], k; (k = fs[i])>0; i++)
    {
        if (statut[k] == 0)
        {
            return circuit(fs, aps, statut, k);
        }
        else
        {
            return false;
        }
    }

    return true;


}

int* grapheov::det_pred() const
{
    int *pilch, *prem;
    int* rg = rang(pilch, prem);
    int n = d_aps[0], t;
    int *pred = new int[n + 1];

    for (int i = 0; i <= d_aps[0]; i++)
        pred[i] = 0;

    for (int s = 1; s <= n; ++s)
        for (int k = d_aps[s]; (t = d_fs[k]) > 0; ++k)
            if (rg[t] == rg[s] + 1)
                pred[t] = s;

    pred[0] = d_aps[0];
    return pred;
}

//si che[0]==0 => pas de chemin
int* grapheov::chemin(int s) const
{

    int* pred = det_pred();
    int *pilch, *prem;
    int *rg = rang(pilch, prem);

    int d = rg[s];
    int a = s;

    int* che = new int[d + 1];

    che[d] = s;

    while (pred[a] != 0)
    {

        a = pred[a];
        che[--d] = a;
    }
    che[0] = rg[s];

    return che;
}

int* grapheov::fs2fp_(int *fs)
{
    grapheonv g(fs, graphe::fs2aps(fs));
    int *ddi = g.nb_pred();
    int n = ddi[0], m = fs[0];
    int *app = new int[n + 1],
        *fp = new int[m + 1];

    fp[0] = m;
    app[0] = n;
    app[1] = 1;

    for (int i = 2; i <= n; ++i)
        app[i] = app[i - 1] + ddi[i - 1] + 1;

    int j = 1;

    for (int i = 1; i <= m; ++i)
        if (fs[i] == 0)
            ++j;
        else
            fp[app[fs[i]]++] = j;

    for (int i = n; i >= 1; --i)
    {
        fp[app[i]] = 0;
        app[i] = app[i - 1] + 1;

    }
    app[1] = 1;

    return fp;

}

void grapheov::ordonnancement(int *&fs, int*&tab)
{
    int n = d_aps[0];
    int k;
    bool *ddi = new bool[n + 1];

    int *num = new int[n + 1];
    for (int y = 1; y <= n; y++)
    {
        num[y] = y;
        ddi[y] = false;

    }

    int i = 1;
    bool change;
    while (i <= n)
    {
        change = false;
        for (int j = d_aps[i]; !change && (k = d_fs[j])>0; j++)
        {
            ddi[k] = true;
            if (num[k]<num[i])
            {
                swap(num[i], num[k]);
                change = true;
            }
        }
        if (change)
        {
            i = 0;
        }
        i++;
    }


    fs = new int[n*n];
    int cpt = 1;

    for (int i = 1; i <= n; i++)
    {
        if (ddi[i] == false)
        {
            fs[cpt] = num[i] + 1;
            cpt++;
        }
    }
    fs[cpt++] = 0;
    int nbdde;


    tab = new int[n + 1];


    for (int i = 1; i <= n; i++)
    {
        tab[num[i]] = i;
    }

    for (int i = 1; i <= n; i++)
    {
        nbdde = 0;
        for (int f = d_aps[tab[i]]; (k = d_fs[f])>0; f++)
        {
            fs[cpt++] = num[k] + 1;
            nbdde++;
        }
        if (nbdde == 0)
            fs[cpt++] = n + 2;
        fs[cpt++] = 0;
    }

    fs[cpt] = 0;
    fs[0] = cpt;


    cpt = 1;
    k = 1;

    while (cpt<fs[0])
    {
        if (fs[cpt] == 0)
        {
            k = cpt;
        }
        else
            if (fs[cpt] != 0 && fs[cpt + 1] != 0 && fs[cpt]>fs[cpt + 1])
            {
                swap(fs[cpt], fs[cpt + 1]);
                cpt = k - 1;
            }
        cpt++;
    }



}

grapheov* grapheov::Critique(int* &lc, int* &fpc, int*& appc, int *coutotal)
{
    int*fs;


    int*tab;
    ordonnancement(fs, tab);

    int*aps = graphe::fs2aps(fs);

    int *fp;
    fp = grapheov::fs2fp_(fs);

    int *app = graphe::fs2aps(fp);
    int n = app[0];
    int m = fp[0];
    int k;
    int longueur;

    int **c = new int*[n + 1];
    c[0] = new int[n];
    c[0][0] = n;
    for (int i = 1; i <= n; ++i)
    {
        c[i] = new int[n + 1];
        c[0][0] = n;
        for (int j = 1; j <= n; ++j)
            c[i][j] = INT_MAX;
    }

    int g;
    for (int i = 2; i <= n - 1; i++)
        for (int j = aps[i]; (g = fs[j])>0; j++)
        {
            if (g != n)
            {
                c[i][g] = coutotal[tab[i - 1]];

            }
            else
            {
                c[i][g] = coutotal[tab[i - 1]];

            }


        }

    for (int j = aps[1]; (g = fs[j])>0; j++)
        c[1][g] = 0;
        lc = new int[n + 1];
        appc = new int[n + 1];
        fpc = new int[m + 1];
        fpc[0] = fp[0];
        lc[1] = 0;
        appc[1] = 1;
        int kc = 1; //indice dans fpc, pointe sur la derniere valeur mise dans fpc
        for (int i = 2; i <= n; ++i)
        {
            //Calcul de lc[i] en fonction des predecesseurs de i
            k = app[i];
            lc[i] = 0;
            appc[i] = kc + 1;

            while (fp[k]>0)
            {
                if (tab[fp[k]])
                longueur = lc[fp[k]] + c[fp[k]][fs[aps[fp[k]]]];
                else
                   longueur = lc[fp[k]];

            if (longueur >= lc[i])
            {
                if (longueur > lc[i])
                {
                    kc = appc[i];
                    fpc[kc] = fp[k];
                    lc[i] = longueur;
                }
                else {
                    kc++;
                    fpc[kc] = fp[k];
                }
            }
            k++;
        }
        kc++;
        fpc[kc] = 0;
    }

    fpc[0] = kc;
    fpc[1] = 0;
    lc[0] = n;
    appc[0] = n;


    return new grapheov(fs, aps, c);

}

