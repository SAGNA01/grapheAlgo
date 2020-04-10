#include "cout.h"
#include"graphe.h"
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>

Couts::Couts(wgraphe *parent, int cout, int sommet1, int sommet2) : QGraphicsTextItem(QString::number(cout)), d_cout{cout},
                                                                    d_parent{parent}, sommetDep{sommet1}, sommetArr{sommet2}
{}

Couts::~Couts(){}

void Couts::mouseListener(QGraphicsSceneMouseEvent *e){
    if (e->button() == Qt::LeftButton)
        {
            bool ok;
            wgraphe * graph = d_parent;
            int sdep = sommetDep;
            int sarr = sommetArr;
            int rep = QInputDialog::getInt(nullptr, QString("Cout"), QString("Cout de l'arc en Km:"), d_cout, -9999, 9999, 1, &ok);
            if (ok)
            {
                grapheov *gOV = nullptr;
                graphenov * gNOV = nullptr;

                gOV = dynamic_cast<grapheov *>(graph->getGCourant());
                gNOV = dynamic_cast<graphenov *>(graph->getGCourant());


                int **couts = nullptr;

                if (gOV != nullptr)
                {
                    couts = gOV->Cout();
                    couts[sdep][sarr] = rep;
                    gOV->setCout(couts);
                }
                else if (gNOV != nullptr)
                {
                    couts = gNOV->Cout();
                    couts[sdep][sarr] = rep;
                    gNOV->setCout(couts);
                }
                graph->dessiner();

            }

        }
}

