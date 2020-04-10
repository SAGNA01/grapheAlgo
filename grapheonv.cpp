#include "grapheonv.h"

grapheonv::grapheonv() : graphe{}
{}

grapheonv::grapheonv(int *fs, int *aps) : graphe{fs, aps}
{}

int* grapheonv::nb_pred() const
{
    int n = d_aps[0];
    int *ddi = new int[n + 1];

    for (int i = 0; i <= n; ++i)
        ddi[i] = 0;

    for (int i = 1; i <= d_fs[0]; ++i)
        ddi[d_fs[i]]++;

    ddi[0] = n;

    return ddi;
}

int* grapheonv::dist(int s) const
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

int* grapheonv::rang(int *&pilch, int *&prem) const
{
    int n = d_aps[0];
    int s, k, t, h;
    pilch = new int[n + 1];
    prem = new int[n + 1];
    int *rang = new int[n + 1];
    rang[0] = n;
    for (int i = 1; i <n + 1; ++i)
        rang[i] = -1;

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

int* grapheonv::fs2fp() const
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

int* grapheonv::det_pred() const
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
int* grapheonv::chemin(int s) const
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

void grapheonv::Tarjan(int **dist,int *&cfc, int *&prem, int *&pilch)
{
    int  nb = 0, l;
    dist[0][0] = nb;
      int n = dist[0][0];
      prem = new int[n+1];
      cfc = new int [n+1];
      pilch = new int [n+1];
      for(int i = 1; i<=n; i++)
      {
          cfc[i] =0; cfc[i] =n;
      }


      for(int i = 1; i<=n; i++){
          if(cfc[i] == 0){
              nb++;
              prem[nb] = i;
              cfc[i] = nb;
              l = i;
              for(int j = i+1; j <= n; j++)
              {
                    if((cfc[j]!=0) && (dist[i][j] != -1) && (dist[j][i] != -1))
                    {
                        pilch[l] = j;
                        l = j;
                        cfc[j] = nb;
                    }
              }//fin j
              pilch[l] = 0;
          }// fin if
    }//fin i
     prem[0] = nb;
}
