#ifndef WGRAPHE_H
#define WGRAPHE_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTableWidget>
#include <QtGui>
#include <QWidget>
#include "mainwindow.h"

#include "graphe.h"
#include "sommet.h"
#include "arc.h"

class sommet;
class arc;

class wgraphe : public QWidget
{
    Q_OBJECT
      friend class MainWindow;
      friend class sommet;
      friend class Couts;
public:
    wgraphe(QWidget * parent);
    ~wgraphe();

    //dessiner le graphe courant
    void dessiner();
    //modification du graphe courant
    void setGraphe(graphe *g);
    void mousePressEvent(QMouseEvent *e);

    //accesseurs
    bool getSS() const { return ss; }
    bool getAA() const { return aa; }
    bool getSA() const { return sa; }
    bool getE() const { return e; }

    //supprime le sommet de numéro num
    void supprimerSommet(int num);
    //ajouter un arc entre le sommet s1 et s2 avec le cout
    void ajouterArc(int s1, int s2, int cout);
    //supprimer l'arc entre s1 et s2
    void supprimerArc(int s1, int s2);
    //colorier l'arc entre s1 et s2 avec la couleur c
    void colorierArc(int s1, int s2, QColor c);
    graphe *getGCourant() const{ return gcourant; }

    public slots:
    //lire le code de Prüfer dans une QTableWidget
    void lirePrufer();
    //créer puis afficher le graphe associé au code de Prüfer donné
    void creerPrufer();
    //lit l'ordonnancement à creer dans une QTableWidget
    void ordonnancement();
    //creer le graphe associe a l'ordonnancement donne
    void creerOrdo();

private: 
    //pointeur sur la fenetre principale
    QWidget *d_parent;
    //scene qui acceuille le graphe
    QGraphicsScene scene;
    QGraphicsView *view;
    //tab le est utilisé pour lire le code de Prüfer et l'ordonnancement
    QTableWidget *table;
    //tableau de pointeur sur les différents sommets du graphe
    QVector<sommet *> item;
    //tableau de pointeur sur les différents arcs du graphe
    QVector<arc *> line;
    //tableau de pointeur sur les différents couts des arêtes du graphe
    QVector<QGraphicsTextItem *> txt;
    //tableau qui contient pour chaque sommet son enregistrement complexe
    QVector<QString> complexe;
    //graphe courant(OV, NOV, NONV ou ONV)
    graphe *gcourant;
    //Widget dans laquelle le codage de Prüfer est saisi
    QWidget *prufer;
    //widget pour l'ordonnancement
    QWidget *w;
    //TableWidget pour la saisie de l'odonnancement
    //QTableWidget *table ;

    //etat des boutons
    bool as, aa, ss, sa, value, oriente, e;
    //sommet *de, *a ;
    int dep, arr;
    int taille_prufer;

    static const int HAUT = 700, LARG = 700, RAYON = 300;
};

#endif // WGRAPHE_H
