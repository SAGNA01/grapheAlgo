#include "arc.h"
#include<math.h>

arc::arc(sommet *sommet1, sommet *sommet2, bool oriente, QGraphicsScene* parent) :
                           QGraphicsLineItem{sommet1->x() + sommet::WIDTH / 2, sommet1->y() + sommet::WIDTH / 2,
                           sommet2->x() + sommet::WIDTH / 2, sommet2->y() + sommet::WIDTH / 2}, d_parent{parent},
                           sommet_dep{sommet1->getNumero()}, sommet_arr{sommet2->getNumero()}
{
    if (oriente){
        double x1 = sommet1->x() + sommet::WIDTH / 2, y1 = sommet1->y() + sommet::WIDTH / 2;
        double x2 = sommet2->x() + sommet::WIDTH / 2, y2 = sommet2->y() + sommet::WIDTH / 2;
        double x3 = x1 + (x2 - x1) / 5;
        double y3 = y1 + (y2 - y1) / 5;
        double dist = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
        double angle = M_PI - acos((x2 - x1) / dist);

            if (y2 - y1 > 0)
            angle *= -1;

            d_parent->addLine(x3, y3, x3 + cos(angle - 30 * M_PI / 180) * 15, y3 + sin(angle - 30 * M_PI / 180) * 15);
            d_parent->addLine(x3, y3, x3 + cos(angle + 30 * M_PI / 180) * 15, y3 + sin(angle + 30 * M_PI / 180) * 15);
        }

}

int arc::getSommetDep() const{
    return sommet_dep;
}
int arc::getSommetArr() const{
    return sommet_arr;
}
