#include"sommet.h"
#include<QInputDialog>
#include<QGraphicsSceneMouseEvent>
#include<string>

sommet::sommet(QWidget *parent, int numero, double x, double y) : QGraphicsEllipseItem{0, 0, WIDTH, HEIGHT},
                                                                  d_numero{numero}, d_parent{parent},
                                                                  d_info{QString::number(numero)}
{
    setPos(x, y);
    setOpacity(1.0);
    setZValue(1);
    setToolTip(d_info);
    setFlag(ItemIsMovable, false);
    setBrush(QBrush(QColor(Qt::green), Qt::SolidPattern));

}

sommet::~sommet(){}

int sommet::getNumero() const {
    return d_numero;
}

QString sommet::getInfo() const {
    return d_info;
}

void sommet::setInfo(QString info) {
    d_info = info; setToolTip(info);
}


void sommet::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        wgraphe *g = static_cast<wgraphe *>(d_parent);

        if (g->getSS())
            g->supprimerSommet(d_numero);

        else if (g->getAA())
        {
            if (g->dep == 0)
            {
                g->dep = this->d_numero;

            }
            else
            {
                g->arr = this->d_numero;
                if (g->value)
                {
                    bool ok;
                    int rep = QInputDialog::getInt(d_parent, QString("Cout"), QString("Cout de l'arc ne Km:"), 0, -9999, 9999, 1, &ok);
                    if (ok)
                        g->ajouterArc(g->dep, g->arr, rep);
                }
                else
                    g->ajouterArc(g->dep, g->arr, 0);

                g->arr = 0;
                g->dep = 0;
            }

        }
        else if (g->getSA())
        {
            if (g->dep == 0)
            {
                g->dep = this->d_numero;

            }
            else
            {
                g->arr = this->d_numero;
                g->supprimerArc(g->dep, g->arr);
                g->arr = 0;
                g->dep = 0;
            }
        }
        else if (g->getE())
        {
            QString str = QInputDialog::getText(d_parent, "Enregistrement", "Texte :");
            setInfo(str);
            //complexe[i] = str ;
            //d_info = str ;
        }
        else
            event->ignore();
    }
}
