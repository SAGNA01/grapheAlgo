#include "wgraphe.h"
#include "sommet.h"
#include "arc.h"
#include "cout.h"
#include "grapheOV.h"
#include "grapheNOV.h"
#include "graphenonv.h"

#include <QInputDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

wgraphe::wgraphe(QWidget * parent) : QWidget{parent}, d_parent{parent}, scene{this}, item{},txt{}, line{},
                                     gcourant{NULL}, aa{false}, as{false}, sa{false}, ss{false}, e{false},
                                     dep{0}, arr{0}, taille_prufer{0}
{
    this->resize(LARG, HAUT);
    view = new QGraphicsView(&scene, this);
    view->resize(HAUT, LARG);
    view->show();
}

wgraphe::~wgraphe()
{
    QList<QGraphicsItem *> tmp = view->items();
    QList<QGraphicsItem *>::iterator it;
    for (it = tmp.begin(); it != tmp.end(); ++it)
        delete *it;
        delete view;
}

void wgraphe::dessiner()
{
    if (gcourant == NULL)
        return;

    int *fs = gcourant->fs(),
        *aps = gcourant->aps();
    if (fs == NULL || aps == NULL)
    {
        scene.clear();
        update();
        scene.update();
        return;
    }

    //suppression de tous les elements de la scene
    QList<QGraphicsItem *> tmp = view->items();
    QList<QGraphicsItem *>::iterator it;
    for (it = tmp.begin(); it != tmp.end(); ++it)
        delete *it;

    int n = gcourant->nbSommet();

    QPoint centre((this->LARG) / 2, (this->HAUT) / 2);
    double dTeta = 2 * 3.14 / n;
    double teta = 0;
    double x, y;
    //on redimensionne les vector avec le nombre de sommets du graphe
    item.resize(n);
    txt.resize(n);
    complexe.resize(n);
    //affichage des sommets et leurs numeros
    for (int i = 0; i<n; ++i, teta += dTeta)
    {
        x = centre.x() + RAYON*cos(teta);
        y = centre.y() + RAYON*sin(teta);
        //ajout du sommets
        sommet *s = new sommet(this, i + 1, x, y);
        s->setInfo(complexe[i]);
        s->setToolTip(complexe[i]);
        item[i] = s;
        scene.addItem(s);

        //ajout du numero du sommet
        txt[i] = scene.addText(QString::number(i + 1));
        txt[i]->setPos(x + 3, y);
        txt[i]->setZValue(2);
    }

    fs = gcourant->fs(),
        aps = gcourant->aps();
    int m = 0;
    int **cou = nullptr;
    grapheOV *gOV = dynamic_cast<grapheOV *>(gcourant);
    grapheNOV *gNOV = dynamic_cast<grapheNOV *>(gcourant);

    if (value)
        if (gOV != nullptr)
            cou = gOV->Cout();
        else if (gNOV != nullptr)
            cou = gNOV->Cout();

    line.resize(fs[0] - aps[0]);

    //parcour des succcesseurs de chaque sommet pour afficher les aretes
    for (int i = 1; i <= n; ++i)
    {
        for (int j = aps[i], k; (k = fs[j])>0; ++j)
        {
            QPointF x1(item[i - 1]->pos()),
                x2(item[k - 1]->pos());

            line[m] = new arc(this->item[i - 1], this->item[k - 1], oriente, &scene);
            scene.addItem(line[m]);
            ++m;

            if (value)
            {
                Couts *c = new Couts(this, cou[i][k], i, k);
                scene.addItem(c);
                c->setPos(x1.x() + (x2.x() - x1.x()) / 4, x1.y() + (x2.y() - x1.y()) / 4);
            }
        }
    }
    delete[] fs;
    delete[] aps;
    delete[] cou;

}

void wgraphe::setGraphe(graphe *g)
{
    delete gcourant;

    QList<QGraphicsItem *> tmp = view->items();
    QList<QGraphicsItem *>::iterator it;
    for (it = tmp.begin(); it != tmp.end(); ++it)
        delete *it;

    if (g == nullptr)
    {
        gcourant = nullptr;
        item.resize(0);
        txt.resize(0);
        line.resize(0);
    }
    else
    {
        gcourant = g;
        int n = gcourant->nbSommet();
        int *fs = gcourant->fs();
        item.resize(n);
        txt.resize(n);
        line.resize(fs[0] - n);
    }
}

void wgraphe::mousePressEvent(QMouseEvent *e)
{
    if (gcourant == nullptr)
        return;
    //ajout d'un sommet
    if (as && e->button() == Qt::LeftButton)
    {
        gcourant->ajoutSommet();
        int n = gcourant->nbSommet();
        complexe.resize(n);
        complexe[n - 1] = QString::number(n);
        dessiner();
    }
}

void wgraphe::supprimerSommet(int num)
{
    gcourant->supprSommet(num);
    dessiner();
}

void wgraphe::ajouterArc(int s1, int s2, int cout)
{
    gcourant->ajoutArc(s1, s2, cout);
    dessiner();
}

void wgraphe::supprimerArc(int sommet1, int sommet2)
{
    gcourant->supprArc(sommet1, sommet2);
    dessiner();
}

void wgraphe::colorierArc(int sommet1, int sommet2, QColor c)
{
    int n = line.size();
    QPen pen(c);
    pen.setWidth(3);
    for (int i = 0; i<n; ++i)
    {
        if (line[i]->getSommetDep() == sommet1 && line[i]->getSommetArr() == sommet2)
        {
            line[i]->setPen(pen);
            break;
        }
    }
}

void wgraphe::lirePrufer()
{
    bool ok;
    int rep = rep = QInputDialog::getInt(NULL, QString("Décodage de Prüfer"), QString("Taille du code ? :"), 1, 1, 100, 1, &ok);
    if (!ok)
        return;
    prufer = new QWidget();
    prufer->setWindowTitle("Décoder Prüfer");
    table = new QTableWidget(prufer);
    QPushButton *b = new QPushButton("Valider", prufer);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(table);
    layout->addWidget(b);
    prufer->setLayout(layout);

    table->setRowCount(1);
    table->setColumnCount(rep);
    table->resize(110 * rep, 50);
    for (int i = 1; i <= rep; ++i)
        table->setItem(0, i - 1, new QTableWidgetItem(""));
    prufer->show();
    taille_prufer = rep;
    QObject::connect(b, SIGNAL(clicked()), this, SLOT(creerPrufer()));
}

void wgraphe::creerPrufer()
{
    int* tab = new int[taille_prufer + 1];
    tab[0] = taille_prufer;
    for (int i = 1; i <= taille_prufer; i++)
    {
        tab[i] = table->item(0, i - 1)->text().toInt();
    }

    int** adj = grapheNONV::decodage(tab);
    grapheNONV *gNONV = new grapheNONV(adj);

    setGraphe(gNONV);
    prufer->close();
    int n = gcourant->nbSommet();
    complexe.resize(n);
    for (int i = 1; i <= n; ++i)
        complexe[i - 1] = i;
    value = false;
    oriente = false;
    dessiner();

}

void wgraphe::ordonnancement()
{
    if (gcourant == NULL)
        return;

    grapheOV *gOV = dynamic_cast<grapheOV *>(gcourant);
    if (gOV == NULL)
    {
        QMessageBox::information(this, "Ordonnancement", "L'ordonnancement ne s'execute que sur un graphe orienté et valué", QMessageBox::Ok);
        return;
    }

    w = new QWidget();
    w->setWindowTitle("Ordonnancement");
    table = new QTableWidget(w);
    int n = gcourant->nbSommet();
    QPushButton *b = new QPushButton("Valider", w);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(table);
    layout->addWidget(b);
    w->setLayout(layout);
    table->resize(110 * n, 50 * n);
    table->setColumnCount(4);
    //int n = gcourant->nbSommet() ;
    table->setRowCount(n);
    QTableWidgetItem* t = new QTableWidgetItem("N° tache");
    table->setHorizontalHeaderItem(0, t);
    t = new QTableWidgetItem("Intitulé");
    table->setHorizontalHeaderItem(1, t);
    t = new QTableWidgetItem("cout");
    table->setHorizontalHeaderItem(2, t);
    t = new QTableWidgetItem("Pred");
    table->setHorizontalHeaderItem(3, t);
    table->resize(440, 50 * n);
    for (int i = 1; i <= n; ++i)
        table->setItem(i - 1, 0, new QTableWidgetItem(QString::number(i)));
    w->show();
    QObject::connect(b, SIGNAL(clicked()), this, SLOT(creerOrdo()));
}

void wgraphe::creerOrdo()
{
    int n = gcourant->nbSommet(),
        nb = 0;
    QString str;
    //on compte le nombre de pred pour avoir la taille de fp
    for (int i = 0; i<n; ++i)
    {
        if (table->item(i, 3) == NULL)
            str = "";
        else
            str = table->item(i, 3)->text();
        for (int j = 0; j<str.size(); ++j)
        {
            if (str[j] != ',')
            {
                //qDebug() << str[j] << " " ;
                nb++;
                if ((j + 1)<str.size() && str[j + 1] != ',')
                    j++;
            }
        }
    }

    int *fp = new int[n + nb];
    int  cptfp = 1;
    fp[0] = n + nb;

    int *cout = new int[n + 1];
    cout[0] = n;
    QString tmp;
    //parcours de la tablewidget pour remplir fp
    for (int i = 0; i<n; ++i)
    {
        complexe[i] = table->item(i, 1)->text();
        if (table->item(i, 3) == NULL)
            str = "";
        else
            str = table->item(i, 3)->text();

        cout[i + 1] = table->item(i, 2)->text().toInt();
        for (int j = 0; j<str.size(); ++j)
            if (str[j] != ',')
            {
                tmp = str[j];
                if ((j + 1)<str.size() && str[j + 1] != ',')
                    tmp += str[++j];
                fp[cptfp++] = atoi(tmp.toStdString().c_str());
            }
        fp[cptfp++] = 0;
    }

    int *fs = grapheOV::fs2fp_(fp);
    int **dcout = new int*[n + 1];
    dcout[0] = new int[1];
    for (int i = 1; i <= n; ++i)
    {
        dcout[i] = new int[n + 1];
        dcout[i][0] = n;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            dcout[i][j] = INT_MAX;

    int taille = fs[0], sommet = 1;
    for (int i = 1; i <= taille; ++i)
        if (fs[i] == 0)
            ++sommet;
        else
            dcout[sommet][fs[i]] = cout[sommet];
    w->close();
    delete gcourant;
    int *aps = graphe::fs2aps(fs);
    grapheOV *gOV = new grapheOV(fs, aps, dcout);
    int *lc, *fpc, *appc;
    gcourant = gOV->Critique(lc, fpc, appc, cout);
    complexe.resize(gcourant->nbSommet());
    for (int i = gcourant->nbSommet() - 2; i >= 0; --i)
    complexe[i + 1] = complexe[i];
    complexe[0] = "Initial";
    complexe[gcourant->nbSommet() - 1] = "Final";

    dessiner();
    int w = appc[0];
    while (fpc[appc[w]] != 0)
    {
        colorierArc(fpc[appc[w]], w, QColor(Qt::green));
        w = fpc[appc[w]];
    }
}
