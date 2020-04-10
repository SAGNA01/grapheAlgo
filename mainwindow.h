#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPainter>
#include <QTextEdit>

#include <QVBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>

#include "wgraphe.h"
#include "graphe.h"
#include "grapheov.h"
#include "graphenonv.h"
#include "graphenov.h"
#include "grapheonv.h"

namespace Ui {
class MainWindow;
}

class wgraphe;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    //explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void afficherTab(int *tab);

    public slots:
    //menu fichier
    void chargerGraphe();
    void sauvegarderGraphe();
    void nouveauGraphe();

    //dockwidget
    void setAjoutSom();
    void setSupprSom();
    void setAjoutArc();
    void setSupprArc();
    void setQuitter();
    //void setEnregistrement();

    //menu graphe
    void afficherMatriceAdj();
    void afficherMatriceCouts();
    void rang();
    void distances();
    void dessinerDijkstra();
    void dessinerTarjan();
    void redessinerGraphe();
    void coderPrufer();
    void dessinerKruskal();

    //description
    void descrDisjktra();
    void descrKruskal();
    void descrOrdo();
    void descrPruffer();
    void descrTarjan();

private:

    //widget du graphe
    wgraphe *wid;
    //widget et table pour l'affichage des distances
    QWidget *w;
    QTableWidget *table;

    //élement de la boite à outils
    QDockWidget *dock;
    QDockWidget *dock_above;
    QWidget *dockwid;
    QWidget *dockwid_above;
    QPushButton *btnAjouteSommet, *btnSupprSommet, *btnAjoutArc, *btnSupprArc, *btnNouveau, *btnQuitter, *btnCharger;
    QCheckBox *bcxValue, *bcxOriente;
    QHBoxLayout *dockLayout;
    QVBoxLayout *dockLayout_above;

    //élements du menu
    QMenu *fichier;
    QMenu *graph;
    QMenu *apropos;
    QMenu *outils;
    QMenu *editMenu;


    //action des menu
    //QAction *quitter;
    QAction *nveau;
    QAction *propos;
    // QAction *charger;
    QAction *sauvegarder;
    QAction *barre_outils;
    QAction *f_djikstra;
    QAction *f_kruskal;
    QAction *f_tarjan;
    QAction *f_ordo;
    QAction *f_pruffer;

    QAction *dessiner;
    QAction *matrice;
    QAction *couts;
    QAction *rg;
    QAction *dist;
    QAction *Dijkstra;
    QAction *Tarjan;
    QAction *prufer;
    QAction *decoderprufer;
    QAction *kruskal;
    QAction *ordo;
    QAction *pointA;
    QAction *isthmes;

    //largeur et hauteur de la fenetre
    static const int HAUT = 900, LARG = 800;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
