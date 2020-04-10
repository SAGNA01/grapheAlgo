#ifndef SOMMET_H
#define SOMMET_H
#include "QGraphicsEllipseItem"
#include <QtGui>


#include "wgraphe.h"

class sommet : public QGraphicsEllipseItem
{
    friend class arc;
public:
    sommet(QWidget *parent, int numero, double x, double y);
    virtual ~sommet();
    int getNumero() const;
    QString getInfo() const;

    void setInfo(QString info);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


private :
    int d_numero;
    QWidget *d_parent;
    //information complexe associée au sommet
    QString d_info;
    //taille duQGraphicsEllispseItem
    static const int WIDTH = 40, HEIGHT = 40;
};

#endif // SOMMET_H
