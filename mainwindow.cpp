#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <fstream>
#include "mainwindow.h" //ProjetGraphe
#include <QDockWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>


MainWindow::MainWindow() : fichier(nullptr), graph(nullptr), apropos(nullptr), btnAjouteSommet(new QPushButton("Ajouter sommet")),
                           btnSupprSommet(new QPushButton("Supprimer sommet")), btnAjoutArc(new QPushButton("Ajouter arc")),
                           btnSupprArc(new QPushButton("Supprimer arc")), btnNouveau(new QPushButton("Nouveau")),
                           btnQuitter(new QPushButton("Quitter")), btnCharger(new QPushButton("Charger")),
                           bcxValue(new QCheckBox("Valué")), bcxOriente(new QCheckBox("Orienté")),QMainWindow{}, ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wid = new wgraphe(this);
    this->resize(HAUT, LARG);
    this->setWindowTitle("Algorithme & Graphe");


    wid->setStyleSheet("background-image:url(C:/Users/okapi/Documents/projet_graphe_v1/projet_graphe_v1/scene.jpg);");
    setCentralWidget(wid);

    fichier = menuBar()->addMenu("&Fichier");
    graph = menuBar()->addMenu("& Algorithmes ");
    outils = menuBar()->addMenu("&Description algorithme");
    apropos = menuBar()->addMenu("&?");

    nveau = fichier->addAction("&Nouveau");
    //charger = fichier->addAction("&Charger");
    sauvegarder = fichier->addAction("&Sauvegarder");

    fichier->addSeparator();
    //quitter = fichier->addAction("&Quitter");
    propos = apropos->addAction("&Qt");

    outils->addSeparator();
    f_djikstra = outils->addAction("&Dijkstra");
    f_kruskal = outils->addAction("&Kruskal");
    f_ordo = outils->addAction("&Ordonancement");
    f_pruffer = outils->addAction("&Pruffer");
    f_tarjan = outils->addAction("&Tarjan");




    matrice = graph->addAction("&Matrice d'adjacence");
    couts = graph->addAction("&Matrice des couts");
    graph->addSeparator();
    dessiner = graph->addAction("&Redessiner graphe");
    graph->addSeparator();
    rg = graph->addAction("&Calcul du rang");
    dist = graph->addAction("&Distances");
    Dijkstra = graph->addAction("&Dijkstra");

    Tarjan = graph->addAction("&Tarjan");
    kruskal = graph->addAction("&Kruskal");
    ordo = graph->addAction("&Ordonnancement");
    graph->addSeparator();
    prufer = graph->addAction("&Coder Prüfer");
    pointA = graph->addAction("&Points d'articulation");
    isthmes = graph->addAction("Isthmes");





    QObject::connect(propos, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    QObject::connect(f_djikstra, SIGNAL(triggered()), this, SLOT(descrDisjktra()));
    QObject::connect(f_kruskal, SIGNAL(triggered()), this, SLOT(descrKruskal()));
    QObject::connect(f_tarjan, SIGNAL(triggered()), this, SLOT(descrTarjan()));
    QObject::connect(f_ordo, SIGNAL(triggered()), this, SLOT(descrOrdo()));
    QObject::connect(f_pruffer, SIGNAL(triggered()), this, SLOT(descrPruffer()));
    QObject::connect(sauvegarder, SIGNAL(triggered()), this, SLOT(sauvegarderGraphe()));
    QObject::connect(nveau, SIGNAL(triggered()), this, SLOT(nouveauGraphe()));



    btnAjouteSommet->setCheckable(true);
    btnSupprSommet->setCheckable(true);
    btnAjoutArc->setCheckable(true);
    btnSupprArc->setCheckable(true);
    //charger->setCheckable(true);
    //enregistrement->setCheckable(true);
    btnQuitter->setCheckable(true);
    bcxValue->setDisabled(true);
    bcxOriente->setDisabled(true);

    QObject::connect(Dijkstra, SIGNAL(triggered()), this, SLOT(dessinerDijkstra()));
    QObject::connect(dessiner, SIGNAL(triggered()), this, SLOT(redessinerGraphe()));
    QObject::connect(matrice, SIGNAL(triggered()), this, SLOT(afficherMatriceAdj()));
    QObject::connect(couts, SIGNAL(triggered()), this, SLOT(afficherMatriceCouts()));
    QObject::connect(rg, SIGNAL(triggered()), this, SLOT(rang()));
    QObject::connect(dist, SIGNAL(triggered()), this, SLOT(distances()));
    QObject::connect(prufer, SIGNAL(triggered()), this, SLOT(coderPrufer()));
    QObject::connect(kruskal, SIGNAL(triggered()), this, SLOT(dessinerKruskal()));
    QObject::connect(decoderprufer, SIGNAL(triggered()), wid, SLOT(lirePrufer()));
    QObject::connect(ordo, SIGNAL(triggered()), wid, SLOT(ordonnancement()));
    dock = new QDockWidget("Outils", this);
    dock->setFloating(false);
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::TopDockWidgetArea, dock);
    dockwid = new QWidget;
    dock->setWidget(dockwid);
    dockLayout = new QHBoxLayout;
    dockLayout->addWidget(bcxValue);
    dockLayout->addWidget(bcxOriente);
    dockLayout->addWidget(btnAjouteSommet);
    dockLayout->addWidget(btnSupprSommet);
    dockLayout->addWidget(btnAjoutArc);
    dockLayout->addWidget(btnSupprArc);
    dockLayout->insertSpacing(6, 20);
    dockwid->setLayout(dockLayout);


    /*here above */
    dock_above = new QDockWidget("barre", this);
    dock_above->setFloating(false);
    dock_above->setFeatures(QDockWidget::NoDockWidgetFeatures | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::LeftDockWidgetArea , dock_above);
    dockwid_above = new QWidget;
    dock_above->setWidget(dockwid_above);
    dockLayout_above = new QVBoxLayout;

    dockLayout_above->addWidget(btnQuitter);
    dockLayout_above->addWidget(btnNouveau);
    dockLayout_above->addWidget(btnCharger);
    dockwid_above->setLayout(dockLayout_above);

    QObject::connect(btnQuitter, SIGNAL(clicked()), this, SLOT(setQuitter()));
    QObject::connect(btnCharger, SIGNAL(clicked()), this, SLOT(chargerGraphe()));
    QObject::connect(btnNouveau, SIGNAL(clicked()), this, SLOT(nouveauGraphe()));
    QObject::connect(btnAjouteSommet, SIGNAL(clicked()), this, SLOT(setAjoutSom()));
    QObject::connect(btnSupprSommet, SIGNAL(clicked()), this, SLOT(setSupprSom()));
    QObject::connect(btnAjoutArc, SIGNAL(clicked()), this, SLOT(setAjoutArc()));
    QObject::connect(btnSupprArc, SIGNAL(clicked()), this, SLOT(setSupprArc()));
    //QObject::connect(enregistrement, SIGNAL(clicked()), this, SLOT(setEnregistrement()));

    QPalette p;
   // QPixmap img ("C:/Users/okapi/Documents/projet_graphe_v1/projet_graphe_v1/graphe2.png");
   // img = img.scaled(this->size(), Qt::IgnoreAspectRatio);
   //  QPalette palette;
   //  palette.setBrush(QPalette::Background, img);
    p.setBrush(QPalette::Background, Qt::gray);
    //dockwid->setStyleSheet("background-color:black;");
    // p.setColor(QPalette::Background, Qt::yellow);
    setPalette(p);

}



MainWindow::~MainWindow()
{
    delete ui;
    delete wid;
    delete btnAjouteSommet;
    delete btnSupprSommet;
    delete btnAjoutArc;
    delete btnSupprArc;
    delete bcxValue;
    delete bcxOriente;
    delete dockLayout;
    delete dockwid;
    delete dock;
    delete btnQuitter;

    delete fichier;
    delete graph;
    delete apropos;

}


void MainWindow::afficherTab(int *d)
{
    w = new QWidget();
    QVBoxLayout *l = new QVBoxLayout;
    w->setWindowTitle("Distances");
    table = new QTableWidget(w);

    int n = d[0];
    /*
    QTableWidgetItem* t ;
    for(int i=0 ; i<n ; ++i)
    {
    t = new QTableWidgetItem(wid->complexe[i]) ;
    table->setHorizontalHeaderItem(0,t) ;
    }
    */
    table->setRowCount(1);
    table->setColumnCount(n);
    table->resize(110 * n, 50);
    for (int i = 1; i <= n; ++i)
        table->setItem(0, i - 1, new QTableWidgetItem(QString::number(d[i])));

    //t = new QTableWidgetItem("Intitulé") ;
    w->setLayout(l);
    l->addWidget(table);
    w->show();
}

void MainWindow::chargerGraphe()
{

    if (wid->gcourant != nullptr)
    {
        int rep = QMessageBox::warning(this, "Charger un graphe", "Supprimmer le graphe courant ?", QMessageBox::Yes | QMessageBox::No);

        if (rep == QMessageBox::No)
            return;
    }
    delete wid->gcourant;
    wid->gcourant = nullptr;
    QString f = QFileDialog::getOpenFileName(this, "Graphe à ouvrir");
    ifstream is(f.toStdString().c_str());
    graphe *gcourant = graphe::lire(is);
    wid->setGraphe(gcourant);

    ifstream is2((f.toStdString() + "complexe").c_str());
    int n;
    is2 >> n;
    wid->complexe.resize(n);
    string tmp;
    for (int i = 0; i<n; ++i)
    {
        is2 >> tmp;
        wid->complexe[i] = tmp.c_str();
    }

    grapheov *gOV = dynamic_cast<grapheov *>(gcourant);
    if (gOV != nullptr)
    {
        bcxValue->setCheckState(Qt::Checked);
        bcxOriente->setCheckState(Qt::Checked);
    }

    graphenonv *gNONV = dynamic_cast<graphenonv *>(gcourant);
    if (gNONV != nullptr)
    {
        bcxValue->setCheckState(Qt::Unchecked);
        bcxOriente->setCheckState(Qt::Unchecked);
    }
    graphenov *gNOV = dynamic_cast<graphenov *>(gcourant);
    if (gNOV != nullptr)
    {
        bcxValue->setCheckState(Qt::Checked);
        bcxOriente->setCheckState(Qt::Unchecked);
    }
    grapheonv *gONV = dynamic_cast<grapheonv *>(gcourant);
    if (gONV != nullptr)
    {
        bcxValue->setCheckState(Qt::Unchecked);
        bcxOriente->setCheckState(Qt::Checked);
    }
    wid->value = bcxValue->isChecked();
    wid->oriente = bcxOriente->isChecked();

    wid->dessiner();
}

void MainWindow::sauvegarderGraphe()
{

    if (wid->gcourant == nullptr)
    {
        //QMessageBox(QMessageBox::Information,"Sauvegarder un graphe", "Impossible de sauvegarder un graphe vide",QMessageBox::Ok) ;
        QMessageBox::information(this, "Sauvegarder un graphe", "Impossible de sauvegarder un graphe vide", QMessageBox::Ok);
        return;
    }

    QString f = QFileDialog::getSaveFileName(this, "Sauvegarder un graphe", "graphe.g");
    ofstream os(f.toStdString().c_str());
    graphe::ecrire(*(wid->gcourant), os);
    os.close();

    ofstream os2((f.toStdString() + "complexe").c_str());
    int n = wid->gcourant->nbSommet();
    os2 << n << std::endl;

    for (int i = 0; i<(wid->item).size(); ++i)
        os2 << ((wid->item[i])->getInfo()).toStdString() << " ";
    os2.close();

}

void MainWindow::nouveauGraphe()
{
    int rep = QMessageBox::warning(this, "Créé un nouveau graphe", "initialiser la scène ?", QMessageBox::Yes | QMessageBox::No);

    if (rep == QMessageBox::No)
        return;

    bool ok;
    QStringList items;
    items << tr("Orienté Valué") << tr("Orienté Non Valué") << tr("Non Orienté Valué") << tr("Non OrientéNon Valué");
    QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("Type de graphe"), items, 0, false, &ok);

    if (!ok)
        return;

    delete wid->gcourant;

    if (item == "Orienté Valué")
    {
        wid->gcourant = new grapheov();
        bcxValue->setCheckState(Qt::Checked);
        wid->value = true;
        bcxOriente->setCheckState(Qt::Checked);
        wid->oriente = true;
    }
    else if (item == "Orienté Non Valué")
    {
        wid->gcourant = new grapheonv();
        bcxValue->setCheckState(Qt::Unchecked);
        bcxOriente->setCheckState(Qt::Checked);
        wid->value = false;
        wid->oriente = true;

    }
    else if (item == "Non Orienté Valué")
    {
        wid->gcourant = new graphenov();
        bcxValue->setCheckState(Qt::Checked);
        bcxOriente->setCheckState(Qt::Unchecked);
        wid->value = true;
        wid->oriente = false;
    }
    else
    {
        wid->gcourant = new graphenonv();
        bcxValue->setCheckState(Qt::Unchecked);
        bcxOriente->setCheckState(Qt::Unchecked);
        wid->value = false;
        wid->oriente = false;
    }

    wid->aa = false;
    btnAjoutArc->setChecked(false);
    wid->as = false;
    btnAjouteSommet->setChecked(false);
    wid->ss = false;
    btnSupprSommet->setChecked(false);
    wid->sa = false;
    btnSupprArc->setChecked(false);

    wid->complexe.resize(0);
    wid->dessiner();
}

void MainWindow::setAjoutSom()
{
    if (btnAjouteSommet->isChecked())
    {
        wid->as = true;
        wid->aa = false;
        wid->ss = false;
        wid->sa = false;
        wid->e = false;
        btnSupprSommet->setChecked(false);
        btnSupprArc->setChecked(false);
        btnAjoutArc->setChecked(false);
       // enregistrement->setChecked(false);
    }
    else
        wid->as = false;

}

void MainWindow::setQuitter()
{
    if (btnQuitter->isChecked())
    {
       close();
    }
}

void MainWindow::setSupprSom()
{
    if (btnSupprSommet->isChecked())
    {
        wid->as = false;
        wid->aa = false;
        wid->ss = true;;
        wid->sa = false;
        btnAjouteSommet->setChecked(false);
        btnSupprArc->setChecked(false);
        btnAjoutArc->setChecked(false);
        wid->e = false;
        //enregistrement->setChecked(false);
        wid->dep = wid->arr = 0;
    }
    else
        wid->ss = false;
}
void MainWindow::setAjoutArc()
{
    if (btnAjoutArc->isChecked())
    {
        wid->as = false;
        wid->aa = true;
        wid->ss = false;
        wid->sa = false;
        btnSupprSommet->setChecked(false);
        btnSupprArc->setChecked(false);
        btnAjouteSommet->setChecked(false);
        wid->e = false;
        //enregistrement->setChecked(false);
        wid->dep = wid->arr = 0;
    }
    else
        wid->aa = false;
}
void MainWindow::setSupprArc()
{
    if (btnSupprArc->isChecked())
    {
        wid->as = false;
        wid->aa = false;
        wid->ss = false;
        wid->sa = true;
        btnSupprSommet->setChecked(false);
        btnAjouteSommet->setChecked(false);
        btnAjoutArc->setChecked(false);
        wid->e = false;
       // enregistrement->setChecked(false);
        wid->dep = wid->arr = 0;
    }
    else
        wid->sa = false;
}



void MainWindow::dessinerDijkstra()
{
    wid->dessiner();

    grapheov *gOV = nullptr;
    graphenov *gNOV = nullptr;
    gOV = dynamic_cast<grapheov *>(wid->gcourant);
    gNOV = dynamic_cast<graphenov *>(wid->gcourant);

    if (gOV == nullptr && gNOV == nullptr)
    {
        QMessageBox::information(this, "Algorithme de Dijkstra", "L' algo de Dyjksta ne s'execute que sur un graphe valué", QMessageBox::Ok);
        return;
    }

    bool ok;
    int rep = QInputDialog::getInt(nullptr, QString("Dijkstra"), QString("Sommet de départ ? :"), 1, 1, wid->gcourant->nbSommet(), 1, &ok);
    int *d = nullptr, *pere = nullptr;
    if (gOV != nullptr)
        gOV->Dijkstra(rep, d, pere);
    else
        if (gNOV != nullptr)
            gNOV->Dijkstra(rep, d, pere);

    int n = pere[0];
    for (int i = 1; i <= n; ++i)
    {
        if (pere[i] != 0)
        {
            wid->colorierArc(pere[i], i, QColor(Qt::red));
        }
    }
    afficherTab(d);
}

void MainWindow::dessinerTarjan()
{
    wid->dessiner();

    //grapheov *gOV = nullptr;
    grapheonv *gONV = nullptr;
   // gOV = dynamic_cast<grapheov *>(wid->gcourant);
    gONV = dynamic_cast<grapheonv *>(wid->gcourant);

    if (gONV == nullptr)
    {
        QMessageBox::information(this, "Algorithme de Tarjan", "L' algo de Tarjan ne s'execute que sur un graphe valué", QMessageBox::Ok);
        return;
    }

    bool ok;
    int rep = QInputDialog::getInt(nullptr, QString("Tarjan"), QString("Sommet de départ ? :"), 1, 1, wid->gcourant->nbSommet(), 1, &ok);
    int *d = nullptr, *pere = nullptr;

    if (gONV != nullptr)
     {
        //gONV->Tarjan(NULL, d, pere, nullptr);
     }

    int n = pere[0];
    for (int i = 1; i <= n; ++i)
    {
        if (pere[i] != 0)
        {
            wid->colorierArc(pere[i], i, QColor(Qt::red));
        }
    }
    afficherTab(d);
}

void MainWindow::redessinerGraphe()
{
    wid->dessiner();
}

void MainWindow::afficherMatriceAdj()
{
    if (wid->gcourant == nullptr)
        return;

    int **adj = wid->gcourant->fs2adj();

    if (adj == nullptr)
        return;

    int n = adj[0][0];

    QWidget *w = new QWidget();
    QVBoxLayout *Layout = new QVBoxLayout;
    w->setWindowTitle("Matrice d'adjacence");
    QTableWidget *table = new QTableWidget(w);
    table->setRowCount(n);
    table->setColumnCount(n);
    table->resize(110 * n, 40 * n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            table->setItem(i - 1, j - 1, new QTableWidgetItem(QString::number(adj[i][j])));
    Layout->addWidget(table);
    w->setLayout(Layout);
    w->show();
}

void MainWindow::afficherMatriceCouts()
{
    if (wid->gcourant == nullptr)
        return;

    grapheov *gOV = nullptr;
    gOV = dynamic_cast<grapheov *>(wid->gcourant);
    graphenov *gNOV = nullptr;
    gNOV = dynamic_cast<graphenov *>(wid->gcourant);

    if (gNOV == nullptr && gOV == nullptr)
    {
        QMessageBox::information(this, "Matrice des couts", "Le graphe n'est pas valué", QMessageBox::Ok);
        return;
    }

    int **c = nullptr;

    if (gNOV != nullptr)
        c = gNOV->Cout();
    else
        c = gOV->Cout();

    if (c == nullptr)
        return;

    int n = c[0][0];

    QWidget *w = new QWidget();
    QVBoxLayout *Layout = new QVBoxLayout;
    w->setWindowTitle("Matrice des couts");
    QTableWidget *table = new QTableWidget(w);
    table->setRowCount(n);
    table->setColumnCount(n);
    table->resize(105 * n, 35 * n);
    int nb;
    QString str;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            nb = c[i][j];
            if (nb == INT_MAX)
                str = "/";
            else
                str = QString::number(nb);
            table->setItem(i - 1, j - 1, new QTableWidgetItem(str));
        }
    Layout->addWidget(table);
    w->setLayout(Layout);
    w->show();
}

void MainWindow::rang()
{
    if (wid->gcourant == nullptr)
        return;

    grapheov *gOV = dynamic_cast<grapheov *>(wid->gcourant);
    grapheonv *gONV = dynamic_cast<grapheonv *>(wid->gcourant);

    if (gOV == nullptr && gONV == nullptr)
    {
        QMessageBox::information(this, "Algorithme du rang", "L'algorithme du rang ne s'execute que sur un graphe orienté", QMessageBox::Ok);
        return;
    }

    int *rg = nullptr, *pilch, *prem;

    if (gOV != nullptr)
        rg = gOV->rang(pilch, prem);
    else
        rg = gONV->rang(pilch, prem);

    if (rg == nullptr)
        return;

    int n = rg[0];
    QWidget *w = new QWidget();
    w->setWindowTitle("rang des sommets du graphe");
    QTableWidget *table = new QTableWidget(w);
    table->setRowCount(1);
    table->setColumnCount(n);
    table->resize(110 * n, 50);
    for (int i = 1; i <= n; ++i)
        table->setItem(0, i - 1, new QTableWidgetItem(QString::number(rg[i])));
    w->show();
}



void MainWindow::distances()
{
    if (wid->gcourant == nullptr)
        return;

    grapheov *gOV = dynamic_cast<grapheov *>(wid->gcourant);
    grapheov *gONV = dynamic_cast<grapheov *>(wid->gcourant);
    //graphenov *gNOV = dynamic_cast<graphenov *>(wid->gcourant) ;

    if (gOV == nullptr && gONV == nullptr /*&& gNOV == nullptr*/)
    {
        QMessageBox::information(this, "Calcul des distances", "On ne peut calculer les distances que sur un graphe orienté", QMessageBox::Ok);
        return;
    }
    int *dist = nullptr;
    int n = wid->gcourant->nbSommet();
    bool ok;
    int rep = QInputDialog::getInt(nullptr, QString("Distances"), QString("Calcul des distances pour le sommet ? :"), 1, 1, n, 1, &ok);

    if (!ok)
        return;

    if (gOV != nullptr)
        dist = gOV->dist(rep);
    else if (gONV != nullptr)
        dist = gONV->dist(rep);
    /*
    else
    dist = gNOV->dist(rep) ;
    */
    if (dist == nullptr)
        return;

    QWidget *w = new QWidget();
    QVBoxLayout *l = new QVBoxLayout();
    w->setWindowTitle("Distance du sommet" + QString::number(rep));
    w->setLayout(l);
    QTableWidget *table = new QTableWidget(w);
    //l->setWidget(w);
    table->setRowCount(1);
    table->setColumnCount(n);
    table->resize(110 * n, 50);
    for (int i = 1; i <= n; ++i)
        table->setItem(0, i - 1, new QTableWidgetItem(QString::number(dist[i])));
    l->addWidget(table);
    w->setLayout(l);
    w->show();
}

void MainWindow::coderPrufer()
{
    if (wid->gcourant == nullptr)
        return;

    graphenonv *gNONV = nullptr;
    gNONV = dynamic_cast<graphenonv *>(wid->gcourant);

    if (gNONV == nullptr)
    {
        QMessageBox::information(this, "Codagede Prüfer", "Le codage de Prüfer ne s'execute que sur un graphe non-orienté et non-valué", QMessageBox::Ok);
        return;
    }
    int *d = nullptr;
    if (!gNONV->est_arbre(d))
    {
        QMessageBox::information(this, "Codage de Prüfer", "Le graphe n'est pas un arbre", QMessageBox::Ok);
        return;
    }
    if (d == nullptr)
        return;

    int n = d[0];

    QWidget *w = new QWidget();
    w->setWindowTitle("Codage de Prüfer");
    QTableWidget *table = new QTableWidget(w);
    table->setRowCount(1);
    table->setColumnCount(n);
    table->resize(110 * n, 50);
    for (int i = 1; i <= n; ++i)
        table->setItem(0, i - 1, new QTableWidgetItem(QString::number(d[i])));
    w->show();
}





void MainWindow::dessinerKruskal()
{
    wid->dessiner();

    if (wid->gcourant == nullptr)
        return;

    int **arete = nullptr;
    graphenov * gNOV = dynamic_cast<graphenov *>(wid->gcourant);
    if (gNOV == nullptr)
    {
        QMessageBox::information(this, "Algorithme de Kruskal", "L' algo de Kruskal ne s'execute que sur un graphe non-orienté et valué", QMessageBox::Ok);
        return;
    }
    gNOV->Kruskal(arete);

    if (arete == nullptr)
        return;

    int n = wid->gcourant->nbSommet();

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            if (arete[i][j] == 1)
                wid->colorierArc(i, j, QColor(Qt::yellow));

    }

}

void MainWindow::descrDisjktra()
{

    QWidget *window = new QWidget;
       window->resize(320, 240);

       QTextEdit *txt = new QTextEdit();
        txt->setHtml("<html><u><b><i><h2>Algorithme de Dijkstra</h2></i></b></u></br></html>");
        txt->append("<div style='font-size: 14px;'><p>En théorie des graphes, l'algorithme de Dijkstra"
                    " sert à résoudre le problème du plus court chemin. </p><p>Il permet, par exemple, de "
                    "déterminer un plus court chemin pour se rendre d'une ville à une autre connaissant "
                    "le réseau routier d'une région. Plus précisément, il calcule des plus courts chemins "
                    "à partir d'une source dans un graphe orienté pondéré par des réels positifs. On peut "
                    "aussi l'utiliser pour calculer un plus court chemin entre un sommet de départ et un sommet "
                    "d'arrivée.</p></div>");
        txt->setReadOnly(true);
        dockLayout = new QHBoxLayout;
        dockLayout->addWidget(txt);
        window->setLayout(dockLayout);
        window->show();
        window->setWindowTitle(
        QApplication::translate("", "Algorithme de Dijkstra"));

}

void MainWindow::descrKruskal()
{

    QWidget *window = new QWidget;
       window->resize(320, 240);

       QTextEdit *txt = new QTextEdit();
        txt->setHtml("<html><u><b><i><h2>Algorithme de Kruskal</h2></i></b></u></br></html>");
        txt->append("<div style='font-size: 14px;'><p>On considère un graphe connexe non-orienté et pondéré ː chaque arête "
                    "possède un poids qui est un nombre qui représente le coût de cette arête. "
                    "Dans un tel graphe, un arbre couvrant est un sous-graphe connexe sans cycle qui contient "
                    "tous les sommets du graphe. </p></p>Le poids d'un tel arbre est la somme des poids des arêtes "
                    "qui le compose. Un arbre couvrant minimum est un arbre couvrant dont le poids est inférieur "
                    "ou égal à celui de tous les autres arbres couvrants du graphe. L'objectif de l'algorithme de "
                    "Kruskal est de calculer un tel arbre couvrant minimum.</p><p> Ce problème a de nombreuses applications,"
                    " par exemple simplifier un câblage ou supprimer les liaisons maritimes les moins rentables en préservant"
                    " l'accessibilité aux différents ports.</p></div>");
        txt->setReadOnly(true);
        dockLayout = new QHBoxLayout;
        dockLayout->addWidget(txt);
        window->setLayout(dockLayout);
        window->show();
        window->setWindowTitle(
        QApplication::translate("", "Algorithme de Kruskal"));

}

void MainWindow::descrOrdo()
{

    QWidget *window = new QWidget;
       window->resize(320, 240);
       window->show();
       window->setWindowTitle(
           QApplication::translate("", "L'ordonancement"));

}

void MainWindow::descrPruffer()
{

    QWidget *window = new QWidget;
       window->resize(320, 240);
       QTextEdit *txt = new QTextEdit();
        txt->setHtml("<html><u><b><i><h2>Algorithme de Pruffer</h2></i></b></u></br></html>");
        txt->append("<div style='font-size: 14px;'><p>En mathématiques, le codage de Prüfer est une méthode pour décrire de façon compacte un "
                    "arbre dont les sommets sont numérotés1. Ce codage représente un arbre de n sommets numérotés avec une suite "
                    "{\displaystyle P=(x_{1},x_{2},x_{3},...,x_{n-2})} P=(x_{1},x_{2},x_{3},...,x_{{n-2}}) de n-2 termes.</p> <p>Une suite P donnée correspond à un et un seul "
                    "arbre numéroté de 1 à n.Les suites de Prüfer ont été utilisées pour la première fois par Heinz Prüfer pour démontrer la formule de Cayley en 19182.</p<p> On peut "
                    "aussi les utiliser en programmation informatique pour enregistrer la structure d'un arbre de façon plus compacte qu'avec des pointeurs.</div>");
        txt->setReadOnly(true);
        dockLayout = new QHBoxLayout;
        dockLayout->addWidget(txt);
        window->setLayout(dockLayout);
        window->show();
       window->setWindowTitle(
           QApplication::translate("", "Algorithme de Pruffer"));

}

void MainWindow::descrTarjan()
{
    QWidget *window = new QWidget;
       window->resize(320, 240);
       QTextEdit *txt = new QTextEdit();
        txt->setHtml("<html><u><b><i><h2>Algorithme de Tarjan</h2></i></b></u></br></html>");
        txt->append("<div style='font-size: 14px;'><p>L'algorithme prend en entrée un graphe orienté et renvoie une partition "
                    "des sommets du graphe correspondant à ses composantes fortement connexes. Le principe de l'algorithme est"
                    " le suivant : on lance un parcours en profondeur depuis un sommet arbitraire.</p><p>"
                    "Les sommets explorés sont placés sur une pile P. Un marquage spécifique permet de distinguer certains sommets : "
                    "les racines des composantes fortement connexes, c'est-à-dire les premiers</p><p> sommets explorés de chaque composante "
                    "(ces racines dépendent de l'ordre dans lequel on fait le parcours, elles ne sont pas fixées de façon absolue sur le graphe). "
                    "Lorsqu'on termine l'exploration d'un sommet racine v, on retire de la pile tous les sommets jusqu'à v inclus. L'ensemble des "
                    "sommets retirés forme une composante fortement connexe du graphe. S'il reste des sommets non atteints à la fin du parcours, "
                    "on recommence à partir de l'un d'entre eux.</p></div>");
        txt->setReadOnly(true);
        dockLayout = new QHBoxLayout;
        dockLayout->addWidget(txt);
        window->setLayout(dockLayout);
       window->show();
       window->setWindowTitle(
           QApplication::translate("", "Algorithme de Tarjan"));
}

