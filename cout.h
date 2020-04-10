#ifndef COUT_H
#define COUT_H
#include<QtGui>
#include<QGraphicsTextItem>

#include"wgraphe.h"
#include"grapheov.h"
#include"graphenov.h"
#include"graphenonv.h"

class wgraphe;
class Couts : public QGraphicsTextItem
{
public:
    Couts(wgraphe *parent, int cout, int sommet1, int sommet2);
    virtual ~Couts();
    //evenement de la souris
    void mouseListener(QGraphicsSceneMouseEvent *e);

private:
    int d_cout;
    wgraphe *d_parent;
    // cout d'un arc
    int sommetDep, sommetArr;
};

#endif // COUT_H
