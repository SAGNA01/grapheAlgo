#ifndef ARC_H
#define ARC_H
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include "sommet.h"

class sommet;
class arc : public QGraphicsLineItem
{
    friend class wgraphe;
public:
    arc(sommet *sommet1, sommet *sommet2, bool oriente, QGraphicsScene* parent);
    int getSommetDep() const;
    int getSommetArr() const;

private:
    QGraphicsScene *d_parent;
    static const int TAILLE = 30, BLANC = 40;
    int sommet_dep, sommet_arr;
};

#endif // ARC_H
